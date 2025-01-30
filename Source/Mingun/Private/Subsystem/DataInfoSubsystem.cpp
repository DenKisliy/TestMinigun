// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/DataInfoSubsystem.h"

void UDataInfoSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	MinigunData = new FWeaponData(6, 10, 1, 1, 5);
}
