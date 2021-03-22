// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AimShootPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API UBTService_AimShootPlayer : public UBTService
{
	GENERATED_BODY()
	
protected:
	//Rotates Enemy towards Player and conducts Line Trace to see if bullet hit and if damage/force should occur.
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		float gunBaseDamage = 20.0f;							//Damage Enemy does to Player.
	UPROPERTY(EditAnywhere)
		float castRange = 10000.0f;								//Distance Enemy can fire Player from.
	UPROPERTY(EditAnywhere)
		float impulseForce = 500.0f;							//Amount of force Enemy shots have on environment and physics props (i.e. Ball).
	UPROPERTY(EditAnywhere) USoundBase* ShotSoundEffect;		//Sound played on shot.
	UPROPERTY(EditAnywhere) float ShotSoundVolume = 1.0f;		//Volume of sound played on shot.
};

