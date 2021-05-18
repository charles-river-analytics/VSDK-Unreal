// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Templates/SharedPointer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VirtuosoInputWrapper.h"
#include "VirtuosoBlueprintFunctions.generated.h"

/**
	This class provides access to the Virtuoso Input Module for Blueprint classes because
	the module's methods are not UFUNCTIONs.

	Contributors: Dan Duggan (dduggan@cra.com) Updated: August 2020
 */
UCLASS()
class VIRTUOSOINPUT_API UVirtuosoBlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		/* 
			Registers an object as in Input Wrapper with the Virtuoso Input Module
			which allows the wrapper to provide input to VSDK.
		*/
		UFUNCTION(BlueprintCallable, Category=VSDK)
			static void RegisterInputWrapper(FName WrapperName, UObject* InInputWrapper);
	
		/*
			Calls the SetInputWrapper method for the VSDK input module,
			which changes the current input wrapper.
		*/
		UFUNCTION(BlueprintCallable, Category=VSDK)
			static void SetInputWrapper(FName WrapperName);

		/*
			Removes an object from the VSDK input module; this should be called
			before the wrapper object is deleted.
		*/
		UFUNCTION(BlueprintCallable, Category=VSDK)
			static void UnRegisterInputWrapper(FName WrapperName);

		UFUNCTION(BlueprintCallable, Category = VSDK)
			static void SetTrackingWrapper(FName WrapperName);
		
		
};
