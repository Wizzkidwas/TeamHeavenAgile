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

	if (!PlayerPawn) {
		return EBTNodeResult::Failed;
	}
	AAIController* EnemyAIController = OwnerComp.GetAIOwner();				 //Controller that possesses the Enemy.
	//AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	FNavLocation RandomLocation;

	//Obtains random location within playable area to ensure Enemies have a higher chance of finding player.
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	FNavLocation NavPoint;
	FVector QueryingExtent = FVector(50.0f, 50.0f, 250.0f);
	bool OnMesh = NavSys->ProjectPointToNavigation(PlayerPawn->GetActorLocation(), NavPoint, QueryingExtent);
 	if (OnMesh) {
		for (int i = 0; i < CycleAmount; i++) {
			if (NavSys->GetRandomReachablePointInRadius(NavPoint, RandomRadius, RandomLocation) && FVector::Dist(NavPoint, RandomLocation) < DistanceFromPlayerCutoff) break;
		}  //Might cause an issue. Should just expand get enemy to stop once its reached certain distance. 

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPosition"), RandomLocation);

		return EBTNodeResult::Succeeded;
	}
	else OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPosition"), NavPoint);
	return EBTNodeResult::Succeeded;
}