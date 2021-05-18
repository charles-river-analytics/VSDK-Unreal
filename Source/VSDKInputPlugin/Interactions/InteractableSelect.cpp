// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "InteractableSelect.h"

UInteractableSelect::UInteractableSelect()
{
	PrimaryComponentTick.bCanEverTick = true;

	ComponentName = FName("Select");
}

void UInteractableSelect::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> SelectableComponents = GetOwner()->GetComponentsByInterface(USelectable::StaticClass());

	if (SelectableComponents.Num() > 0)
	{
		for (UActorComponent* current : SelectableComponents)
		{
			TScriptInterface<ISelectable> CurrentSelectable = TScriptInterface<ISelectable>();
			CurrentSelectable.SetInterface(Cast<ISelectable>(current));
			CurrentSelectable.SetObject(current);

			CurrentSelectable->SetSelectable(this);
		}
	}
}

// Cannot be selected if an object is already selected
bool UInteractableSelect::IsActionable_Implementation()
{
	return !bIsComponentActive;
}

bool UInteractableSelect::IsSelectedByActor(AActor* SelectingActor)
{
	return CurrentSelectors.Contains(SelectingActor);
}

void UInteractableSelect::Select(AActor* ObjectSelecting)
{
	if (ObjectSelecting->GetClass()->ImplementsInterface(USelector::StaticClass()))
	{
		TScriptInterface<ISelector> CurrentSelector;
		CurrentSelector.SetInterface(Cast<ISelector>(ObjectSelecting));
		CurrentSelector.SetObject(ObjectSelecting);

		CurrentSelector->OnInteractableBeginSelect(Cast<AInteractableObject>(GetOwner()));

		CurrentSelectors.Add(ObjectSelecting, CurrentSelector);

		bIsComponentActive = true;

		OnInteractableSelect.Broadcast(this, ObjectSelecting);
	}
}

void UInteractableSelect::Deselect(AActor* ObjectDeselecting)
{
	if (CurrentSelectors.Contains(ObjectDeselecting))
	{
		bIsComponentActive = false;

		OnInteractableDeselect.Broadcast(this, ObjectDeselecting);

		CurrentSelectors[ObjectDeselecting]->OnInteractableEndSelect(Cast<AInteractableObject>(GetOwner()));

		CurrentSelectors.Remove(ObjectDeselecting);

		if (CurrentSelectors.Num() == 0)
		{
			bIsComponentActive = false;
		}
	}
}
