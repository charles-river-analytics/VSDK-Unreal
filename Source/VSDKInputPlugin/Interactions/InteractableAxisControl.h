// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"
#include "InteractableAxisControl.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInteractableAxisSignature, float, value, float, normalizedValue, int, axis);

/**
* Struct to hold the data for a single axis an InteractableAxisControl can manipulate.
*
* Written by: Nicolas Herrera (nherrera@cra.com), 2020
*/
USTRUCT(BlueprintType)
struct FInteractableAxisStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAxisMoves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float minAxisValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxAxisValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float axisNormalizedStartValue;
};

/**
 * Provides 3 axis for an implementing child to manipulate as well as common set of events.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS()
class VSDKINPUTPLUGIN_API UInteractableAxisControl : public UInteractableComponent
{
	GENERATED_BODY()

public:
	UInteractableAxisControl();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK | Interactable Axis")
		FInteractableAxisStruct xAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK | Interactable Axis")
		FInteractableAxisStruct yAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK | Interactable Axis")
		FInteractableAxisStruct zAxis;

	UPROPERTY()
		UPrimitiveComponent* PhysicsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK | Interactable Axis")
		float movementTime = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Axis")
		FVector StartingPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Axis")
		FVector TargetPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Axis")
		FRotator TargetRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Axis")
		FTimerHandle MovementTimerHandle;

	/* Events */
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FInteractableAxisSignature OnValueChanged;

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FInteractableAxisSignature OnStartingPointReached;

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FInteractableAxisSignature OnStartingPointExited; // TODO [VIRTUOSO-50]

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FInteractableAxisSignature OnMaxLimitReached;

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FInteractableAxisSignature OnMaxLimitExited; // TODO [VIRTUOSO-50]

	/* Virtual classes */
	/** Called in the constructor to set the physics constraint */
	UFUNCTION(BlueprintCallable)
		virtual void SetupAxesConstraints();

	/** Called during BeginPlay to grab the initial start values and set up max limits */
	UFUNCTION(BlueprintCallable)
		virtual void SetupStartValues();

	/** Allows a child class to set a specific axis to a normalized value
	* @Param axis 0 x axis, 1 - y axis, 2 - z axis
	* @Param value A value between 0 and 1 to specify the position between the extremes
	* @Param teleport if true, will set value immedietly, otherwise will lerp to position
	*/
	UFUNCTION(BlueprintCallable)
		virtual void SetAxisValue(int axis, int value, bool teleport = false);

	/** Function called during the end frame tick to maintain the object within the limits */
	UFUNCTION(BlueprintCallable)
		virtual void MaintainAxesConstraints();

	/** Provides a normalized (0-1) value along a given axis.
	* @Param axis 0 - x axis, 1 - y axis, 2 - z axis
	* @Param value The current value of the axis position or rotation
    * @Return A value between 0 and 1 based on current value and start/max values
	*/
	UFUNCTION(BlueprintCallable)
		virtual float Normalize(int axis, float value);

	/** TODO */
	UFUNCTION(BlueprintCallable)
		virtual float GetAbsoluteFromNormalize(int axis, float normalizedValue);

	UFUNCTION()
		virtual void MoveOverTime();

	/** Check if the current value has moved past the start or max value limit and 
	* send the approrpriate event if so.
	* @Param axis 0 - x axis, 1 - y axis, 2 - z axis
	* @Param value The current value of the axis position or rotation
	*/
	UFUNCTION(BlueprintCallable)
		virtual void CheckLimits(int axis, float value);

	/** UActorComponent Overrides */
	virtual void OnComponentCreated() override;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
