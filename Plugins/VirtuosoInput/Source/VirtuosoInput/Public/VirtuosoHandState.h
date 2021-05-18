// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VirtuosoInputCommon.h"
#include "VirtuosoHandState.generated.h"

UENUM()
enum class VirtuosoHandId : uint8
{
	Left UMETA(DisplayName="Left"),
	Right UMETA(DisplayName="Right")
};

// Possible button states 
UENUM()
enum class VirtuosoButtonState : uint8
{
	Unpressed UMETA(DisplayName="Unpressed"),
	Touched UMETA(DisplayName = "Touched"),
	Pressed UMETA(DisplayName = "Pressed")
};

/**
	The VirtuosoHandState object is used to communicate the current state of input
	buttons and axes between wrappers, the input system, and other classes.

	Contributors: Dan Duggan (dduggan@cra.com) Updated: August 2020
*/
UCLASS(BlueprintType)
class VIRTUOSOINPUT_API UVirtuosoHandState : public UObject
{
public:

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsValid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState TriggerButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState GripButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState AButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState BButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState MenuButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState JoystickButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState DpadUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState DpadDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState DpadLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	VirtuosoButtonState DpadRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D JoystickAxis;

	UFUNCTION()
		void CopyValues(UVirtuosoHandState* Other);

	UFUNCTION(BlueprintCallable)
		void SetValid(bool Valid);

	UFUNCTION(BlueprintCallable)
		void SetTriggerButtonState(VirtuosoButtonState State);

	UFUNCTION(BlueprintCallable)
		void SetGripButtonState(VirtuosoButtonState State);

	UFUNCTION(BlueprintCallable)
		void SetAButtonState(VirtuosoButtonState State);

	UFUNCTION(BlueprintCallable)
		void SetBButtonState(VirtuosoButtonState State);

	UFUNCTION(BlueprintCallable)
		void SetMenuButtonState(VirtuosoButtonState State);

	UFUNCTION(BlueprintCallable)
		void SetJoystickButtonState(VirtuosoButtonState State);

	UFUNCTION(BlueprintCallable)
		void SetDpadUpState(VirtuosoButtonState State);

	UFUNCTION(BlueprintCallable)
		void SetDpadDownState(VirtuosoButtonState State);

	UFUNCTION(BlueprintCallable)
		void SetDpadLeftState(VirtuosoButtonState State);

	UFUNCTION(BlueprintCallable)
		void SetDpadRightState(VirtuosoButtonState State);

};

