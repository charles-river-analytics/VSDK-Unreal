// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "DefaultVirtuosoInputWrapper.h"
#include "IMotionController.h"
#include "Modules/ModuleManager.h"
#include "Runtime/InputDevice/Public/IInputDeviceModule.h"
#include "Runtime/InputDevice/Public/IInputDevice.h"
#include "VirtuosoTrackingState.h"
#include "VirtuosoHandState.h"
#include "XRMotionControllerBase.h"

UDefaultVirtuosoInputWrapper::UDefaultVirtuosoInputWrapper()
{
}

UDefaultVirtuosoInputWrapper::~UDefaultVirtuosoInputWrapper()
{
}

UVirtuosoHandState* UDefaultVirtuosoInputWrapper::GetInput_Implementation(VirtuosoHandId HandId)
{
	// TODO wrap basic controller input functionality
	return nullptr;
}

UVirtuosoTrackingState* UDefaultVirtuosoInputWrapper::GetTrackingState_Implementation(VirtuosoHandId HandId)
{
	TArray<IMotionController*> MotionControllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());
	FName MotionSource = (HandId == VirtuosoHandId::Left) ? FXRMotionControllerBase::LeftHandSourceId : FXRMotionControllerBase::RightHandSourceId;
	UVirtuosoTrackingState* TrackingState = NewObject<UVirtuosoTrackingState>();

	for (IMotionController* MotionController : MotionControllers)
	{
		if (MotionController != nullptr)
		{
			TrackingState->TrackingStatus = MotionController->GetControllerTrackingStatus(
				0,
				MotionSource
			);
			if (TrackingState->TrackingStatus == ETrackingStatus::Tracked)
			{
				MotionController->GetControllerOrientationAndPosition(
					0,
					MotionSource,
					TrackingState->Rotation,
					TrackingState->Position, 
					1.0f // TODO world scale
				);
			}
			return TrackingState;
		}
	}
	return nullptr;
}
