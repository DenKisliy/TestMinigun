// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/MinigunReloadTask.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UMinigunReloadTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	if (IsValid(GetWorld()))
	{
		if (!IsValid(BehaviorTreeComponent))
		{
			BehaviorTreeComponent = &OwnerComp;

			if (BlackboardComp->GetValueAsFloat("RechargeTime") > 0)
			{
				if (AMinigunActor* MinigunActor = Cast<AMinigunActor>(OwnerComp.GetAIOwner()->GetPawn()))
				{
					DefaultMaterial = MinigunActor->MinigunMesh->GetMaterial(0);
					if (IsValid(ReloadMaterial))
					{
						MinigunActor->MinigunMesh->SetMaterial(0, ReloadMaterial);
					}
				}

				GetWorld()->GetTimerManager().ClearTimer(LaunchTimer);
				GetWorld()->GetTimerManager().SetTimer(LaunchTimer, this, &UMinigunReloadTask::OnFinishReload, BlackboardComp->GetValueAsFloat("RechargeTime"), false);
				return EBTNodeResult::InProgress;
			}
		}
	}

    return EBTNodeResult::Failed;
}

void UMinigunReloadTask::OnEndAbility()
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

void UMinigunReloadTask::OnFinishReload()
{
	if (IsValid(GetWorld()))
	{
		GetWorld()->GetTimerManager().ClearTimer(LaunchTimer);
		if (UBlackboardComponent* BlackboardComp = BehaviorTreeComponent->GetBlackboardComponent())
		{
			BlackboardComp->SetValueAsInt("CountOfBullet", BlackboardComp->GetValueAsInt("MaxCountOfBullet"));

			if (AMinigunActor* MinigunActor = Cast<AMinigunActor>(BehaviorTreeComponent->GetAIOwner()->GetPawn()))
			{
				if (IsValid(DefaultMaterial))
				{
					MinigunActor->MinigunMesh->SetMaterial(0, DefaultMaterial);
				}

				if (IsValid(FinishReloadSound))
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), FinishReloadSound, MinigunActor->GetActorLocation());
				}
			}
		}

		OnEndAbility();
	}
}
