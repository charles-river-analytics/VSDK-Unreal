// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VirtuosoInputWrapper.h"
#include "DefaultVirtuosoInputWrapper.generated.h"

/**
 * Wraps the most common VR inputs methods for use with Virtuoso.
 *
 *	Contributors: Dan Duggan (dduggan@cra.com) Updated: Septemeber 2020
 */
UCLASS(BlueprintType)
class VIRTUOSOINPUT_API UDefaultVirtuosoInputWrapper :  public UObject, public IVirtuosoInputWrapper
{
public:

	GENERATED_BODY()

	UDefaultVirtuosoInputWrapper();
	~UDefaultVirtuosoInputWrapper();

	virtual class UVirtuosoHandState* GetInput_Implementation(VirtuosoHandId HandId) override;

	virtual class UVirtuosoTrackingState* GetTrackingState_Implementation(VirtuosoHandId HandId) override;
};
