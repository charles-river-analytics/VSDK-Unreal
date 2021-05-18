// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "VirtuosoInput.h"
#include "VirtuosoInputDevice.h"
#include "DefaultVirtuosoInputWrapper.h"

DEFINE_LOG_CATEGORY_STATIC(VirtuosoTopLogCategory, Log, All);

#define LOCTEXT_NAMESPACE "FVirtuosoInputModule"

void FVirtuosoInputModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	VirtuosoInput::VirtuosoInputDevice::InitializeVirtuosoInput();
	RegisteredInputWrappers.Reset();
	CurrentInputWrapperName = "";
	CurrentTrackingWrapperName = "";
	IModularFeatures::Get().RegisterModularFeature(GetModularFeatureName(), this);
	UE_LOG(VirtuosoTopLogCategory, Log, TEXT("Virtuoso Input Module Started"));
}

void FVirtuosoInputModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(VirtuosoTopLogCategory, Log, TEXT("Virtuoso Input Module Stopped"));
	RegisteredInputWrappers.Reset();
	IModularFeatures::Get().UnregisterModularFeature(GetModularFeatureName(), this);
}

TSharedPtr<IInputDevice> FVirtuosoInputModule::CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	VirtuosoInputDevice = TSharedPtr<IInputDevice>(new VirtuosoInput::VirtuosoInputDevice(InMessageHandler));
	
	if (VirtuosoInputDevice && CurrentInputWrapperName != "")
	{
		SetInputWrapper(CurrentInputWrapperName);
	}

	if (VirtuosoInputDevice && CurrentTrackingWrapperName != "")
	{
		SetTrackingWrapper(CurrentTrackingWrapperName);
	}
	
	return VirtuosoInputDevice;

}


void FVirtuosoInputModule::RegisterInputWrapper(FName WrapperName, UObject* InputWrapper)
{
	if (InputWrapper == nullptr)
	{
		return;
	}

	if (InputWrapper->Implements<UVirtuosoInputWrapper>())
	{
		RegisteredInputWrappers.Add(WrapperName, InputWrapper);
	}
	
}

void FVirtuosoInputModule::UnRegisterInputWrapper(FName WrapperName)
{
	if (RegisteredInputWrappers.Contains(WrapperName))
	{
		RegisteredInputWrappers.Remove(WrapperName);
		if ((CurrentInputWrapperName == WrapperName 
			|| CurrentTrackingWrapperName == WrapperName) && VirtuosoInputDevice != nullptr)
		{
			TSharedPtr<VirtuosoInput::VirtuosoInputDevice> InputDevice =
				StaticCastSharedPtr<VirtuosoInput::VirtuosoInputDevice>(VirtuosoInputDevice);
			InputDevice->SetInputWrapper(nullptr);
		}
	}
}

bool FVirtuosoInputModule::SetInputWrapper(FName WrapperName)
{
	if (RegisteredInputWrappers.Contains(WrapperName))
	{
		UObject* InputWrapper = RegisteredInputWrappers[WrapperName];
		if (InputWrapper != nullptr)
		{
			CurrentInputWrapperName = WrapperName;
			TSharedPtr<VirtuosoInput::VirtuosoInputDevice> InputDevice =
				StaticCastSharedPtr<VirtuosoInput::VirtuosoInputDevice>(VirtuosoInputDevice);
			if (InputDevice)
			{
				InputDevice->SetInputWrapper(InputWrapper);
				return true;
			}
		}
	}
	
	return false;
}

bool FVirtuosoInputModule::SetTrackingWrapper(FName WrapperName)
{
	if (RegisteredInputWrappers.Contains(WrapperName))
	{
		UObject* TrackingWrapper = RegisteredInputWrappers[WrapperName];
		if (TrackingWrapper != nullptr)
		{
			CurrentTrackingWrapperName = WrapperName;
			TSharedPtr<VirtuosoInput::VirtuosoInputDevice> InputDevice =
				StaticCastSharedPtr<VirtuosoInput::VirtuosoInputDevice>(VirtuosoInputDevice);
			if (InputDevice)
			{
				InputDevice->SetTrackingWrapper(TrackingWrapper);
				return true;
			}
		}
	}
	return false;
}

TSharedPtr<VirtuosoInput::VirtuosoInputDevice> FVirtuosoInputModule::GetVirtuosoInputDevice()
{
	if (VirtuosoInputDevice == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<VirtuosoInput::VirtuosoInputDevice> InputDevice =
		StaticCastSharedPtr<VirtuosoInput::VirtuosoInputDevice>(VirtuosoInputDevice);
	return InputDevice;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVirtuosoInputModule, VirtuosoInput)