// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TEST_TMAP.generated.h"

/*
	Date created: 28/07/19
	A test for UE4's map data structure.
*/
UCLASS()
class SMALLSCOPE_API ATEST_TMAP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATEST_TMAP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, Instanced)
	TMap<uint8, UStaticMeshComponent*> Meshes;
	
};
