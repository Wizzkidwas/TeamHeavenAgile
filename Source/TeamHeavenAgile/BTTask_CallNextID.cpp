// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CallNextID.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_CallNextID::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Ensures function only works when EnemyAiController is active.
	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	if (UGameplayStatics::GetGameMode(GetWorld())->GetClass()->IsChildOf(AEnemyRoomGameMode::StaticClass())){
		EnemyRoomGameModeRef = Cast<AEnemyRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if(EnemyRoomGameModeRef) EnemyRoomGameModeRef->NextId();
	}
	/*else if (UGameplayStatics::GetGameMode(GetWorld())->GetClass()->IsChildOf(AWaveRoomGameMode::StaticClass())){
		WaveRoomGameModeRef = Cast<AWaveRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (WaveRoomGameModeRef) WaveRoomGameModeRef->NextId();
	}*/

	return EBTNodeResult::Succeeded;
}
