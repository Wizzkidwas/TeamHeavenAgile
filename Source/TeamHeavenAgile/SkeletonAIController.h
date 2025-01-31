// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SkeletonAIController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API ASkeletonAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere) UBehaviorTree* BT_SkeletonAI;

public:

};
