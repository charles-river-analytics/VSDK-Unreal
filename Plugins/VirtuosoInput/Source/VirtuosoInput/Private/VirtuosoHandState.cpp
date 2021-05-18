// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "VirtuosoHandState.h"

void UVirtuosoHandState::SetValid(bool Valid)
{
	bIsValid = Valid;
}

void UVirtuosoHandState::SetTriggerButtonState(VirtuosoButtonState State)
{
	TriggerButton = State;
}

void UVirtuosoHandState::SetGripButtonState(VirtuosoButtonState State)
{
	GripButton = State;
}


void UVirtuosoHandState::SetAButtonState(VirtuosoButtonState State)
{
	AButton = State;
}

void UVirtuosoHandState::SetBButtonState(VirtuosoButtonState State)
{
	BButton = State;
}

void UVirtuosoHandState::SetMenuButtonState(VirtuosoButtonState State)
{
	MenuButton = State;
}

void UVirtuosoHandState::SetJoystickButtonState(VirtuosoButtonState State)
{
	JoystickButton = State;
}

void UVirtuosoHandState::SetDpadUpState(VirtuosoButtonState State)
{
	DpadUp = State;
}

void UVirtuosoHandState::SetDpadDownState(VirtuosoButtonState State)
{
	DpadDown = State;
}

void UVirtuosoHandState::SetDpadLeftState(VirtuosoButtonState State)
{
	DpadLeft = State;
}

void UVirtuosoHandState::SetDpadRightState(VirtuosoButtonState State)
{
	DpadRight = State;
}

void UVirtuosoHandState::CopyValues(UVirtuosoHandState* Other)
{
	bIsValid = Other->bIsValid;
	TriggerButton = Other->TriggerButton;
	GripButton = Other->GripButton;
	AButton = Other->AButton;
	BButton = Other->BButton;
	MenuButton = Other->MenuButton;
	JoystickButton = Other->JoystickButton;
	DpadUp = Other->DpadUp;
	DpadDown = Other->DpadDown;
	DpadLeft = Other->DpadLeft;
	DpadRight = Other->DpadRight;
	JoystickAxis = Other->JoystickAxis;
}