// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindRandPositionByPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API UBTTask_FindRandPositionByPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere) float RandomRadius = 2000.0f;

protected:
	//Obtains random location within playable area to ensure Enemies have a higher chance of finding player or Ball.
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
