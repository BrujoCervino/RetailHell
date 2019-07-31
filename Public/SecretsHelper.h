// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "SecretsHelper.generated.h"

struct FWeightedBlendable;

// The time dilation state used within OverrideGlobalTimeDilation
// (Marked as UENUM because accessed by Blueprints)
UENUM()
enum class ETimeDilation : uint8
{
	ETD_Standard = 0,
	ETD_SlowMotion = 1,
	ETD_FastMotion = 2
};

namespace MirrorState // Used for mirroring camera and movement input
{
	static constexpr float Mirrored = -1.0f;
	static constexpr float UnMirrored = 1.0f;
};

namespace MirrorWeight // Used for postprocess material blend weights
{
	static constexpr float Empty = 0.0f;
	static constexpr float Full = 1.0f;
};

/* 
* Date created: 28/06/19
* Handles and applies all unlockable cheats in the game: such as silly gravity, slow motion and more.
* Chose not to derive from UCheatManager because derivation from AActor allows this class to have different
* cheats active in different UWorlds, and AInfo is recommended for "manager classes" (Info.h).
* Consider: making an interface whose implementors can access and edit ASecretsHelper
* #ToDo: Spawn only one of this actor in each world through the GameMode
* Limitation: an instance of this class must exist in the world, otherwise features affected by cheats (such as player movement and gravity)
* 	will not work correctly.
*/
UCLASS(notplaceable,meta=(ShortToolTip="SecretsHelper handles and applies all unlockable cheats in the game."))
class SMALLSCOPE_API ASecretsHelper : public AInfo
{
	GENERATED_BODY()
	
public:	
	// Default constructor
	ASecretsHelper();

	// Override the world's gravity, applying a silly amount of gravity.
	// Param: const bool bOverride : Whether gravity is silly and overridden (true), or normal (false)
	// (Marked as a UFUNCTION because can be called in Blueprints)
	UFUNCTION(Category = "Secrets", BlueprintCallable )
	void SetOverrideGravity(const bool bOverride); 

	// Dilate time: apply slow motion or fast motion or revert to undilated time.
	// Param: const ETimeDilation DilationState : the dilation to be applied (see ETimeDilation)
	// (Marked as a UFUNCTION because can be called in Blueprints)
	UFUNCTION(Category = "Secrets", BlueprintCallable)
	void OverrideGlobalTimeDilation(const ETimeDilation DilationState);

	// Flips the player's view of the world horizontally, using a postprocess material
	// Param: const bool bMirrored : whether the world will be mirrored
	// Param: UPARAM(ref) FWeightedBlendable& MirroringMaterial : a reference to the postprocess 
	//		material to be changed by this function 
	//		(Marked as a UPARAM because that's the only way to pass by reference to a Blueprint parameter)
	// (Marked as a UFUNCTION because can be called in Blueprints)
	UFUNCTION(Category = "Secrets", BlueprintCallable)
	void MirrorWorld(const bool bMirrored, UPARAM(ref) FWeightedBlendable& MirroringMaterial);

private:

	// Multiply your horizontal turn axis and horizontal move axis by this number to reverse input
	UPROPERTY(Category="Secrets", BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	float MirrorMultiplier;

};
