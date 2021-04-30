// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Charge.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_Charge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Ensures function only works when EnemyAiController is active.
	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	ChargerRef = Cast<AChargerEnemy>(OwnerComp.GetAIOwner()->GetCharacter());
	if (ChargerRef) ChargerRef->BeginChargePrep();

	return EBTNodeResult::Succeeded;
}
