// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "../Controller/AIMinigunController.h"

#include "MinigunReloadTask.generated.h"

/**
 * 
 */
UCLASS()
class MINGUN_API UMinigunReloadTask : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Data, EditAnywhere)
	UMaterialInterface* ReloadMaterial;

	UPROPERTY(EditAnywhere, Category = Data)
	USoundBase* FinishReloadSound;

private:
	UBehaviorTreeComponent* BehaviorTreeComponent;

	FTimerHandle LaunchTimer;

	UMaterialInterface* DefaultMaterial;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UFUNCTION()
	void OnEndAbility();

	UFUNCTION()
	void OnFinishReload();
};
