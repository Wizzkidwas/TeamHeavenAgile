// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateInRange.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API UBTService_UpdateInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere) float DistanceFromPlayerCutoff = 500.0f;
protected:
	//Checks Enemy can see Player to know if to shot Player or chase them.
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
