// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "VirtuosoMotionController.h"
#include "VirtuosoInput.h"
#include "VirtuosoInputDevice.h"
#include "Engine/World.h"

using namespace VirtuosoInput;

UVirtuosoMotionController::UVirtuosoMotionController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UVirtuosoMotionController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (VirtuosoInputDev != nullptr && VirtuosoInputDev.IsValid())
	{
		float WorldToMeters = GetWorldToMetersScalar();
		TrackingStatus = VirtuosoInputDev->GetControllerTrackingStatus(MotionSource);
		FVector Position;
		FRotator Rotation;
		bool TrackingSuccess = VirtuosoInputDev->GetControllerOrientationAndPosition(
			MotionSource,
			Rotation,
			Position,
			WorldToMeters
		);
		if (TrackingSuccess)
		{
			SetRelativeLocationAndRotation(Position, Rotation);
		}
	}
	else
	{
		TrackingStatus = ETrackingStatus::NotTracked;
		FVirtuosoInputModule& VirtuosoInputModule = FVirtuosoInputModule::Get();
		if (!VirtuosoInputModule.IsAvailable())
		{
			return;
		}
		VirtuosoInputDev = FVirtuosoInputModule::Get().GetVirtuosoInputDevice();
	}
}

float UVirtuosoMotionController::GetWorldToMetersScalar()
{
	return GetWorld() ? GetWorld()->GetWorldSettings()->WorldToMeters : 100.0f;
}

ETrackingStatus UVirtuosoMotionController::GetTrackingStatus()
{
	return TrackingStatus;
}

VirtuosoHandId UVirtuosoMotionController::GetMotionSource()
{
	return MotionSource;
}

void UVirtuosoMotionController::SetMotionSource(VirtuosoHandId HandId)
{
	MotionSource = HandId;
}

