// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "VirtuosoInputWrapper.h"
#include "VirtuosoHandState.h"
#include "VirtuosoTrackingState.h"

// Add default functionality here for any IVirtuosoInputWrapper functions that are not pure virtual.

UVirtuosoHandState* IVirtuosoInputWrapper::GetInput_Implementation(VirtuosoHandId HandId)
{
	UVirtuosoHandState* result = NewObject<UVirtuosoHandState>();
	result->bIsValid = false;
	return result;
}

UVirtuosoTrackingState* IVirtuosoInputWrapper::GetTrackingState_Implementation(VirtuosoHandId HandId)
{
	UVirtuosoTrackingState* result = NewObject<UVirtuosoTrackingState>();
	result->TrackingStatus = ETrackingStatus::NotTracked;
	return result;
}