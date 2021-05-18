#include "VirtuosoInputDevice.h"
#include "VirtuosoTrackingState.h"
#include "Features/IModularFeatures.h"

using namespace VirtuosoInput;

#define LOCTEXT_NAMESPACE "VirtuosoInputDevice"

DEFINE_LOG_CATEGORY_STATIC(VirtuosoLogCategory, Log, All);

VirtuosoInputDevice::VirtuosoInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
	: MessageHandler(InMessageHandler)
{
	TrackingWrapper = nullptr;
	InputWrapper = nullptr;
	LeftHandStatePreviousState = NewObject<UVirtuosoHandState>();
	RightHandStatePreviousState = NewObject<UVirtuosoHandState>();
}

VirtuosoInputDevice::~VirtuosoInputDevice()
{
	// no clean-up for now
}

/** IInputDevice Overrides */

void VirtuosoInputDevice::SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

void VirtuosoInputDevice::Tick(float deltaTime)
{
	// Processing is done in "SendControllerEvents"
}

bool VirtuosoInputDevice::Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar)
{
	// No Cmds implemented
	return false;
}

void VirtuosoInputDevice::SendControllerEvents()
{
	UVirtuosoHandState* LeftHandStateCurrentState;
	UVirtuosoHandState* RightHandStateCurrentState;
	if (InputWrapper != nullptr && InputWrapper->IsValidLowLevel())
	{
		LeftHandStateCurrentState = IVirtuosoInputWrapper::Execute_GetInput(InputWrapper, VirtuosoHandId::Left);
		RightHandStateCurrentState = IVirtuosoInputWrapper::Execute_GetInput(InputWrapper, VirtuosoHandId::Right);
	}
	else
	{
		return;
	}
	
	// TODO controller ID - Unreal Engine assigns controller IDs to different devices which should be sent via the input message handler,
	// but it isn't essential in VR since typically only one player is playing at a time

	ProcessButtonState(
		LeftHandStatePreviousState->TriggerButton, 
		LeftHandStateCurrentState->TriggerButton, 
		VirtuosoKeys::VirtuosoLeftTriggerPress.GetFName(), 
		VirtuosoKeys::VirtuosoLeftTriggerTouch.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->TriggerButton,
		RightHandStateCurrentState->TriggerButton,
		VirtuosoKeys::VirtuosoRightTriggerPress.GetFName(),
		VirtuosoKeys::VirtuosoRightTriggerTouch.GetFName()
	);

	ProcessButtonState(
		LeftHandStatePreviousState->GripButton,
		LeftHandStateCurrentState->GripButton,
		VirtuosoKeys::VirtuosoLeftGripPress.GetFName(),
		VirtuosoKeys::VirtuosoLeftGripTouch.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->GripButton,
		RightHandStateCurrentState->GripButton,
		VirtuosoKeys::VirtuosoRightGripPress.GetFName(),
		VirtuosoKeys::VirtuosoRightGripTouch.GetFName()
	);

	ProcessButtonState(
		LeftHandStatePreviousState->AButton,
		LeftHandStateCurrentState->AButton,
		VirtuosoKeys::VirtuosoLeftAPress.GetFName(),
		VirtuosoKeys::VirtuosoLeftATouch.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->AButton,
		RightHandStateCurrentState->AButton,
		VirtuosoKeys::VirtuosoRightAPress.GetFName(),
		VirtuosoKeys::VirtuosoRightATouch.GetFName()
	);

	ProcessButtonState(
		LeftHandStatePreviousState->BButton,
		LeftHandStateCurrentState->BButton,
		VirtuosoKeys::VirtuosoLeftBPress.GetFName(),
		VirtuosoKeys::VirtuosoLeftBTouch.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->BButton,
		RightHandStateCurrentState->BButton,
		VirtuosoKeys::VirtuosoRightBPress.GetFName(),
		VirtuosoKeys::VirtuosoRightBTouch.GetFName()
	);

	ProcessButtonState(
		LeftHandStatePreviousState->MenuButton,
		LeftHandStateCurrentState->MenuButton,
		VirtuosoKeys::VirtuosoLeftMenuPress.GetFName(),
		VirtuosoKeys::VirtuosoLeftMenuTouch.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->MenuButton,
		RightHandStateCurrentState->MenuButton,
		VirtuosoKeys::VirtuosoRightMenuPress.GetFName(),
		VirtuosoKeys::VirtuosoRightMenuTouch.GetFName()
	);

	ProcessButtonState(
		LeftHandStatePreviousState->JoystickButton,
		LeftHandStateCurrentState->JoystickButton,
		VirtuosoKeys::VirtuosoLeftJoystickPress.GetFName(),
		VirtuosoKeys::VirtuosoLeftJoystickTouch.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->JoystickButton,
		RightHandStateCurrentState->JoystickButton,
		VirtuosoKeys::VirtuosoRightJoystickPress.GetFName(),
		VirtuosoKeys::VirtuosoRightJoystickTouch.GetFName()
	);

	ProcessButtonState(
		LeftHandStatePreviousState->DpadUp,
		LeftHandStateCurrentState->DpadUp,
		VirtuosoKeys::VirtuosoLeftDpadUp.GetFName(),
		VirtuosoKeys::VirtuosoLeftDpadUp.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->DpadUp,
		RightHandStateCurrentState->DpadUp,
		VirtuosoKeys::VirtuosoRightDpadUp.GetFName(),
		VirtuosoKeys::VirtuosoRightDpadUp.GetFName()
	);

	ProcessButtonState(
		LeftHandStatePreviousState->DpadDown,
		LeftHandStateCurrentState->DpadDown,
		VirtuosoKeys::VirtuosoLeftDpadDown.GetFName(),
		VirtuosoKeys::VirtuosoLeftDpadDown.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->DpadDown,
		RightHandStateCurrentState->DpadDown,
		VirtuosoKeys::VirtuosoRightDpadDown.GetFName(),
		VirtuosoKeys::VirtuosoRightDpadDown.GetFName()
	);

	ProcessButtonState(
		LeftHandStatePreviousState->DpadLeft,
		LeftHandStateCurrentState->DpadLeft,
		VirtuosoKeys::VirtuosoLeftDpadLeft.GetFName(),
		VirtuosoKeys::VirtuosoLeftDpadLeft.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->DpadLeft,
		RightHandStateCurrentState->DpadLeft,
		VirtuosoKeys::VirtuosoRightDpadLeft.GetFName(),
		VirtuosoKeys::VirtuosoRightDpadLeft.GetFName()
	);

	ProcessButtonState(
		LeftHandStatePreviousState->DpadRight,
		LeftHandStateCurrentState->DpadRight,
		VirtuosoKeys::VirtuosoLeftDpadRight.GetFName(),
		VirtuosoKeys::VirtuosoLeftDpadRight.GetFName()
	);

	ProcessButtonState(
		RightHandStatePreviousState->DpadRight,
		RightHandStateCurrentState->DpadRight,
		VirtuosoKeys::VirtuosoRightDpadRight.GetFName(),
		VirtuosoKeys::VirtuosoRightDpadRight.GetFName()
	);

	ProcessAxisState(
		LeftHandStatePreviousState->JoystickAxis,
		LeftHandStateCurrentState->JoystickAxis,
		VirtuosoKeys::VirtuosoLeftJoystickAxis.GetFName(),
		VirtuosoKeys::VirtuosoLeftJoystickXAxis.GetFName(),
		VirtuosoKeys::VirtuosoLeftJoystickYAxis.GetFName()
	);

	ProcessAxisState(
		RightHandStatePreviousState->JoystickAxis,
		RightHandStateCurrentState->JoystickAxis,
		VirtuosoKeys::VirtuosoRightJoystickAxis.GetFName(),
		VirtuosoKeys::VirtuosoRightJoystickXAxis.GetFName(),
		VirtuosoKeys::VirtuosoRightJoystickYAxis.GetFName()
	);

	LeftHandStatePreviousState->CopyValues(LeftHandStateCurrentState);
	RightHandStatePreviousState->CopyValues(RightHandStateCurrentState);
}

void VirtuosoInputDevice::ProcessButtonState(
	VirtuosoButtonState Previous, 
	VirtuosoButtonState Current, 
	FName ControllerButtonNamePress,
	FName ControllerButtonNameTouch)
{
	if (Current != Previous)
	{
		switch (Current)
		{
		case VirtuosoButtonState::Pressed:
		{
			bool success = MessageHandler->OnControllerButtonPressed(ControllerButtonNamePress, 0, false);
			if (!success)
			{
				UE_LOG(VirtuosoLogCategory, Error, TEXT("Failed to propogate controller event!"));
			}
			break;
		}
		case VirtuosoButtonState::Touched:
		{
			if (Previous == VirtuosoButtonState::Pressed)
			{
				MessageHandler->OnControllerButtonReleased(ControllerButtonNamePress, 0, false);
			}
			else
			{
				MessageHandler->OnControllerButtonPressed(ControllerButtonNameTouch, 0, false);
			}
			break;
		}
		case VirtuosoButtonState::Unpressed:
		{
			if (Previous == VirtuosoButtonState::Pressed)
			{
				MessageHandler->OnControllerButtonReleased(ControllerButtonNamePress, 0, false);
			}
			else
			{
				MessageHandler->OnControllerButtonReleased(ControllerButtonNameTouch, 0, false);
			}
			break;
		}
		}
	}
}

void VirtuosoInputDevice::ProcessAxisState(
	FVector2D Previous, 
	FVector2D Current, 
	FName AxisName, 
	FName AxisXName, 
	FName AxisYName)
{
	// TODO primary axis update; for some reason this isn't an option in the message handler
	MessageHandler->OnControllerAnalog(AxisXName, 0, Current.X);
	MessageHandler->OnControllerAnalog(AxisYName, 0, Current.Y);
}

void VirtuosoInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	// Not yet implemented
}

void VirtuosoInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values)
{
	// Not yet implemented
}

/* Motion Input State Methods */

bool VirtuosoInputDevice::GetControllerOrientationAndPosition(
	VirtuosoHandId HandId,
	FRotator& OutOrientation,
	FVector& OutPosition,
	float WorldToMetersScale
) const
{
	if (TrackingWrapper != nullptr && TrackingWrapper->IsValidLowLevel())
	{
		UVirtuosoTrackingState* TrackingState = IVirtuosoInputWrapper::Execute_GetTrackingState(TrackingWrapper, HandId);
		if (!TrackingState || TrackingState->TrackingStatus != ETrackingStatus::Tracked)
		{
			return false;
		}
		OutOrientation = TrackingState->Rotation;
		OutPosition = WorldToMetersScale * TrackingState->Position;
		return true;
	}
	return false;
}

ETrackingStatus VirtuosoInputDevice::GetControllerTrackingStatus(
	VirtuosoHandId HandId
) const
{                                                       
	if (TrackingWrapper != nullptr && TrackingWrapper->IsValidLowLevel())
	{
		UVirtuosoTrackingState* TrackingState = IVirtuosoInputWrapper::Execute_GetTrackingState(TrackingWrapper, HandId);
		if (!TrackingState)
		{
			return ETrackingStatus::NotTracked;
		}
		return TrackingState->TrackingStatus;
	}
	return ETrackingStatus::NotTracked;
}

void VirtuosoInputDevice::SetInputWrapper(UObject* InInputWrapper)
{
	InputWrapper = InInputWrapper;
}

void VirtuosoInputDevice::SetTrackingWrapper(UObject* InTrackingWrapper)
{
	TrackingWrapper = InTrackingWrapper;
}


/* Handles set up of Virtuoso Input Devices, including key mappings for Unreal */
void VirtuosoInputDevice::InitializeVirtuosoInput()
{
	InitializeVirtuosoKeys();
}

// Initializes Virtuoso Input Keys and updates Unreal Engine Input system accordingly
void VirtuosoInputDevice::InitializeVirtuosoKeys()
{
	EKeys::AddMenuCategoryDisplayInfo("VirtuosoInput", LOCTEXT("VirtuosoInputSubCategory", "Virtuoso Input"), TEXT("GraphEditor.PadEvent_16x"));

	// Trigger
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftTriggerPress, LOCTEXT("VirtuosoLeftTriggerPress", "Virtuoso (L) Trigger Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftTriggerTouch, LOCTEXT("VirtuosoLeftTriggerTouch", "Virtuoso (L) Trigger Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightTriggerPress, LOCTEXT("VirtuosoRightTriggerPress", "Virtuoso (R) Trigger Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightTriggerTouch, LOCTEXT("VirtuosoRightTriggerTouch", "Virtuoso (R) Trigger Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));

	// Grip
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftGripPress, LOCTEXT("VirtuosoLeftGripPress", "Virtuoso (L) Grip Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftGripTouch, LOCTEXT("VirtuosoLeftGripTouch", "Virtuoso (L) Grip Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightGripPress, LOCTEXT("VirtuosoRightGripPress", "Virtuoso (R) Grip Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightGripTouch, LOCTEXT("VirtuosoRightGripTouch", "Virtuoso (R) Grip Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));

	// Buttons
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftAPress, LOCTEXT("VirtuosoLeftAPress", "Virtuoso (L) A Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftATouch, LOCTEXT("VirtuosoLeftATouch", "Virtuoso (L) A Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftBPress, LOCTEXT("VirtuosoLeftBPress", "Virtuoso (L) B Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftBTouch, LOCTEXT("VirtuosoLeftBTouch", "Virtuoso (L) B Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftMenuPress, LOCTEXT("VirtuosoLeftMenuPress", "Virtuoso (L) Menu Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftMenuTouch, LOCTEXT("VirtuosoLeftMenuTouch", "Virtuoso (L) Menu Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightAPress, LOCTEXT("VirtuosoRightAPress", "Virtuoso (R) A Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightATouch, LOCTEXT("VirtuosoRightATouch", "Virtuoso (R) A Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightBPress, LOCTEXT("VirtuosoRightBPress", "Virtuoso (R) B Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightBTouch, LOCTEXT("VirtuosoRightBTouch", "Virtuoso (R) B Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightMenuPress, LOCTEXT("VirtuosoRightMenuPress", "Virtuoso (R) Menu Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightMenuTouch, LOCTEXT("VirtuosoRightMenuTouch", "Virtuoso (R) Menu Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));

	// Joystick Click
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftJoystickPress, LOCTEXT("VirtuosoLeftJoystickPress", "Virtuoso (L) Joystick Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftJoystickTouch, LOCTEXT("VirtuosoLeftJoystickTouch", "Virtuoso (L) Joystick Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightJoystickPress, LOCTEXT("VirtuosoRightJoystickPress", "Virtuoso (R) Joystick Press"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightJoystickTouch, LOCTEXT("VirtuosoRightJoystickTouch", "Virtuoso (R) Joystick Touch"), FKeyDetails::GamepadKey, "VirtuosoInput"));

	// Joystick Axes
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftJoystickXAxis, LOCTEXT("VirtuosoLeftJoystickXAxis", "Virtuoso (L) Joystick X Axis"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftJoystickYAxis, LOCTEXT("VirtuosoLeftJoystickYAxis", "Virtuoso (L) Joystick Y Axis"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftJoystickAxis, LOCTEXT("VirtuosoLeftJoystickAxis", "Virtuoso (L) Joystick Axis"), FKeyDetails::GamepadKey | FKeyDetails::VectorAxis, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightJoystickXAxis, LOCTEXT("VirtuosoRightJoystickXAxis", "Virtuoso (R) Joystick X Axis"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightJoystickYAxis, LOCTEXT("VirtuosoRightJoystickYAxis", "Virtuoso (R) Joystick Y Axis"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightJoystickAxis, LOCTEXT("VirtuosoRightJoystickAxis", "Virtuoso (R) Joystick Axis"), FKeyDetails::GamepadKey | FKeyDetails::VectorAxis, "VirtuosoInput"));

	// Joystick Dpad
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftDpadUp, LOCTEXT("VirtuosoLeftDpadUp", "Virtuoso (L) Dpad Up"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftDpadDown, LOCTEXT("VirtuosoLeftDpadDown", "Virtuoso (L) Dpad Down"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftDpadLeft, LOCTEXT("VirtuosoLeftDpadLeft", "Virtuoso (L) Dpad Left"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoLeftDpadRight, LOCTEXT("VirtuosoLeftDpadRight", "Virtuoso (L) Dpad Right"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightDpadUp, LOCTEXT("VirtuosoRightDpadUp", "Virtuoso (R) Dpad Up"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightDpadDown, LOCTEXT("VirtuosoRightDpadDown", "Virtuoso (R) Dpad Down"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightDpadLeft, LOCTEXT("VirtuosoRightDpadLeft", "Virtuoso (R) Dpad Left"), FKeyDetails::GamepadKey, "VirtuosoInput"));
	EKeys::AddKey(FKeyDetails(VirtuosoKeys::VirtuosoRightDpadRight, LOCTEXT("VirtuosoRightDpadRight", "Virtuoso (R) Dpad Right"), FKeyDetails::GamepadKey, "VirtuosoInput"));

}

#undef LOCTEXT_NAMESPACE