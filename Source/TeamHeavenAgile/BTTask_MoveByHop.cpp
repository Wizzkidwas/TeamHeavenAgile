// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveByHop.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_MoveByHop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Ensures function only works when EnemyAiController is active.
	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	AAIController* EnemyAIController = OwnerComp.GetAIOwner();	
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	EnemyAIController->SetFocus(PlayerPawn);

	float DistanceBetween = -1.0f;
	if (AIActor && PlayerPawn) DistanceBetween = FVector::Dist(AIActor->GetActorLocation(), PlayerPawn->GetActorLocation());
	if (DistanceBetween > 0.0f) {
		FVector HopForce = FVector(PlayerPawn->GetActorForwardVector().X * DistanceBetween * ForceAdjustment, PlayerPawn->GetActorForwardVector().Y * DistanceBetween * ForceAdjustment, PlayerPawn->GetActorUpVector().Z * DistanceBetween * ForceAdjustment);
		PlayerPawn->LaunchPawn(HopForce, true, true);
	}
	return EBTNodeResult::Succeeded;

	//Have it be feed in a target (i.e. randPosition or PlayerPosition)
}

