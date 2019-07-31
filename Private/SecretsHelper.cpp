// Fill out your copyright notice in the Description page of Project Settings.

#include "SecretsHelper.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASecretsHelper::ASecretsHelper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Explicitly ensure gravity begins unoverridden
	SetOverrideGravity(false);
	// Explicitly ensure time begins undilated
	OverrideGlobalTimeDilation(ETimeDilation::ETD_Standard);

	// 
	MirrorMultiplier = MirrorState::UnMirrored;

}

void ASecretsHelper::SetOverrideGravity(const bool bOverride)
{
	// If we can access the world,
	if( GetWorld() )
	{
		if( bOverride )
		{
			// Override the gravity.
			GetWorld()->GetWorldSettings()->bGlobalGravitySet = true;
			GetWorld()->GetWorldSettings()->GlobalGravityZ = 0.1f;
		}
		else
		{
			// Revert to standard gravity.
			GetWorld()->GetWorldSettings()->bGlobalGravitySet = false;
		}
	}
}

void ASecretsHelper::OverrideGlobalTimeDilation(const ETimeDilation DilationState)
{
	// Create a float in which to store the dilation
	float NewTimeDilation = 0.0f;
	
	// Store the standard time
	static constexpr float StandardTime = 1.0f;
	
	// Switch by dilation state
	switch( DilationState )
	{
		case ( ETimeDilation::ETD_FastMotion ):
		{
			NewTimeDilation = 10.0f;
			break;
		};
		case ( ETimeDilation::ETD_SlowMotion ):
		{
			NewTimeDilation = 0.1f;
			break;
		};
		case ( ETimeDilation::ETD_Standard ):
		{
			NewTimeDilation = StandardTime;
			break;
		};
		default:
		{
			NewTimeDilation = StandardTime;
			break;
		};
	};
	// Dilate time.
	UGameplayStatics::SetGlobalTimeDilation(this, NewTimeDilation);
}

void ASecretsHelper::MirrorWorld(const bool bMirrored, UPARAM(ref) FWeightedBlendable& MirroringMaterial)
{
	if( bMirrored )
	{
		// Set the blend weight of the horizontal res-switcher to 1.
		MirroringMaterial.Weight = MirrorWeight::Full;

		// Set the player movement input and player camera input to -1
		MirrorMultiplier = MirrorState::Mirrored;
	}
	else
	{
		// Set the blend weight of the horizontal res-switcher to 0.
		MirroringMaterial.Weight = MirrorWeight::Empty;

		// Set the player movement input and player camera input to 1
		MirrorMultiplier = MirrorState::UnMirrored;
	}
}