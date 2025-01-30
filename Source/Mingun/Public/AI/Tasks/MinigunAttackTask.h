// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "../../Actor/BulletActor.h"
#include "../Controller/AIMinigunController.h"

#include "MinigunAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class MINGUN_API UMinigunAttackTask : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Data, EditAnywhere)
	TSubclassOf<ABulletActor> SpawnActor;

	UPROPERTY(EditAnywhere, Category = Data)
	USoundBase* FireSound;

private:
	UBehaviorTreeComponent* BehaviorTreeComponent;

	FTimerHandle LaunchTimer;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UFUNCTION()
	void OnEndAbility();

	//Manager timer
	UFUNCTION()
	void OnFire();

	void SpawnBullet();
};
