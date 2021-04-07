// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Bullet.h"
#include "BTService_AimShootProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API UBTService_AimShootProjectile : public UBTService
{
	GENERATED_BODY()
	
protected:
	//Rotates Enemy towards Player and conducts Line Trace to see if bullet hit and if damage/force should occur.
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	UPROPERTY(EditAnywhere) USoundBase* ShotSoundEffect;		//Sound played on shot.
	UPROPERTY(EditAnywhere) float ShotSoundVolume = 1.0f;		//Volume of sound played on shot.
	UPROPERTY(EditAnywhere) TSubclassOf<ABullet> BulletClass;
};
