// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RetailCharacter.generated.h"

// #ToDo: If I have remappable controls, I can tear out the entire camera inversion
//	(the player can remap to -Axis (See DmC: Devil May Cry)).
// 
UENUM()
enum class ECameraInversion : uint8
{
	ECI_Standard = 0,
	ECI_Inverted = 1
};
/*
	Date created: 26/06/19
*/
UCLASS()
class SMALLSCOPE_API ARetailCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARetailCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// 
	UFUNCTION(Category = "Character|CustomControls", BlueprintCallable)
	virtual float InvertCameraAxes();
	
	UFUNCTION(Category = "Character|CustomControls", BlueprintCallable)
	virtual float GetCameraInversionSigns() const; 


private:

	// #ToDo: If I have remappable controls, I can tear out the entire camera inversion (the player can remap to -Axis (See DmC: Devil May Cry).
	//
	UPROPERTY(Category = "Character|CustomControls", BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FVector2D CameraAxisInversion;

};
