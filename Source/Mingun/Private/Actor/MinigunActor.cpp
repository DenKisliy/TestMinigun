// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MinigunActor.h"

// Sets default values
AMinigunActor::AMinigunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("CollisionComponent");
	CollisionComponent->InitCapsuleSize(55.f, 96.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	CollisionComponent->SetShouldUpdatePhysicsVolume(true);
	CollisionComponent->SetCanEverAffectNavigation(false);
	CollisionComponent->bDynamicObstacle = true;
	RootComponent = CollisionComponent;

	MinigunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MinigunMesh"));
	MinigunMesh->SetupAttachment(CollisionComponent);

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(CollisionComponent);

	SpawnArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrow"));
	if (SpawnArrowComponent)
	{
		SpawnArrowComponent->ArrowColor = FColor(255, 0, 0);
		SpawnArrowComponent->bTreatAsASprite = true;
		SpawnArrowComponent->bIsScreenSizeScaled = true;
		SpawnArrowComponent->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AMinigunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinigunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

