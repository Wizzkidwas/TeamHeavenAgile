// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlimeEnemy.h"
#include "ChargerEnemy.h"
#include "SkeletonEnemy.h"
#include "Test_Character.h"
#include "ObjectiveLockedDoor.h"
#include "EnemyRoomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API AEnemyRoomGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
		void EnemyDefeated(int EnemyId);
	UFUNCTION()
		int EnemySpawned();
	UFUNCTION()
		void NextId();
	UFUNCTION()
		int GetId();

	UPROPERTY(EditAnywhere)
		AObjectiveLockedDoor* LockedDoor;
protected:

	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void StartGame();
	UFUNCTION()
		void GameBeginSpawning();
	UFUNCTION()
		void AllEnemiesDefeated();

	UPROPERTY() TArray<AActor*> Targets;				  //Stores positions and rotations of all Target Points within Level for flitering.
	UPROPERTY() AActor* PlayerSpawn;					  //Position and Rotation for spawning Player.

	UPROPERTY() TArray<AActor*> TempSlimeSpawns;		  //Stores positions and rotations of all Slime spawns within Level for flitering.
	UPROPERTY() TArray<AActor*> SlimeSpawns;			  //Position and Rotation for spawning Slimes.
	UPROPERTY(EditAnywhere) TSubclassOf <ASlimeEnemy> SlimeClass;			//Blueprint used as a template to create Slime.
	UPROPERTY(EditAnywhere) int SlimeSize = 3;

	UPROPERTY() TArray<AActor*> TempChargerSpawns;		  //Stores positions and rotations of all Charger spawns within Level for flitering.
	UPROPERTY() TArray<AActor*> ChargerSpawns;			  //Position and Rotation for spawning Chargers.
	UPROPERTY(EditAnywhere) TSubclassOf <AChargerEnemy> ChargerClass;			//Blueprint used as a template to create Charger.

	UPROPERTY() TArray<AActor*> TempSkeletonSpawns;		  //Stores positions and rotations of all Skeleton spawns within Level for flitering.
	UPROPERTY() TArray<AActor*> SkeletonSpawns;			  //Position and Rotation for spawning Skeletons.
	UPROPERTY(EditAnywhere) TSubclassOf <ASkeletonEnemy> SkeletonClass;			//Blueprint used as a template to create Skeleton.

	UPROPERTY(EditAnywhere) TSubclassOf <ATest_Character> PlayerClass;			//Blueprint used as a template to create Player.
	UPROPERTY() TArray<int> EnemiesInPlay;
	UPROPERTY() int CurrentTurn = -1;
	UPROPERTY() int EnemySpawnId = -1;
	UPROPERTY() int EnemiesInPlayIndex = -1;

	UPROPERTY() int EnemiesSpawnedCount = 0;
};
