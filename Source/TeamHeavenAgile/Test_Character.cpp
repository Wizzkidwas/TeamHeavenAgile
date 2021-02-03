// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Character.h"

// Sets default values
ATest_Character::ATest_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATest_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATest_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

