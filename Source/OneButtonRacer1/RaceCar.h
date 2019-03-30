// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/Classes/Components/SplineComponent.h"
#include "RaceCar.generated.h"

UCLASS()
class ONEBUTTONRACER1_API ARaceCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARaceCar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RaceTrack")
		USplineComponent* RaceTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RaceCar")
		float acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RaceCar")
		float deAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RaceCar")
		bool accelerating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RaceCar")
		float maxSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RaceCar")
		float currentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RaceCar")
		float crashRotAndSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RaceCar")
		FVector oldLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RaceCar")
		FRotator oldRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RaceCar")
		float currentLength;

	void addSpeed();
	void addSpeedEnd();


	bool checkCrash(FRotator newRotation);

	UFUNCTION(BlueprintImplementableEvent, Category = "RaceCar")
		void crash();

	UFUNCTION(BlueprintCallable, Category = "RaceTrack")
		void getTrackInfo();

	float trackDistance;



};
