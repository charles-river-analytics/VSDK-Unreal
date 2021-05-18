// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "HapticInteractableComponent.h"
#include "Haptics/HapticFeedbackEffect_Base.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "VirtuosoHapticsManager.h"

UHapticInteractableComponent::UHapticInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHapticInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	HapticsManager = nullptr;
	// ...
	
}

void UHapticInteractableComponent::SetSelectingHand(VirtuosoHandId HandId)
{
	CurrentSelectingHand = HandId;
}

void UHapticInteractableComponent::PlaySelectEffect()
{
	if (!SelectEffect) { return; }
	FindHapticsManager();
	if (HapticsManager)
	{
		HapticsManager->PlayHapticEffect(SelectEffect, CurrentSelectingHand);
	}
}

void UHapticInteractableComponent::PlayDeselectEffect()
{
	if (!DeselectEffect) { return; }
	FindHapticsManager();
	if (HapticsManager)
	{
		HapticsManager->PlayHapticEffect(DeselectEffect, CurrentSelectingHand);
	}
}

void UHapticInteractableComponent::PlayGrabEffect()
{
	if (!GrabEffect) { return; }
	FindHapticsManager();
	if (HapticsManager)
	{
		HapticsManager->PlayHapticEffect(GrabEffect, CurrentSelectingHand);
	}
}

void UHapticInteractableComponent::PlayUngrabEffect()
{
	if (!UngrabEffect) { return; }
	FindHapticsManager();
	if (HapticsManager)
	{
		HapticsManager->PlayHapticEffect(UngrabEffect, CurrentSelectingHand);
	}
}

void UHapticInteractableComponent::PlayUseEffect()
{
	if (!UseEffect) { return; }
	FindHapticsManager();
	if (HapticsManager)
	{
		HapticsManager->PlayHapticEffect(UseEffect, CurrentSelectingHand);
	}
}

void UHapticInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHapticInteractableComponent::FindHapticsManager()
{
	if (HapticsManager != nullptr)
	{
		return;
	}

	TArray<AActor*> AvailableHapticManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVirtuosoHapticsManager::StaticClass(), AvailableHapticManagers);
	if (AvailableHapticManagers.Num() > 0)
	{
		HapticsManager = (AVirtuosoHapticsManager*)AvailableHapticManagers[0];
	}
	else
	{
		HapticsManager = nullptr;
	}
}



