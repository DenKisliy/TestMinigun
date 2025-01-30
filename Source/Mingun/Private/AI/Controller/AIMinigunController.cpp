// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIMinigunController.h"
#include "../../../MingunCharacter.h"
#include "../../../Public/Subsystem/DataInfoSubsystem.h"

AAIMinigunController::AAIMinigunController(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	UAISenseConfig_Sight* Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sensesight");
	Sight->SightRadius = 500;
	Sight->LoseSightRadius = 550;
	Sight->PeripheralVisionAngleDegrees = 45;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectEnemies = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	AIPerceptionComponent->ConfigureSense(*Sight);
	AIPerceptionComponent->SetDominantSense(Sight->GetSenseImplementation());

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIMinigunController::OnPerception);

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AAIMinigunController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	if (IsValid(BTMinigun))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			if (AMingunCharacter* Player = Cast<AMingunCharacter>(Actor))
			{
				BlackboardComponent->SetValueAsObject("DetectPlayer", Actor);
			}
		}
		else
		{
			BlackboardComponent->SetValueAsObject("DetectPlayer", nullptr);
		}
	}
}

void AAIMinigunController::SetStartDate()
{
	if (AMinigunActor* Bot = Cast<AMinigunActor>(GetPawn()))
	{
		OwnerCharacter = Bot;
		RunBehaviorTree(BTMinigun);

		if (IsValid(BTMinigun))
		{
			if (UBlackboardData* BlackboardData = BTMinigun->GetBlackboardAsset())
			{
				BlackboardComponent->InitializeBlackboard(*BlackboardData);

				if (UDataInfoSubsystem* SessionSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataInfoSubsystem>())
				{
					if (FWeaponData* WeaponData = SessionSubsystem->GetWeaponData())
					{
						BlackboardComponent->SetValueAsInt("CountOfBullet", WeaponData->CountOfBullet);
						BlackboardComponent->SetValueAsInt("MaxCountOfBullet", WeaponData->CountOfBullet);
						BlackboardComponent->SetValueAsFloat("RechargeTime", WeaponData->RechargeTime);
						BlackboardComponent->SetValueAsFloat("TimeToStart", WeaponData->TimeToStart);
						BlackboardComponent->SetValueAsFloat("FireRate", WeaponData->FireRate);
						BlackboardComponent->SetValueAsFloat("Damage", WeaponData->Damage);
					}
				}
			}
		}
	}
}

void AAIMinigunController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetStartDate();
}
