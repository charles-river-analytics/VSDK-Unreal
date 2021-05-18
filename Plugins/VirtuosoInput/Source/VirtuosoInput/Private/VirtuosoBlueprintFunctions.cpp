// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "VirtuosoBlueprintFunctions.h"
#include "VirtuosoInput.h"


void UVirtuosoBlueprintFunctions::RegisterInputWrapper(FName WrapperName, UObject* InInputWrapper)
{
	FVirtuosoInputModule::Get().RegisterInputWrapper(WrapperName, InInputWrapper);
}

void UVirtuosoBlueprintFunctions::SetInputWrapper(FName WrapperName)
{
	FVirtuosoInputModule::Get().SetInputWrapper(WrapperName);
}

void UVirtuosoBlueprintFunctions::UnRegisterInputWrapper(FName WrapperName)
{
	FVirtuosoInputModule::Get().UnRegisterInputWrapper(WrapperName);
}

void UVirtuosoBlueprintFunctions::SetTrackingWrapper(FName WrapperName)
{
	FVirtuosoInputModule::Get().SetTrackingWrapper(WrapperName);
}