// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRoomGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ObjectiveLockedDoor.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/TargetPoint.h"

void AEnemyRoomGameMode::BeginPlay() {
	Super::BeginPlay();
	StartGame();
}

void AEnemyRoomGameMode::StartGame()
{
	//Grabs locations of spawns to feed to RoundBeginSpawning.
	if (SlimeClass && PlayerClass) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Targets);
		for (AActor* Waypoint : Targets) {
			if (Waypoint->ActorHasTag(TEXT("SlimeSpawn"))) {
				SlimeSpawns.Emplace(Waypoint);
			}
			else if (Waypoint->ActorHasTag(TEXT("PlayerSpawn"))) {
				PlayerSpawn = Waypoint;
			}
		}
		GameBeginSpawning();
	}
}

void AEnemyRoomGameMode::GameBeginSpawning()
{
	//Spawns amount of Enemies equal to Target Points tags in locations specified.
	if (SlimeSpawns.Num() != 0 && SlimeClass) {
		for (AActor* SpawnPoint : SlimeSpawns) {
			FVector SpawnLocation = SpawnPoint->GetActorLocation();
			FRotator SpawnRotation = SpawnPoint->GetActorRotation();
			ASlimeEnemy* TempEnemy = GetWorld()->SpawnActor<ASlimeEnemy>(SlimeClass, SpawnLocation, SpawnRotation);
			EnemySpawned();
		}
	}
	//Spawns Player in location specified.
	if (PlayerSpawn && PlayerClass) {
		FVector SpawnLocation = PlayerSpawn->GetActorLocation();
		FRotator SpawnRotation = PlayerSpawn->GetActorRotation();
		ATest_Character* TempPlayer = GetWorld()->SpawnActor<ATest_Character>(PlayerClass, SpawnLocation, SpawnRotation);
	}
}

void AEnemyRoomGameMode::EnemyDefeated() {
	EnemiesSpawnedCount--;
	if (EnemiesSpawnedCount == 0) {
		AllEnemiesDefeated();
	}
}

void AEnemyRoomGameMode::EnemySpawned() {
	EnemiesSpawnedCount++;
}

void AEnemyRoomGameMode::AllEnemiesDefeated()
{
	LockedDoor->Destroy();
}

