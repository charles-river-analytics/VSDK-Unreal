// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VirtuosoHandState.h"
#include "VirtuosoInputWrapper.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UVirtuosoInputWrapper : public UInterface
{
	GENERATED_BODY()
};

/**
* Classes that implement this interface provide input data that
* drives controller event generation in the Virtuoso Input Device.
*
*   Contributors: Dan Duggan (dduggan@cra.com) Updated: August 2020
*/
class VIRTUOSOINPUT_API IVirtuosoInputWrapper
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = VSDK)
		class UVirtuosoHandState* GetInput(VirtuosoHandId HandId);
	virtual class UVirtuosoHandState* GetInput_Implementation(VirtuosoHandId HandId);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = VSDK)
		class UVirtuosoTrackingState* GetTrackingState(VirtuosoHandId HandId);
	virtual class UVirtuosoTrackingState* GetTrackingState_Implementation(VirtuosoHandId HandId);

};
