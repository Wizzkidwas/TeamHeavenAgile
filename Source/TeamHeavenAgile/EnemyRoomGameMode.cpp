// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRoomGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ObjectiveLockedDoor.h"
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
	int tempId = -1;
	//Spawns amount of Enemies equal to Target Points tags in locations specified.
	if (SlimeSpawns.Num() != 0 && SlimeClass) {
		for (AActor* SpawnPoint : SlimeSpawns) {
			FVector SpawnLocation = SpawnPoint->GetActorLocation();
			FRotator SpawnRotation = SpawnPoint->GetActorRotation();
			ASlimeEnemy* TempEnemy = GetWorld()->SpawnActor<ASlimeEnemy>(SlimeClass, SpawnLocation, SpawnRotation);
			tempId = EnemySpawned();
			TempEnemy->Initialise(SlimeSize, tempId);
		}
	}

	if (ChargerSpawns.Num() != 0 && ChargerClass) {
		for (AActor* SpawnPoint : ChargerSpawns) {
			FVector SpawnLocation = SpawnPoint->GetActorLocation();
			FRotator SpawnRotation = SpawnPoint->GetActorRotation();
			AChargerEnemy* TempEnemy = GetWorld()->SpawnActor<AChargerEnemy>(ChargerClass, SpawnLocation, SpawnRotation);
			tempId = EnemySpawned();
			TempEnemy->Initialise(tempId);
		}
	}

	if (SkeletonSpawns.Num() != 0 && SkeletonClass) {
		for (AActor* SpawnPoint : SkeletonSpawns) {
			FVector SpawnLocation = SpawnPoint->GetActorLocation();
			FRotator SpawnRotation = SpawnPoint->GetActorRotation();
			ASkeletonEnemy* TempEnemy = GetWorld()->SpawnActor<ASkeletonEnemy>(SkeletonClass, SpawnLocation, SpawnRotation);
			tempId = EnemySpawned();
			TempEnemy->Initialise(tempId);
		}
	}
	//Spawns Player in location specified.
	if (PlayerSpawn && PlayerClass) {
		FVector SpawnLocation = PlayerSpawn->GetActorLocation();
		FRotator SpawnRotation = PlayerSpawn->GetActorRotation();
		ATest_Character* TempPlayer = GetWorld()->SpawnActor<ATest_Character>(PlayerClass, SpawnLocation, SpawnRotation);
	}
}

void AEnemyRoomGameMode::EnemyDefeated(int EnemyId) {
	EnemiesSpawnedCount--;
	for (int i = 0; i < EnemiesInPlay.Num(); i++) {
		if (EnemiesInPlay[i] == EnemyId) EnemiesInPlay.RemoveAt(i);
	}

	if (EnemyId == CurrentTurn) NextId();
	
	if (EnemiesSpawnedCount == 0) {
		AllEnemiesDefeated();
	}
}

int AEnemyRoomGameMode::EnemySpawned() {
	EnemiesSpawnedCount++;
	EnemySpawnId++;
	EnemiesInPlay.Emplace(EnemySpawnId);
	return EnemySpawnId;
}

void AEnemyRoomGameMode::NextId()
{
	if ((EnemiesInPlayIndex + 1) >= EnemiesInPlay.Num()) EnemiesInPlayIndex = 0;
	else EnemiesInPlayIndex++;
	CurrentTurn = EnemiesInPlay[EnemiesInPlayIndex];
}

int AEnemyRoomGameMode::GetId()
{
	return CurrentTurn;
}

void AEnemyRoomGameMode::AllEnemiesDefeated()
{
	LockedDoor->Destroy();
}
