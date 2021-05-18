// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "VirtuosoHapticsManager.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"

AVirtuosoHapticsManager::AVirtuosoHapticsManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AVirtuosoHapticsManager::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void AVirtuosoHapticsManager::PlayHapticEffect(class UHapticFeedbackEffect_Base* HapticPayload, VirtuosoHandId HapticLocation)
{
	if (HapticPayload != nullptr && HapticPayload != nullptr && PlayerController != nullptr)
	{
		EControllerHand controllerHand = HapticLocation == VirtuosoHandId::Left ? EControllerHand::Left : EControllerHand::Right;
		PlayerController->PlayHapticEffect(HapticPayload, controllerHand);
	}
}


