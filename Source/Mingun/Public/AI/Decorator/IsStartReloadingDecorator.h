// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "../Controller/AIMinigunController.h"

#include "IsStartReloadingDecorator.generated.h"

/**
 * 
 */
UCLASS()
class MINGUN_API UIsStartReloadingDecorator : public UBTDecorator
{
	GENERATED_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
