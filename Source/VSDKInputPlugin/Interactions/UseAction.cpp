// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "UseAction.h"

UUseAction::UUseAction()
{
}

void UUseAction::SetInteractableUse(UInteractableUse* ActionUse)
{
	InteractableUse = ActionUse;
}

UInteractableUse * UUseAction::GetInteractableUse()
{
	return InteractableUse;
}

void UUseAction::TryUse_Implementation(AActor* UsingActor)
{
}

void UUseAction::TryUnuse_Implementation(AActor* UnusingActor)
{
}