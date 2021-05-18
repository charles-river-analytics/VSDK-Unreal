// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "SimpleHapticEffect.h"
#include "VirtuosoHapticsManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
USimpleHapticEffect::USimpleHapticEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USimpleHapticEffect::BeginPlay()
{
	Super::BeginPlay();
	FindHapticsManager();
	// ...
	
}


void USimpleHapticEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (HapticsManager == nullptr)
	{
		FindHapticsManager();
	}
}

void USimpleHapticEffect::PlayHaptics()
{
	if (HapticsManager && HapticPayload)
	{
		HapticsManager->PlayHapticEffect(HapticPayload, HapticLocation);
	}
}

AVirtuosoHapticsManager* USimpleHapticEffect::FindHapticsManager()
{
	TArray<AActor*> AvailableHapticManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVirtuosoHapticsManager::StaticClass(), AvailableHapticManagers);
	if (AvailableHapticManagers.Num() > 0)
	{
		HapticsManager = (AVirtuosoHapticsManager*) AvailableHapticManagers[0];
		return HapticsManager;
	}
	HapticsManager = nullptr;
	return nullptr;
}

