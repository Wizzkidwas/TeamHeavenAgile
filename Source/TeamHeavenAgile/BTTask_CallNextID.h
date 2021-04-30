// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyRoomGameMode.h"
#include "WaveRoomGameMode.h"
#include "BehaviorTree/Tasks/BTTask_GameplayTaskBase.h"
#include "BTTask_CallNextID.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API UBTTask_CallNextID : public UBTTask_GameplayTaskBase
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY() AEnemyRoomGameMode* EnemyRoomGameModeRef;
	UPROPERTY() AWaveRoomGameMode* WaveRoomGameModeRef;
};
