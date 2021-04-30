// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Swipe.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_Swipe::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Ensures function only works when EnemyAiController is active.
	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	BrawlerRef = Cast<ABrawlerEnemy>(OwnerComp.GetAIOwner()->GetCharacter());
	if (BrawlerRef) BrawlerRef->BeginSwipe();
	
	return EBTNodeResult::Succeeded;
}

