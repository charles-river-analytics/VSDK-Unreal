// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "LocomotionBase.h"
#include <GameFramework/PlayerController.h>

ALocomotionBase::ALocomotionBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALocomotionBase::BeginPlay()
{
	Super::BeginPlay();

	// Bind input!
	PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()->GetPawn()->GetController());

	if (PlayerController)
	{
		EnableInput(PlayerController);
	}
}

void ALocomotionBase::DoLocomotion()
{
	// No op - overridden by children
}

void ALocomotionBase::EnableLocomotion()
{
	bLocomotionEnabled = true;
}

void ALocomotionBase::DisableLocomotion()
{
	bLocomotionEnabled = false;
}