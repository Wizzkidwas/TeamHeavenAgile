// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomPosition.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FindRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Ensures function only works when EnemyAiController is active.
	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	FNavLocation RandomLocation;

	//Obtains random location within playable area to ensure Enemies have a higher chance of finding player.
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	NavSys->GetRandomReachablePointInRadius(AIActor->GetActorLocation(), RandomRadius, RandomLocation);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPosition"), RandomLocation);

	return EBTNodeResult::Succeeded;
}
