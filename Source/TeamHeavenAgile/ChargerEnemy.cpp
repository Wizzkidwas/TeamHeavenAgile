// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargerEnemy.h"
#include "EnemyRoomGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChargerEnemy::AChargerEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChargerEnemy::BeginPlay()
{
	Super::BeginPlay();
	AIControllerClass = AChargerAIController::StaticClass();
	SpawnDefaultController();
	DisableComponentsSimulatePhysics();
}

// Called every frame
void AChargerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AChargerEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	Health -= DamageAmount;
	EnemyRoomGameModeRef = Cast<AEnemyRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	//Drops Ball and updates Game mode upon death. Also activates respawn timer.
	if (Health <= 0) {
		if (EnemyRoomGameModeRef) EnemyRoomGameModeRef->EnemyDefeated();
		Destroy();
	}
	return DamageAmount;
}