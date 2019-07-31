// Fill out your copyright notice in the Description page of Project Settings.

#include "RetailCharacter.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ARetailCharacter::ARetailCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// General defaults:
	// Camera:
}

// Called when the game starts or when spawned
void ARetailCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARetailCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARetailCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ARetailCharacter::InvertCameraAxes()
{
	return 0.0f;
}


float ARetailCharacter::GetCameraInversionSigns() const
{
	return 0.0f;
}

