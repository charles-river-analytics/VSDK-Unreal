// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "Hand.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <MotionControllerComponent.h>
#include <MotionTrackedDeviceFunctionLibrary.generated.h>
#include <VirtuosoInput/Public/VirtuosoMotionController.h>

DEFINE_LOG_CATEGORY_STATIC(VirtuosoHandCat, Log, All);

// Sets default values
AHand::AHand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don'checkInteractableGrab need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UVirtuosoMotionController>(TEXT("VirtuosoMotionController"));
	SetRootComponent(MotionController);
	MotionController->SetMotionSource(VirtuosoHandId::Left);

	HandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(GetRootComponent());
	// TODO: Force Set to overlap all dynamic
	HandMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	CurrentSelectedObject = nullptr;
	CurrentSelectedInteractableGrab = nullptr;
	CurrentSelectedInteractableUse = nullptr;
}

void AHand::SetHand(EControllerHand HandToSet)
{
	Hand = HandToSet;

	VirtuosoHandId HandId = (Hand == EControllerHand::Left) ? VirtuosoHandId::Left : VirtuosoHandId::Right;

	if (MotionController)
	{
		MotionController->SetMotionSource(HandId);
	}
}

void AHand::Grab()
{
	if (CurrentSelectedInteractableGrab)
	{
		CurrentSelectedInteractableGrab->Grab(this);
		OnHandGrab.Broadcast(this, CurrentSelectedObject);
	}
}

void AHand::DropCurrent()
{
	if (CurrentSelectedInteractableGrab)
	{
		CurrentSelectedInteractableGrab->Ungrab(this);
		OnHandUnGrab.Broadcast(this, CurrentSelectedObject);
	}
}

void AHand::Use()
{
	if (CurrentSelectedInteractableUse)
	{
		CurrentSelectedInteractableUse->Use(this);
		OnHandUse.Broadcast(this, CurrentSelectedObject);
	}
}

void AHand::StopUse()
{
	if (CurrentSelectedInteractableUse)
	{
		CurrentSelectedInteractableUse->StopUse(this);
		OnHandStopUse.Broadcast(this, CurrentSelectedObject);
	}
}

void AHand::OnInteractableBeginSelect(AInteractableObject* SelectedObject)
{
	// Do not select a new object if one is already selected
	if (CurrentSelectedObject == nullptr)
	{
		CurrentSelectedObject = SelectedObject;

		UInteractableComponent* checkInteractableGrab = CurrentSelectedObject->GetInteractableComponent(FName("Grab"));

		if (checkInteractableGrab->IsA(UInteractableGrab::StaticClass()))
		{
			CurrentSelectedInteractableGrab = Cast<UInteractableGrab>(checkInteractableGrab);
		}

		UInteractableComponent* checkInteractableUse = CurrentSelectedObject->GetInteractableComponent(FName("Use"));

		if (checkInteractableUse->IsA(UInteractableUse::StaticClass()))
		{
			CurrentSelectedInteractableUse = Cast<UInteractableUse>(checkInteractableUse);
		}

		OnHandSelect.Broadcast(this, CurrentSelectedObject);
	}
}

void AHand::OnInteractableEndSelect(AInteractableObject* DeselectedObject)
{
	if (DeselectedObject == CurrentSelectedObject)
	{
		DropCurrent();

		StopUse();

		CurrentSelectedObject = nullptr;
		CurrentSelectedInteractableGrab = nullptr;
		CurrentSelectedInteractableUse = nullptr;

		OnHandDeselect.Broadcast(this, DeselectedObject);
	}
}