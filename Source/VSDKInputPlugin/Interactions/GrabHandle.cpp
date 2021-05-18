// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "GrabHandle.h"

// Sets default values for this component's properties
UGrabHandle::UGrabHandle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

FTransform UGrabHandle::GetTransform()
{ 
	return this->GetComponentTransform();
}