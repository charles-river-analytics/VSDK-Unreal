// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "InteractableAxisControl.h"

UInteractableAxisControl::UInteractableAxisControl()
{
	PrimaryComponentTick.TickGroup = TG_LastDemotable;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UInteractableAxisControl::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		StartingPosition = GetOwner()->GetActorLocation();

		SetupStartValues();
	}
}

void UInteractableAxisControl::OnComponentCreated()
{
	Super::OnComponentCreated();

	if (GetOwner() != nullptr)
	{
		PhysicsComponent = Cast<UPrimitiveComponent>(GetOwner()->GetComponentByClass(UPrimitiveComponent::StaticClass()));

		if (PhysicsComponent)
		{
			SetupAxesConstraints();
		}
	}
}

/** UActorComponent Overrides */
void UInteractableAxisControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MaintainAxesConstraints();
}

float UInteractableAxisControl::Normalize(int axis, float value)
{
	return 0.0f;
}

float UInteractableAxisControl::GetAbsoluteFromNormalize(int axis, float normalizedValue)
{
	return 0.0f;
}

void UInteractableAxisControl::MoveOverTime()
{
}

void UInteractableAxisControl::CheckLimits(int axis, float value)
{
}

void UInteractableAxisControl::SetupAxesConstraints()
{
}

void UInteractableAxisControl::SetupStartValues()
{
}

void UInteractableAxisControl::SetAxisValue(int axis, int value, bool teleport)
{
}

void UInteractableAxisControl::MaintainAxesConstraints()
{
}