// Charles River Analytics Inc. -- Arthur Wollocko (awollocko@cra.com), 2020

#include "VSDKCharacter.h"
#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Engine/EngineTypes.h>
#include "TimerManager.h"
#include <GameFramework/PlayerController.h>
#include <GameFramework/Actor.h>
#include <Components/CapsuleComponent.h>
#include <Engine/World.h>
#include "NavigationSystem.h"
#include "MotionControllerComponent.h"
#include "DrawDebugHelpers.h"
#include <PhysicsEngine/PhysicsConstraintComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>
#include "../HandPresence/Hand.h"
#include "../Locomotion/LocomotionBase.h"

AVSDKCharacter::AVSDKCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up a ROOT vr object. Important since we'll have to account for the offset that Unreal automatically puts on the Camera when in VR.
	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VR Root"));
	VRRoot->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(VRRoot);

	// Controllers are specified as Actors, and therefore instantiated within BeginPlay 
}

void AVSDKCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get the offset from camera to the actor
	FVector NewCameraOffset = CameraComponent->GetComponentLocation() - GetActorLocation();
	AddActorWorldOffset(NewCameraOffset);
	// Zero out the Z, so no differential up/down on the camera
	NewCameraOffset.Z = 0.f;

	// Reset the VR root back a bit, so the user doesn't see the movement of the pawn
	VRRoot->AddWorldOffset(NewCameraOffset);

	// Spawn the VSDK Hands
	LeftHand = GetWorld()->SpawnActor<AHand>(HandLeftControllerBlueprint);
	if (LeftHand)
	{
		LeftHand->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
		LeftHand->SetHand(EControllerHand::Left);
		LeftHand->SetVSDKCharacter(this);
		LeftHand->SetOwner(this);
	}
	RightHand = GetWorld()->SpawnActor<AHand>(HandRightControllerBlueprint);
	if (RightHand)
	{
		RightHand->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
		RightHand->SetHand(EControllerHand::Right);
		RightHand->SetVSDKCharacter(this);
		RightHand->SetOwner(this);

		// For now, locomotion is on the right hand. TODO: Enum and move this around
		if (LocomotionClassBlueprint)
		{
			Locomotion = GetWorld()->SpawnActor<ALocomotionBase>(LocomotionClassBlueprint);
			Locomotion->AttachToComponent(RightHand->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			Locomotion->SetOwner(RightHand);
		}
	}
}

// Called to bind functionality to input. Allows binding to VSDK inputs (T1)
void AVSDKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AVSDKCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AVSDKCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("VirtuosoGrabL"), IE_Pressed, this, &AVSDKCharacter::GrabL);
	PlayerInputComponent->BindAction(TEXT("VirtuosoGrabL"), IE_Released, this, &AVSDKCharacter::UnGrabL);

	PlayerInputComponent->BindAction(TEXT("VirtuosoGrabR"), IE_Pressed, this, &AVSDKCharacter::GrabR);
	PlayerInputComponent->BindAction(TEXT("VirtuosoGrabR"), IE_Released, this, &AVSDKCharacter::UnGrabR);

	PlayerInputComponent->BindAction(TEXT("VirtuosoUseL"), IE_Pressed, this, &AVSDKCharacter::UseL);
	PlayerInputComponent->BindAction(TEXT("VirtuosoUseL"), IE_Released, this, &AVSDKCharacter::StopUseL);

	PlayerInputComponent->BindAction(TEXT("VirtuosoUseR"), IE_Pressed, this, &AVSDKCharacter::UseR);
	PlayerInputComponent->BindAction(TEXT("VirtuosoUseR"), IE_Released, this, &AVSDKCharacter::StopUseR);
}


void AVSDKCharacter::MoveForward(float Value)
{
	AddMovementInput(CameraComponent->GetForwardVector() * Value);
}

void AVSDKCharacter::MoveRight(float Value)
{
	AddMovementInput(CameraComponent->GetRightVector() * Value);
}

void AVSDKCharacter::GrabL()
{
	LeftHand->Grab();
}

void AVSDKCharacter::GrabR()
{
	RightHand->Grab();
}

void AVSDKCharacter::UnGrabL()
{
	LeftHand->DropCurrent();
}

void AVSDKCharacter::UnGrabR()
{
	RightHand->DropCurrent();
}

void AVSDKCharacter::UseL()
{
	LeftHand->Use();
}

void AVSDKCharacter::UseR()
{
	RightHand->Use();
}

void AVSDKCharacter::StopUseL()
{
	LeftHand->StopUse();
}

void AVSDKCharacter::StopUseR()
{
	RightHand->StopUse();
}

