#pragma once
// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "Runtime/InputDevice/Public/IInputDevice.h"
#include "Runtime/InputCore/Public/InputCore.h"
#include "XRMotionControllerBase.h"
#include "VirtuosoInputCommon.h"
#include "VirtuosoHandState.h"
#include "VirtuosoInputWrapper.h"


namespace VirtuosoInput
{
	/*
		This class acts as a virtual input device, polling and monitoring hand/controller state through an Input API Wrapper,
		and generating Action/Axis events/updates for the Unreal Input system.

		Contributors: Dan Duggan (dduggan@cra.com) Updated: August 2020
	*/
	class VirtuosoInputDevice : public IInputDevice
	{
	public:

		VirtuosoInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);
		~VirtuosoInputDevice();

		/** IInputDevice Overrides */
		virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);
		virtual void Tick(float deltaTime) override;
		virtual bool Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar) override;
		virtual void SendControllerEvents() override;
		virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
		virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override;

		
		/** Retrieves the Orientation and Position of the specified controller/hand, if available.
		*  Returns true if the data is available and false otherwise.	
		*/
		virtual bool GetControllerOrientationAndPosition(
			const VirtuosoHandId HandId,
			FRotator& OutOrientation,
			FVector& OutPosition,
			float WorldToMetersScale
		) const;
		
		/** Returns the tracking status of the hand. NotTracked is also returned if no tracking wrapper is available.*/
		virtual ETrackingStatus GetControllerTrackingStatus(
			const VirtuosoHandId HandId
		) const;

		/** Virtuoso Input Device-specific methods */
		
		/** Changes the current input API wrapper */
		virtual void SetInputWrapper(UObject* InInputWrapper);

		/** Changes the current motion tracking API wrapper */
		virtual void SetTrackingWrapper(UObject* InTrackingWrapper);

		/** Static method for handling setup when the module is initialized. */
		static void InitializeVirtuosoInput();

	private:

		/** Helper method to process changes in a particular button's state */
		void ProcessButtonState(
			VirtuosoButtonState Previous, 
			VirtuosoButtonState Current, 
			FName ControllerButtonNamePress,
			FName ControllerButtonNameTouch
		);

		/** Helper method to process changes in a particular axis' state */
		void ProcessAxisState(
			FVector2D Previous,
			FVector2D Current,
			FName AxisName,
			FName AxisXName,
			FName AxisYName
		);

		TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
		UObject* InputWrapper;
		UObject* TrackingWrapper;
		UVirtuosoHandState* LeftHandStatePreviousState;
		UVirtuosoHandState* RightHandStatePreviousState;

		/* Method to assist with Virtuoso system setup */
		static void InitializeVirtuosoKeys();
	};
}