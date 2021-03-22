// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdatePlayerPosition.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API UBTService_UpdatePlayerPosition : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	//Used to ensure Enemy chases Player when seen.
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

