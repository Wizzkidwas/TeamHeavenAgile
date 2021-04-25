// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BrawlerAIController.h"
#include "BrawlerEnemy.generated.h"

class AEnemyRoomGameMode;

UCLASS()
class TEAMHEAVENAGILE_API ABrawlerEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABrawlerEnemy();
	UFUNCTION() void Initialise(int EnemyId);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY() AEnemyRoomGameMode* EnemyRoomGameModeRef;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere) float Health = 100.0f;
	UPROPERTY() int EnemyID = -1;
};
