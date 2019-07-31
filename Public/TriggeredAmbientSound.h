// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/AmbientSound.h"
#include "TriggeredAmbientSound.generated.h"

class USphereComponent;

/*  
* Date Created: 19/07/19
* A sound actor which plays upon overlap by a specified actor
*/
UCLASS()
class SMALLSCOPE_API ATriggeredAmbientSound : public AAmbientSound
{
	GENERATED_BODY()
	
public:

	// Default constructor
	ATriggeredAmbientSound();
	
	// Returns Trigger
	inline USphereComponent* GetTrigger() const { return Trigger; }

private:

	// The sphere trigger whose overlap checks handle the playing and stopping of the audio component
	UPROPERTY(Category = "TriggeredAmbientSound", EditAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = true ))
	USphereComponent* Trigger;
	
protected:

	// Implement AActor::OnConstruction:
	// Utilised to prevent certain changes within the editor, and use functions only safe within the construction script
	virtual void OnConstruction(const FTransform& Transform) override;

	// A delegate bound to the sphere trigger's OnComponentBeginOverlap event
	// (Marked as a UFUNCTION because is a delegate)
	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// A delegate bound to the sphere trigger's OnComponentEndOverlap event
	// (Marked as a UFUNCTION because is a delegate)
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// A delegate bound to the audio component's OnAudioFinished event
	// (Marked as a UFUNCTION because is a delegate)
	UFUNCTION()
	virtual void OnStopAudio();

	// Returns whether this actor can play the audio component, at the moment of the function call
	// Param: const bool bCanRandomlyPlay : whether randomness should affect whether the sound can play
	// (Marked as a UFUNCTION because can be called in Blueprints)
	UFUNCTION(Category = "TriggeredAmbientSound|AudioPlayback", BlueprintCallable, meta = ( BlueprintProtected = true ))
	virtual bool CanPlayAudio(const bool bCanRandomlyPlay = false) const;

	// Plays the audio component, only if CanPlayAudio returns true
	// Param: const bool bAllowRandomlyPlay : whether randomness should affect whether the sound can play
	// Consider: making this a function for an interface, because I'm finding I need this across so many classes
	// (Marked as a UFUNCTION because can be called in Blueprints)
	UFUNCTION(Category = "TriggeredAmbientSound|AudioPlayback", BlueprintCallable, meta = ( BlueprintProtected = true ))
	virtual bool SafelyPlayAudio(const bool bAllowRandomlyPlay = false) const;

private:

	// Whether the sound should stop playing on exit
	// Consider switching this to an enum: the music could fade out, stop or be unaffected.
	UPROPERTY(Category = "TriggeredAmbientSound", EditAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = true ))
	bool bStopPlayingOnExit;

	// Whether the sound can randomly play by default
	UPROPERTY(Category = "TriggeredAmbientSound", EditAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = true ))
	bool bRandomlyPlayByDefault;
};
