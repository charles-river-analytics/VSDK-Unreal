// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Runtime/InputDevice/Public/IInputDeviceModule.h"
#include "Runtime/InputDevice/Public/IInputDevice.h"
#include "VirtuosoInputCommon.h"
#include "VirtuosoInputDevice.h"
#include "VirtuosoInputWrapper.h"


/**
*	Controls the Virtuoso input module by doing several things:
*	- Implements the IInputDeviceModule interface to communicate with Unreal Engine 
*		that it can provide input
*	- Manages an Input Device to provide to Unreal Engine at runtime
*	- Manages Input Wrappers that provide input data to the input device
*
*	Contributors: Dan Duggan (dduggan@cra.com) Updated: August 2020
*/
class FVirtuosoInputModule : public IInputDeviceModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("VirtuosoInput");
	}

	static inline FVirtuosoInputModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FVirtuosoInputModule>("VirtuosoInput");
	}

	/** IInputDeviceModule implementation */
	virtual TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);

	/* Registers a VirtuosoInputWrapper for potential use */
	void RegisterInputWrapper(FName WrapperName, UObject* InputWrapper);

	/* Removes a VirtuosoInputWrapper from the available wrapper list */
	void UnRegisterInputWrapper(FName WrapperName);

	/* Sets the current Virtuoso Input Wrapper. Wrapper must already be registered! */
	bool SetInputWrapper(FName WrapperName);

	bool SetTrackingWrapper(FName TrackingWrapperName);

	TSharedPtr<VirtuosoInput::VirtuosoInputDevice> GetVirtuosoInputDevice();

private:
	TSharedPtr<IInputDevice> VirtuosoInputDevice;

	TMap<FName, UObject*> RegisteredInputWrappers;

	FName CurrentInputWrapperName;

	FName CurrentTrackingWrapperName;

};
