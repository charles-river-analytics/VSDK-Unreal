// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "InteractableSlider.h"
#include "Kismet/KismetMathLibrary.h"

void UInteractableSlider::SetupAxesConstraints()
{
	PhysicsComponent->GetBodyInstance()->bLockXTranslation = !xAxis.bAxisMoves;
	PhysicsComponent->GetBodyInstance()->bLockYTranslation = !yAxis.bAxisMoves;
	PhysicsComponent->GetBodyInstance()->bLockZTranslation = !zAxis.bAxisMoves;
}

void UInteractableSlider::SetupStartValues()
{
	SlideMinDistances = FVector(
		FMath::Min(StartingPosition.X + xAxis.minAxisValue, StartingPosition.X + xAxis.maxAxisValue),
		FMath::Min(StartingPosition.Y + yAxis.minAxisValue, StartingPosition.Y + yAxis.maxAxisValue),
		FMath::Min(StartingPosition.Z + zAxis.minAxisValue, StartingPosition.Z + zAxis.maxAxisValue));

	SlideMaxDistances = FVector(
		FMath::Max(StartingPosition.X + xAxis.minAxisValue, StartingPosition.X + xAxis.maxAxisValue),
		FMath::Max(StartingPosition.Y + yAxis.minAxisValue, StartingPosition.Y + yAxis.maxAxisValue),
		FMath::Max(StartingPosition.Z + zAxis.minAxisValue, StartingPosition.Z + zAxis.maxAxisValue));

	FVector startPosition = FVector(GetAbsoluteFromNormalize(0, xAxis.axisNormalizedStartValue),
		GetAbsoluteFromNormalize(1, yAxis.axisNormalizedStartValue),
		GetAbsoluteFromNormalize(2, zAxis.axisNormalizedStartValue));

	GetOwner()->SetActorLocation(startPosition);
}

void UInteractableSlider::MaintainAxesConstraints()
{
	FVector currentPosition = GetOwner()->GetActorLocation();
	FVector newPosition = currentPosition;

	// Keep X Axis within bounds
	if (xAxis.bAxisMoves)
	{
		if (currentPosition.X < SlideMinDistances.X)
		{
			newPosition.X = SlideMinDistances.X;

			CheckLimits(0, newPosition.X);
		}
		else if (currentPosition.X > SlideMaxDistances.X)
		{
			newPosition.X = SlideMaxDistances.X;

			CheckLimits(0, newPosition.X);
		}

		OnValueChanged.Broadcast(newPosition.X, Normalize(0, newPosition.X), 0);
	}
	else
	{
		newPosition.X = SlideMinDistances.X;
	}

	// Keep Y Axis within bounds
	if (yAxis.bAxisMoves)
	{
		if (currentPosition.Y < SlideMinDistances.Y)
		{
			newPosition.Y = SlideMinDistances.Y;

			CheckLimits(1, newPosition.Y);
		}
		else if (currentPosition.Y > SlideMaxDistances.Y)
		{
			newPosition.Y = SlideMaxDistances.Y;

			CheckLimits(1, newPosition.Y);
		}

		OnValueChanged.Broadcast(newPosition.Y, Normalize(1, newPosition.Y), 1);
	}
	else
	{
		newPosition.Y = SlideMinDistances.Y;
	}

	// Keep Z Axis within bounds
	if (zAxis.bAxisMoves)
	{
		if (currentPosition.Z < SlideMinDistances.Z)
		{
			newPosition.Z = SlideMinDistances.Z;

			CheckLimits(2, newPosition.Z);
		}
		else if (currentPosition.Z > SlideMaxDistances.Z)
		{
			newPosition.Z = SlideMaxDistances.Z;

			CheckLimits(2, newPosition.Z);
		}

		OnValueChanged.Broadcast(newPosition.Z, Normalize(2, newPosition.Z), 2);
	}
	else
	{
		newPosition.Z = SlideMinDistances.Z;
	}

	GetOwner()->SetActorLocation(newPosition);
}

float UInteractableSlider::Normalize(int axis, float value)
{
	return UKismetMathLibrary::NormalizeToRange(value, SlideMinDistances[axis], SlideMaxDistances[axis]);
}

void UInteractableSlider::CheckLimits(int axis, float value)
{
	if (value == SlideMinDistances[axis])
	{
		OnStartingPointReached.Broadcast(value, Normalize(axis, value), axis);
	}
	else
	{
		OnMaxLimitReached.Broadcast(value, Normalize(axis, value), axis);
	}
}

void UInteractableSlider::SetAxisValue(int axis, int value, bool teleport)
{
	FVector currentPosition = GetOwner()->GetActorLocation();

	TargetPosition = currentPosition;
	TargetPosition[axis] = GetAbsoluteFromNormalize(axis, value);
	
	if (teleport)
	{
		GetOwner()->SetActorLocation(TargetPosition);
	}
	else
	{
		// Call the move function at the same rate as the physics time delta
		GetOwner()->GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &UInteractableSlider::MoveOverTime, FApp::GetFixedDeltaTime(), true);
	}
}

float UInteractableSlider::GetAbsoluteFromNormalize(int axis, float normalizedValue)
{
	return FMath::Lerp(SlideMinDistances[axis], SlideMaxDistances[axis], normalizedValue);
}

void UInteractableSlider::MoveOverTime()
{
	FVector currentPosition = GetOwner()->GetActorLocation();

	if (FVector::Distance(currentPosition, TargetPosition) < KINDA_SMALL_NUMBER)
	{
		GetOwner()->GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
	}
	else
	{
		GetOwner()->SetActorLocation(FMath::VInterpTo(currentPosition, TargetPosition, FApp::GetFixedDeltaTime(), movementTime));
	}
}