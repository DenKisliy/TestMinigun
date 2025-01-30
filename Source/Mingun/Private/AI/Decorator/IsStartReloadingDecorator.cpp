// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/IsStartReloadingDecorator.h"

bool UIsStartReloadingDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return false;
	}

	return BlackboardComp->GetValueAsInt("CountOfBullet") == 0;

}
