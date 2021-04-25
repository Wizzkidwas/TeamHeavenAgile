// Fill out your copyright notice in the Description page of Project Settings.


#include "BrawlerEnemy.h"
#include "EnemyRoomGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABrawlerEnemy::ABrawlerEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABrawlerEnemy::Initialise(int EnemyId)
{
	EnemyID = EnemyId;
	FString iD = FString::FromInt(EnemyID);
	Tags.Emplace(FName(*iD));
}

// Called when the game starts or when spawned
void ABrawlerEnemy::BeginPlay()
{
	Super::BeginPlay();
	AIControllerClass = ABrawlerAIController::StaticClass();
	SpawnDefaultController();
	DisableComponentsSimulatePhysics();
}

// Called every frame
void ABrawlerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABrawlerEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	EnemyRoomGameModeRef = Cast<AEnemyRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	//Drops Ball and updates Game mode upon death. Also activates respawn timer.
	if (Health <= 0) {
		if (EnemyRoomGameModeRef) EnemyRoomGameModeRef->EnemyDefeated(EnemyID);
		Destroy();
	}
	return DamageAmount;
}

