// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/MinigunAttackTask.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../../MingunCharacter.h"

EBTNodeResult::Type UMinigunAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	if (IsValid(GetWorld()))
	{
		if (!IsValid(BehaviorTreeComponent) && IsValid(SpawnActor))
		{
			BehaviorTreeComponent = &OwnerComp;

			if (BlackboardComp->GetValueAsInt("CountOfBullet") > 0)
			{
				GetWorld()->GetTimerManager().ClearTimer(LaunchTimer);
				GetWorld()->GetTimerManager().SetTimer(LaunchTimer, this, &UMinigunAttackTask::OnFire, BlackboardComp->GetValueAsFloat("TimeToStart"), false);

				return EBTNodeResult::InProgress;
			}
		}
	}

	return EBTNodeResult::Failed;
}

void UMinigunAttackTask::OnEndAbility()
{
	if (IsValid(BehaviorTreeComponent))
	{
		if (UBTTaskNode* TemplateNode = Cast<UBTTaskNode>(BehaviorTreeComponent->FindTemplateNode(this)))
		{
			BehaviorTreeComponent->OnTaskFinished(TemplateNode, EBTNodeResult::Succeeded);
			BehaviorTreeComponent = nullptr;
		}
	}
}

void UMinigunAttackTask::OnFire()
{
	if (UBlackboardComponent* BlackboardComp = BehaviorTreeComponent->GetBlackboardComponent())
	{
		if (BlackboardComp->GetValueAsObject("DetectPlayer"))
		{
			if (IsValid(GetWorld()))
			{
				GetWorld()->GetTimerManager().ClearTimer(LaunchTimer);
				int CountOfBullet = BlackboardComp->GetValueAsInt("CountOfBullet");
				if (AMinigunActor* MinigunActor = Cast<AMinigunActor>(BehaviorTreeComponent->GetAIOwner()->GetPawn()))
				{
					BlackboardComp->SetValueAsInt("CountOfBullet", CountOfBullet - 1);

					SpawnBullet();

					if (CountOfBullet - 1 == 0)
					{
						OnEndAbility();
					}
					else
					{
						GetWorld()->GetTimerManager().SetTimer(LaunchTimer, this, &UMinigunAttackTask::OnFire, BlackboardComp->GetValueAsFloat("FireRate"), false);
					}
				}
			}
		}
		else
		{
			OnEndAbility();
		}
	}
}

void UMinigunAttackTask::SpawnBullet()
{
	if (IsValid(GetWorld()))
	{
		if (UBlackboardComponent* BlackboardComp = BehaviorTreeComponent->GetBlackboardComponent())
		{
			if (AMinigunActor* MinigunActor = Cast<AMinigunActor>(BehaviorTreeComponent->GetAIOwner()->GetPawn()))
			{
				if (AMingunCharacter* Player = Cast<AMingunCharacter>(BlackboardComp->GetValueAsObject("DetectPlayer")))
				{
					MinigunActor->SetActorRotation(
						UKismetMathLibrary::FindLookAtRotation(MinigunActor->GetActorLocation(), Player->GetActorLocation()), ETeleportType::None);
				}

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				ABulletActor* Bullet = GetWorld()->SpawnActor<ABulletActor>(SpawnActor, MinigunActor->GetSpawnActorLocation(),
					MinigunActor->GetSpawnActorRotation(), ActorSpawnParams);

				Bullet->SetData(BlackboardComp->GetValueAsFloat("Damage"));

				if (IsValid(FireSound))
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, MinigunActor->GetActorLocation());
				}
			}
		}
	}
}
