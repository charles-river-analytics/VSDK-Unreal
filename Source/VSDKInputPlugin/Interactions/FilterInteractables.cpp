// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "FilterInteractables.h"

bool UFilterInteractables::IsValidInteractable(AActor* UsingActor)
{
	bool isValid = false;

	for (FFilterInteractableData Filter : FilterForInteractableObjects)
	{
		bool isCurrentFilterValid = IsValidFilter(UsingActor, Filter);

		// The object has the correct value for the type, but set to ignore, which takes precedant
		if (isCurrentFilterValid && Filter.FilterLevel == EFilterLevel::IGNORE)
		{
			return false;
		}

		isValid = isValid && isCurrentFilterValid;
	}

	return isValid;
}

bool UFilterInteractables::IsValidFilter(AActor* UsingActor, FFilterInteractableData filter)
{
	bool isValid = false;
	
	switch (filter.FilterType)
	{
	case TAG:
		isValid = UsingActor->Tags.Contains(filter.FilterValue);
		break;
	default:
		break;
	}

	return isValid;
}