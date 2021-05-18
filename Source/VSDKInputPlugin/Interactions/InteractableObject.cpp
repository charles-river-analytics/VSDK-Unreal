// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "InteractableObject.h"
#include "InteractableComponent.h"
#include "InteractableSelect.h"
#include "InteractableGrab.h"
#include "InteractableUse.h"
#include "TouchSelector.h"
#include "ChildGrabAttach.h"

AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set up mesh
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMesh"));
	SetRootComponent(InteractableMesh);

	// Set up selection
	DefaultSelectComponent = CreateDefaultSubobject<UInteractableSelect>(TEXT("InteractableSelect"));
	DefaultSelectComponent->bEditableWhenInherited = true;
	DefaultSelectComponent->RegisterComponentWithWorld(GetWorld());
	DefaultSelectComponent->CreationMethod = EComponentCreationMethod::Native;

	// Set up grabbing
	DefaultGrabComponent = CreateDefaultSubobject<UInteractableGrab>(TEXT("InteractableGrab"));
	DefaultGrabComponent->bEditableWhenInherited = true;
	DefaultGrabComponent->RegisterComponentWithWorld(GetWorld());
	DefaultGrabComponent->CreationMethod = EComponentCreationMethod::Native;

	// Set the grab handle
	GrabHandle = CreateDefaultSubobject<UGrabHandle>(TEXT("GrabHandle"));
	GrabHandle->bEditableWhenInherited = true;
	GrabHandle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	GrabHandle->CreationMethod = EComponentCreationMethod::Native;

	// Set up using
	DefaultUseComponent = CreateDefaultSubobject<UInteractableUse>(TEXT("InteractableUse"));
	DefaultUseComponent->bEditableWhenInherited = true;
	DefaultUseComponent->RegisterComponentWithWorld(GetWorld());
	DefaultUseComponent->CreationMethod = EComponentCreationMethod::Native;
}

void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UInteractableComponent*> DynamicInteractableComponentsArray;
	GetComponents<UInteractableComponent>(DynamicInteractableComponentsArray);

	for (UInteractableComponent* CurrentActorComponent : DynamicInteractableComponentsArray)
	{
		UInteractableComponent* CurrentInteractableComponent = Cast<UInteractableComponent>(CurrentActorComponent);

		AvailableInteractableComponents.Add(CurrentInteractableComponent->GetComponentName(), CurrentInteractableComponent);
	}
}

UInteractableComponent* AInteractableObject::GetInteractableComponent(FName componentName)
{
	if (AvailableInteractableComponents.Contains(componentName))
	{
		return AvailableInteractableComponents[componentName];
	}

	return nullptr;
}

FTransform AInteractableObject::GetGrabTransform()
{
	return GrabHandle->GetTransform();
}