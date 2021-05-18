#pragma once

#include "Runtime/InputCore/Public/InputCore.h"
/*
	This file contains common types used between multiple Virtuoso Input Modules.

	Contributors: Dan Duggan (dduggan@cra.com) Updated: August 2020
*/

/** Namespace contains the FKey definitions for Virtuoso (used to identify input actions elsewhere) */
namespace VirtuosoKeys
{
	// Trigger
	const FKey VirtuosoLeftTriggerPress("VirtuosoLeftTriggerPress");
	const FKey VirtuosoLeftTriggerTouch("VirtuosoLeftTriggerTouch");
	const FKey VirtuosoRightTriggerPress("VirtuosoRightTriggerPress");
	const FKey VirtuosoRightTriggerTouch("VirtuosoRightTriggerTouch");

	// Grip
	const FKey VirtuosoLeftGripPress("VirtuosoLeftGripPress");
	const FKey VirtuosoLeftGripTouch("VirtuosoLeftGripTouch");
	const FKey VirtuosoRightGripPress("VirtuosoRightGripPress");
	const FKey VirtuosoRightGripTouch("VirtuosoRightGripTouch");

	// Buttons
	const FKey VirtuosoLeftAPress("VirtuosoLeftAPress");
	const FKey VirtuosoLeftATouch("VirtuosoLeftATouch");
	const FKey VirtuosoLeftBPress("VirtuosoLeftBPress");
	const FKey VirtuosoLeftBTouch("VirtuosoLeftBTouch");
	const FKey VirtuosoLeftMenuPress("VirtuosoLeftMenuPress");
	const FKey VirtuosoLeftMenuTouch("VirtuosoLeftMenuTouch");
	const FKey VirtuosoRightAPress("VirtuosoRightAPress");
	const FKey VirtuosoRightATouch("VirtuosoRightATouch");
	const FKey VirtuosoRightBPress("VirtuosoRightBPress");
	const FKey VirtuosoRightBTouch("VirtuosoRightBTouch");
	const FKey VirtuosoRightMenuPress("VirtuosoRightMenuPress");
	const FKey VirtuosoRightMenuTouch("VirtuosoRightMenuTouch");

	// Joystick Click
	const FKey VirtuosoLeftJoystickPress("VirtuosoLeftJoystickPress");
	const FKey VirtuosoLeftJoystickTouch("VirtuosoLeftJoystickTouch");
	const FKey VirtuosoRightJoystickPress("VirtuosoRightJoystickPress");
	const FKey VirtuosoRightJoystickTouch("VirtuosoRightJoystickTouch");

	// Joystick Axes
	const FKey VirtuosoLeftJoystickXAxis("VirtuosoLeftJoystickXAxis");
	const FKey VirtuosoLeftJoystickYAxis("VirtuosoLeftJoystickYAxis");
	const FKey VirtuosoLeftJoystickAxis("VirtuosoLeftJoystickAxis");
	const FKey VirtuosoRightJoystickXAxis("VirtuosoRightJoystickXAxis");
	const FKey VirtuosoRightJoystickYAxis("VirtuosoRightJoystickYAxis");
	const FKey VirtuosoRightJoystickAxis("VirtuosoRightJoystickAxis");

	// Joystick D-Pad
	/*
		These keys are intended to provide a shortcut for using the joystick as 
		a D-Pad for input (e.g. for a quick select wheel).
	*/
	const FKey VirtuosoLeftDpadUp("VirtuosoLeftDpadUp");
	const FKey VirtuosoLeftDpadDown("VirtuosoLeftDpadDown");
	const FKey VirtuosoLeftDpadLeft("VirtuosoLeftDpadLeft");
	const FKey VirtuosoLeftDpadRight("VirtuosoLeftDpadRight");
	const FKey VirtuosoRightDpadUp("VirtuosoRightDpadUp");
	const FKey VirtuosoRightDpadDown("VirtuosoRightDpadDown");
	const FKey VirtuosoRightDpadLeft("VirtuosoRightDpadLeft");
	const FKey VirtuosoRightDpadRight("VirtuosoRightDpadRight");
}