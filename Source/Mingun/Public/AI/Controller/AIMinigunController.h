// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "../../Actor/MinigunActor.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AIMinigunController.generated.h"

/**
 * 
 */
UCLASS()
class MINGUN_API AAIMinigunController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior Tree", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BTMinigun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BlackboardComponent;

private:
	AMinigunActor* OwnerCharacter;

public:
	AAIMinigunController(const FObjectInitializer& ObjectInitializer);

private:
	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	void SetStartDate();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
