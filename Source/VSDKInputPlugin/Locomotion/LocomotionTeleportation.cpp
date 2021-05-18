// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "LocomotionTeleportation.h"
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
#include <Kismet/GameplayStaticsTypes.h>
#include "../HandPresence/Hand.h"
#include <Components/SceneComponent.h>
#include <UObject/NoExportTypes.h>


ALocomotionTeleportation::ALocomotionTeleportation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// Teleport Path Spline
	LocomotionRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LocoRoot"));
	SetRootComponent(LocomotionRoot);

	// Teleporting
	DestinationMarker = CreateDefaultSubobject<USceneComponent>(TEXT("DestinationMarkerParent"));
	DestinationMarker->SetupAttachment(GetRootComponent());
	DestinationMarkerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestinationMesh"));
	DestinationMarkerMesh->SetupAttachment(DestinationMarker);

	// Setup initial variables for things
	bLocomotionEnabled = false;
	TeleportFadeTime = .5f;
	TeleportFadeColor = FLinearColor::Black;
}


void ALocomotionTeleportation::Tick(float DeltaTime)
{
	if (bLocomotionEnabled)
	{
		UpdateDestinationMarker();
	}
}


void ALocomotionTeleportation::BeginPlay()
{
	Super::BeginPlay();

	ControllingActor = Cast<AHand>(GetOwner());
	if (PlayerController)
	{
		// Thumbstick touch to enable/disable
		InputComponent->BindAction(TEXT("VirtuosoJoystickClickR"), IE_Pressed, this, &ALocomotionTeleportation::EnableLocomotion);
		InputComponent->BindAction(TEXT("VirtuosoJoystickClickR"), IE_Released, this, &ALocomotionTeleportation::DisableLocomotion);

		InputComponent->BindAxis("VirtuosoJoystickXR", this, &ALocomotionTeleportation::DestinationRotationAdjustment);
	}

	// Set up the pointer from the BLUEPRINT provided
	pointer = GetWorld()->SpawnActor<APointerBase>(pointerBp);
	pointer->AttachToComponent(LocomotionRoot, FAttachmentTransformRules::KeepRelativeTransform);
	pointer->SetOwner(this);

	// Disable locomotion initially
	DisableLocomotion();
}

void ALocomotionTeleportation::SetControllingActor()
{
	if (ControllingActor == nullptr)
	{
		ControllingActor = Cast<AHand>(GetOwner());
	}
}

void ALocomotionTeleportation::DestinationRotationAdjustment(float amountFromThumbstickAxis)
{
	if (bLocomotionEnabled)
	{
		// Multiply by 180 since value is [-1,1] to achieve RotationalAdjustment
		CurrentRotationAdjustment = amountFromThumbstickAxis * 180.0;
	}
}

void ALocomotionTeleportation::EnableLocomotion()
{
	Super::EnableLocomotion();

	pointer->AdjustVisibility(true);
	DestinationMarker->SetVisibility(true, true);
}

void ALocomotionTeleportation::DisableLocomotion()
{
	Super::DisableLocomotion();

	pointer->AdjustVisibility(false);
	DestinationMarkerMesh->SetVisibility(false, true);
}

void ALocomotionTeleportation::UpdateDestinationMarker()
{

	FVector TraceLocation;
	TArray<FVector> Path;
	bool bHit = pointer->FindEndLocationAndPath(Path, TraceLocation);

	if (bHit)
	{
		DestinationMarkerMesh->SetVisibility(true);
		DestinationMarker->SetWorldLocation(TraceLocation);
		// Prohibit rotation of the destination marker despite the rotation of the trace line. 
		DestinationMarker->SetWorldRotation(FRotator(0.0, DestinationMarker->GetComponentRotation().Yaw, 0.0));

		pointer->DrawPath(Path);
		// Adjust the destination marker mesh locally rotated by the amount of the thumbstick 
		DestinationMarkerMesh->SetRelativeRotation(FRotator(0.0, CurrentRotationAdjustment, 0.0));
	}
	else
	{
		DestinationMarkerMesh->SetVisibility(false);
		// Need to draw an INVISIBLE spline if we need
		TArray <FVector> EmptyPath;
		pointer->DrawPath(EmptyPath);
	}
}

void ALocomotionTeleportation::DoLocomotion()
{
	Super::DoLocomotion();

	if (bLocomotionEnabled)
	{
		SetControllingActor();

		if (ControllingActor)
		{
			if (PlayerController)
			{
				PlayerController->PlayerCameraManager->StartCameraFade(0.f, 1.f, TeleportFadeTime, TeleportFadeColor);
				FTimerHandle Handle;
				GetWorldTimerManager().SetTimer(Handle, this, &ALocomotionTeleportation::TeleportToDestinationEnd, TeleportFadeTime);
			}
		}
	}
}

void ALocomotionTeleportation::TeleportToDestinationEnd()
{
	SetControllingActor();

	if (ControllingActor)
	{
		FVector Destination = DestinationMarker->GetComponentLocation();
		Destination += ControllingActor->ControllingCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * ControllingActor->ControllingCharacter->GetActorUpVector();
		ControllingActor->ControllingCharacter->SetActorLocation(Destination);

		// Set the VRRoot (which holds the camera component on the player pawn) orientation to match that of the DestinationMarkerMesh
		ControllingActor->ControllingCharacter->VRRoot->SetWorldRotation(DestinationMarkerMesh->GetComponentRotation());
	}
}


