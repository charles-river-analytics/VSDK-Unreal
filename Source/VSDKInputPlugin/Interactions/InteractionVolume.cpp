// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "InteractionVolume.h"
#include "../HandPresence/Hand.h"
#include "Components/BoxComponent.h"

UInteractionVolume::UInteractionVolume() : Super()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	CollisionComponent->bEditableWhenInherited = true;
	CollisionComponent->CreationMethod = EComponentCreationMethod::Native;
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3); // InteractionVolume Type
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComponent->SetCanEverAffectNavigation(false);

	FilterForInteractableObjects = CreateDefaultSubobject<UFilterInteractables>(TEXT("Filters"));
	FilterForInteractableObjects->bEditableWhenInherited = true;
	FilterForInteractableObjects->CreationMethod = EComponentCreationMethod::Native;
}

void UInteractionVolume::OnComponentCreated()
{
	Super::OnComponentCreated();

	if (GetOwner() != nullptr && !(CollisionComponent->IsRegistered()))
	{
		CollisionComponent->SetupAttachment(this);
		CollisionComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
	}

	if (FilterForInteractableObjects != nullptr)
	{
		if (GetOwner() != nullptr && !(FilterForInteractableObjects->IsRegistered()))
		{
			FilterForInteractableObjects->RegisterComponentWithWorld(GetOwner()->GetWorld());
		}
	}
}

void UInteractionVolume::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionComponent != nullptr)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UInteractionVolume::BeginOverlap);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UInteractionVolume::EndOverlap);
	}
}

void UInteractionVolume::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CollisionComponent != nullptr)
	{
		CollisionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UInteractionVolume::BeginOverlap);
		CollisionComponent->OnComponentEndOverlap.RemoveDynamic(this, &UInteractionVolume::EndOverlap);
	}
}

void UInteractionVolume::UseVolume(AActor* UsingActor)
{
	if (IntersectingActors.Contains(UsingActor))
	{
		OnUseStarted.Broadcast(UsingActor);
	}
}

void UInteractionVolume::FinishUseVolume(AActor* UsingActor)
{
	if (IntersectingActors.Contains(UsingActor))
	{
		OnUseFinished.Broadcast(UsingActor);

		StopUseVolume(UsingActor);
	}
}

void UInteractionVolume::StopUseVolume(AActor* UsingActor)
{
	if (IntersectingActors.Contains(UsingActor))
	{
		OnUseStopped.Broadcast(UsingActor);
	}
}

void UInteractionVolume::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsInteractableObject(OtherActor) || IsHand(OtherActor))
	{
		if (OtherActor != GetOwner() &&
			FilterForInteractableObjects->FilterForInteractableObjects.Num() == 0 ||
			FilterForInteractableObjects->IsValidInteractable(OtherActor))
		{
			if (!IntersectingActors.Contains(OtherActor))
			{
				IntersectingActors.Add(OtherActor);

				OnObjectEnter.Broadcast(OtherActor);
			}
		}
	}
}

void UInteractionVolume::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IntersectingActors.Contains(OtherActor))
	{
		IntersectingActors.Remove(OtherActor);

		OnObjectExit.Broadcast(OtherActor);
	}
}

bool UInteractionVolume::IsInteractableObject(AActor* Other)
{
	return Other->IsA(AInteractableObject::StaticClass());
}

bool UInteractionVolume::IsHand(AActor* Other)
{
	return Other->IsA(AHand::StaticClass());
}