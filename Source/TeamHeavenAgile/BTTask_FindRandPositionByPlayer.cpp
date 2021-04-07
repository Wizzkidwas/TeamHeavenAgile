// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandPositionByPlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Math/Vector.h"

EBTNodeResult::Type UBTTask_FindRandPositionByPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Ensures function only works when EnemyAiController is active.
	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);	
	//AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	FNavLocation RandomLocation;

	//Obtains random location within playable area to ensure Enemies have a higher chance of finding player.
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	do  {
		NavSys->GetRandomReachablePointInRadius(PlayerPawn->GetActorLocation(), RandomRadius, RandomLocation);
	} while (FVector::Dist(PlayerPawn->GetActorLocation(), RandomLocation) < DistanceFromPlayerCutoff); //Might cause an issue. Should just expand get enemy to stop once its reached certain distance. 

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPosition"), RandomLocation);

	return EBTNodeResult::Succeeded;
}