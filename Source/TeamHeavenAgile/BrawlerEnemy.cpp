// Fill out your copyright notice in the Description page of Project Settings.


#include "BrawlerEnemy.h"

// Sets default values
ABrawlerEnemy::ABrawlerEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABrawlerEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrawlerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABrawlerEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

