// Charles River Analytics Inc. -- Arthur Wollocko (awollocko@cra.com), 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Locomotion/LocomotionBase.h"
#include "VSDKCharacter.generated.h"

/**
 * Main VSDK Character, will contain the motion controllers as hands, including interaction capabilities triggered through VSDK custom input system
 * 
 * Written by: Arthur Wollocko (awollocko@cra.com), 2020
 */
UCLASS()
class VSDKINPUTPLUGIN_API AVSDKCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVSDKCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/** Teleport Functionality */
	// TODO: Add enum for WHICH HAND to have locomotion on
	UPROPERTY(EditDefaultsOnly, Category = "VSDK | Locomotion")
		TSubclassOf<class ALocomotionBase> LocomotionClassBlueprint;
	UPROPERTY(VisibleAnywhere, Category = "VSDK | Locomotion")
		class ALocomotionBase* Locomotion;


	/** Hand Controller Setup Parameters */
	UPROPERTY(EditDefaultsOnly, Category = "VSDK | Hands")
		TSubclassOf<class AHand> HandLeftControllerBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "VSDK | Hands")
		TSubclassOf<class AHand> HandRightControllerBlueprint;

	/**  Provide a new ROOT object to offset the head movements (HMD) from the capsule collider of the player. This allows for actual offset of HMD from the base of the capsule (which is typical on characters) */
	UPROPERTY(VisibleAnywhere)
		USceneComponent* VRRoot;
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* CameraComponent;

private: // Configuration Parameters

	/** Hand Setup */
	UPROPERTY()
		class AHand* LeftHand;
	UPROPERTY()
		AHand* RightHand;

	/** Move Functionality */
	void MoveForward(float Value);
	void MoveRight(float Value);

	/** Grabbing Functionality */
	void GrabL();
	void GrabR();
	void UnGrabL();
	void UnGrabR();

	/** Use Functionality */
	void UseL();
	void UseR();
	void StopUseL();
	void StopUseR();

};

