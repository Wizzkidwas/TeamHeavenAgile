// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyRoomGameMode.h"
#include "WaveRoomGameMode.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateEnemyInPlay.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API UBTService_UpdateEnemyInPlay : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY() AEnemyRoomGameMode* EnemyRoomGameModeRef;
	UPROPERTY() AWaveRoomGameMode* WaveRoomGameModeRef;
};
