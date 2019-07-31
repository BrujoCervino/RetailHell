// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AnnoyingGameModeBase.generated.h"

/**
 * Date created: 22/07/19
 * The base game mode.
 */
UCLASS()
class SMALLSCOPE_API AAnnoyingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	// Default constructor
	AAnnoyingGameModeBase();
	
	virtual void BeginPlay() override;

};
