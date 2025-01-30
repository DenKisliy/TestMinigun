// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/IsCanAttackDecorator.h"

bool UIsCanAttackDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return false;
	}
	
	if (BlackboardComp->GetValueAsObject("DetectPlayer"))
	{
		return BlackboardComp->GetValueAsInt("CountOfBullet") > 0;
	}

	return false;
}
