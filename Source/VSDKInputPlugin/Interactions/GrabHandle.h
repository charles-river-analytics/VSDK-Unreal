// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GrabHandle.generated.h"


UCLASS( ClassGroup=(VSDK), meta=(BlueprintSpawnableComponent) )
class VSDKINPUTPLUGIN_API UGrabHandle : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabHandle();

	UFUNCTION(BlueprintCallable, Category = "VSDK")
	FTransform GetTransform();
};
