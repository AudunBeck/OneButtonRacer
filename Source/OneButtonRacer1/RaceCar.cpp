// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceCar.h"

// Sets default values
ARaceCar::ARaceCar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARaceCar::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARaceCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RaceTrack != nullptr)
	{
		if (accelerating)
			currentSpeed = (acceleration * DeltaTime) + currentSpeed;
		else if (currentSpeed > 0.f)
			currentSpeed = (deAcceleration * DeltaTime) + currentSpeed;
		else
			currentSpeed = 0.f;
		currentLength += currentSpeed;
		if (currentLength >= trackDistance)
			currentLength -= trackDistance;
		FVector newLocation = RaceTrack->GetLocationAtDistanceAlongSpline(currentLength, ESplineCoordinateSpace::World);
		FRotator newRotation = RaceTrack->GetRotationAtDistanceAlongSpline(currentLength, ESplineCoordinateSpace::World);
		SetActorLocationAndRotation(newLocation, newRotation);
		if (checkCrash(newRotation))
			crash();
		else
		{
			oldLocation = newLocation;
			oldRotation = newRotation;
		}

	}
}

// Called to bind functionality to input
void ARaceCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Throttle", IE_Pressed, this, &ARaceCar::addSpeed);
	PlayerInputComponent->BindAction("Throttle", IE_Released, this, &ARaceCar::addSpeedEnd);
}

void ARaceCar::addSpeed()
{
	accelerating = true;
}

void ARaceCar::addSpeedEnd()
{
	accelerating = false;
}

bool ARaceCar::checkCrash(FRotator newRotation)
{
	FVector newRotationVec, oldRotationVec;
	newRotationVec = newRotation.Vector();
	oldRotationVec = oldRotation.Vector();
	float dotProduct = FVector::DotProduct(oldRotationVec, newRotationVec);

	float rotationStrength = (1-dotProduct) * currentSpeed;

	UE_LOG(LogTemp, Warning, TEXT("Dot product is %f || Rotation strength is %f"),dotProduct, rotationStrength);

	if (rotationStrength > crashRotAndSpeed)
		return true;
	else
		return false;

}

void ARaceCar::getTrackInfo()
{
	trackDistance = RaceTrack->GetSplineLength();
}

