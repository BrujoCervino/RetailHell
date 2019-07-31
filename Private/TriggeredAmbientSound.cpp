// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggeredAmbientSound.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"

ATriggeredAmbientSound::ATriggeredAmbientSound()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// Note: as discussed in previous projects, I have bound delegates to component events (instead of overriding 
	// the more generic actor events), to make my programming more defensive: by binding to specific component events,
	// I can choose which trigger does what

	// Create the sphere trigger subobject
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	if( Trigger )
	{
		// Attach the trigger to our audio component.
		Trigger->SetupAttachment( GetAudioComponent() );

		// Add this class's delegates to the trigger's events
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATriggeredAmbientSound::OnSphereBeginOverlap);
		Trigger->OnComponentEndOverlap.AddDynamic(this, &ATriggeredAmbientSound::OnSphereEndOverlap);
	}

	// Add this class's delegate to the audio component's events
	GetAudioComponent()->OnAudioFinished.AddDynamic(this, &ATriggeredAmbientSound::OnStopAudio);

	// General defaults:
	bStopPlayingOnExit = false;
	bRandomlyPlayByDefault = false;
}

void ATriggeredAmbientSound::OnConstruction(const FTransform & Transform)
{
	// Don't call Super::OnConstruction, because neither AActor nor AAmbientSound implements it.

	// Ensure our sound is not played when the game starts.
	// (Called here because UActorComponent::SetAutoActivate is only safe within construction scripts(see ActorComponent.h)).
	GetAudioComponent()->SetAutoActivate(false);

	// Ensure the trigger can never be moved away from the root component, in-editor.
	Trigger->SetRelativeLocation(FVector::ZeroVector);
}

void ATriggeredAmbientSound::OnSphereBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// If the overlapper is the player,
	// Note: For #expansibility, an int can be used instead of a bool here to 
	//	check how many players are in the trigger at once (if the sound replicates).
	// Elsewise, this function will remain the same as in single-player
	if( OtherActor->ActorHasTag("Player") )
	{
		SafelyPlayAudio(bRandomlyPlayByDefault);
	}
}

void ATriggeredAmbientSound::OnSphereEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if( bStopPlayingOnExit )
	{
		// If the overlapper is the player,
		if( OtherActor->ActorHasTag("Player") )
		{
			if( GetAudioComponent()->IsPlaying() )
			{
				GetAudioComponent()->Stop();
			}
		}
	}
}

void ATriggeredAmbientSound::OnStopAudio()
{
}

bool ATriggeredAmbientSound::CanPlayAudio(const bool bCanRandomlyPlay /*= false*/) const
{
	// Decide whether the sound will randomly play.
	const bool bShouldPlay = bCanRandomlyPlay ? FMath::RandBool() : true;

	return ( bShouldPlay && !GetAudioComponent()->IsPlaying() );
}

bool ATriggeredAmbientSound::SafelyPlayAudio(const bool bAllowRandomlyPlay /*= false*/) const
{
	if( CanPlayAudio(bAllowRandomlyPlay) )
	{
		GetAudioComponent()->Play();
		return true;
	}
	return false;
}