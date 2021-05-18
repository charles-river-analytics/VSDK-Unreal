// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "InteractableRotator.h"
#include "Kismet/KismetMathLibrary.h"

void UInteractableRotator::SetupAxesConstraints()
{
	PhysicsComponent->GetBodyInstance()->bLockXRotation = !xAxis.bAxisMoves;
	PhysicsComponent->GetBodyInstance()->bLockYRotation = !yAxis.bAxisMoves;
	PhysicsComponent->GetBodyInstance()->bLockZRotation = !zAxis.bAxisMoves;
}

void UInteractableRotator::BeginPlay()
{
	Super::BeginPlay();

	PivotLocation = GetCurrentPivotLocation();
}

void UInteractableRotator::SetupStartValues()
{
	StartingRotation = GetOwner()->GetActorRotation();

	MinRotationLimit = FVector(
		FMath::Min(StartingRotation.Euler().X + xAxis.minAxisValue, StartingRotation.Euler().X + xAxis.maxAxisValue),
		FMath::Min(StartingRotation.Euler().Y + yAxis.minAxisValue, StartingRotation.Euler().Y + yAxis.maxAxisValue),
		FMath::Min(StartingRotation.Euler().Z + zAxis.minAxisValue, StartingRotation.Euler().Z + zAxis.maxAxisValue));

	MaxRotationLimit = FVector(
		FMath::Max(StartingRotation.Euler().X + xAxis.minAxisValue, StartingRotation.Euler().X + xAxis.maxAxisValue),
		FMath::Max(StartingRotation.Euler().Y + yAxis.minAxisValue, StartingRotation.Euler().Y + yAxis.maxAxisValue),
		FMath::Max(StartingRotation.Euler().Z + zAxis.minAxisValue, StartingRotation.Euler().Z + zAxis.maxAxisValue));
	
	// Args for FRotator - InPitch, InYaw, InRoll
	FRotator startingRotation = FRotator(
		GetAbsoluteFromNormalize(1, yAxis.axisNormalizedStartValue),
		GetAbsoluteFromNormalize(2, zAxis.axisNormalizedStartValue),
		GetAbsoluteFromNormalize(0, xAxis.axisNormalizedStartValue));

	GetOwner()->SetActorRotation(startingRotation);
}

FVector UInteractableRotator::GetCurrentPivotLocation()
{
	return GetOwner()->GetActorLocation() + (PivotOffset * GetOwner()->GetActorScale());
}

void UInteractableRotator::MaintainAxesConstraints()
{
	FRotator currentRotation = GetOwner()->GetActorRotation();
	FVector constrainedRotation = currentRotation.Euler();

	// Keep Roll axis within bounds
	if (xAxis.bAxisMoves)
	{
		if (constrainedRotation.X < MinRotationLimit.X)
		{
			constrainedRotation.X = GetAbsoluteFromNormalize(0, 0);

			CheckLimits(0, constrainedRotation.X);
		}
		else if (constrainedRotation.X > MaxRotationLimit.X)
		{
			constrainedRotation.X = GetAbsoluteFromNormalize(0, 1);

			CheckLimits(0, constrainedRotation.X);
		}

		OnValueChanged.Broadcast(constrainedRotation.X, Normalize(0, constrainedRotation.X), 0);
	}
	else
	{
		constrainedRotation.X = GetAbsoluteFromNormalize(0, xAxis.axisNormalizedStartValue);
	}

	// Keep Pitch axis within bounds
	if (yAxis.bAxisMoves)
	{
		if (constrainedRotation.Y < MinRotationLimit.Y)
		{
			constrainedRotation.Y = GetAbsoluteFromNormalize(1, 0);

			CheckLimits(1, constrainedRotation.Y);
		}
		else if (constrainedRotation.Y > MaxRotationLimit.Y)
		{
			constrainedRotation.Y = GetAbsoluteFromNormalize(1, 1);
			
			CheckLimits(1, constrainedRotation.Y);
		}

		OnValueChanged.Broadcast(constrainedRotation.Y, Normalize(1, constrainedRotation.Y), 1);
	}
	else
	{
		constrainedRotation.Y = GetAbsoluteFromNormalize(1, yAxis.axisNormalizedStartValue);
	}

	// Keep Yaw axis within bounds
	if (zAxis.bAxisMoves)
	{
		if (constrainedRotation.Z < MinRotationLimit.Z)
		{
			constrainedRotation.Z = GetAbsoluteFromNormalize(2, 0);
			
			CheckLimits(2, constrainedRotation.Z);
		}
		else if (constrainedRotation.Z > MaxRotationLimit.Z)
		{
			constrainedRotation.Z = GetAbsoluteFromNormalize(2, 1);
			
			CheckLimits(2, constrainedRotation.Z);
		}

		OnValueChanged.Broadcast(constrainedRotation.Z, Normalize(2, constrainedRotation.Z), 2);
	}
	else
	{
		constrainedRotation.Z = GetAbsoluteFromNormalize(2, zAxis.axisNormalizedStartValue);
	}
	
	// Convert the euler angles back to an FRotator and set the rotation
	FRotator constrainedRotator = FRotator::MakeFromEuler(constrainedRotation);
	GetOwner()->SetActorRotation(constrainedRotator);
	
	// Keep the actor at the correct pivot position
	FVector newLocation = PivotLocation + constrainedRotator.RotateVector(StartingPosition - PivotLocation);
	GetOwner()->SetActorLocation(newLocation);
}

float UInteractableRotator::Normalize(int axis, float value)
{
	return UKismetMathLibrary::NormalizeToRange(value, MinRotationLimit[axis], MaxRotationLimit[axis]);
}

void UInteractableRotator::CheckLimits(int axis, float value)
{
	if (value == MinRotationLimit[axis])
	{
		OnStartingPointReached.Broadcast(value, Normalize(axis, value), axis);
	}
	else
	{
		OnMaxLimitReached.Broadcast(value, Normalize(axis, value), axis);
	}
}

void UInteractableRotator::SetAxisValue(int axis, int value, bool teleport)
{
	TargetRotation = GetOwner()->GetActorRotation();

	float newValue = GetAbsoluteFromNormalize(axis, value);

	TargetRotation.Vector()[axis] = newValue;

	if (teleport)
	{
		GetOwner()->SetActorRotation(TargetRotation, ETeleportType::TeleportPhysics);
	}
	else
	{
		// Call the move function at the same rate as the physics time delta
		GetOwner()->GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &UInteractableRotator::MoveOverTime, FApp::GetFixedDeltaTime(), true);
	}
}

float UInteractableRotator::GetAbsoluteFromNormalize(int axis, float normalizedValue)
{
	return FMath::Lerp(MinRotationLimit[axis], MaxRotationLimit[axis], normalizedValue);
}

void UInteractableRotator::MoveOverTime()
{
	// movementTime
	FRotator currentRotation = GetOwner()->GetActorRotation();

	//FVector::DotProduct(currentRotation.GetNormalized(), TargetRotation.GetNormalized())
	if (true/*FVector::Distance(currentPosition, TargetPosition) < KINDA_SMALL_NUMBER*/)
	{
		GetOwner()->GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);
	}
	else
	{
		GetOwner()->SetActorRotation(FMath::RInterpTo(currentRotation, TargetRotation, FApp::GetFixedDeltaTime(), movementTime));
	}
}