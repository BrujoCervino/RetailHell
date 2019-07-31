// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Customer.generated.h"

/*
* Date Created: 22/07/19
* The base class of all customers. 
* Essentially the game's enemies, customers are a mix between quest-giving NPCs and
*	typical enemies in a game. A customer's job is to talk (play dialogue lines) to 
*	the player and set missions for the player to complete.
*/
UCLASS()
class SMALLSCOPE_API ACustomer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
