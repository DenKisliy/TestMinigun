// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataInfoSubsystem.generated.h"

/**
 * 
 */
USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	float CountOfBullet;

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float FireRate;

	UPROPERTY(EditAnywhere)
	float TimeToStart;

	UPROPERTY(EditAnywhere)
	float RechargeTime;

	FWeaponData(float CountOfBulletValue = 0, float DamageValue = 0, float FireRateValue = 0, float TimeToStartValue = 0, float RechargeTimeValue = 0)
	{
		CountOfBullet = CountOfBulletValue;
		Damage = DamageValue;
		FireRate = FireRateValue;
		TimeToStart = TimeToStartValue;
		RechargeTime = RechargeTimeValue;
	}
};

UCLASS()
class MINGUN_API UDataInfoSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	FWeaponData* MinigunData = nullptr;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	FWeaponData* GetWeaponData() { return MinigunData; }


};
