// Fill out your copyright notice in the Description page of Project Settings.

#include "TEST_TMAP.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATEST_TMAP::ATEST_TMAP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootyTooty"));

	const int NumMeshes = 3;
	Meshes.Reserve(NumMeshes);

	

}

// Called when the game starts or when spawned
void ATEST_TMAP::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATEST_TMAP::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	
}

// Called every frame
void ATEST_TMAP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for( const TPair<uint8, UStaticMeshComponent*>& Map : Meshes )
	{
		const FRotator Rot = FRotator( 0.0f, Map.Key * 3.0f, 0.0f );
		Map.Value->AddLocalRotation(Rot);
	}

}

