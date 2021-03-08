// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeEnemy.h"

// Sets default values
ASlimeEnemy::ASlimeEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SlimeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slime"));
	SetRootComponent(SlimeMesh);
	SlimeMesh->SetNotifyRigidBodyCollision(true);
	SlimeMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ASlimeEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlimeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlimeEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ASlimeEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	Health -= DamageAmount;

	if (Health <= 0) {
		Destroy();
	}
	return DamageAmount;
}