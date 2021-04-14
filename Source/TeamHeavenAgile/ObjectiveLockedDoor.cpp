// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveLockedDoor.h"
#include "EnemyRoomGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObjectiveLockedDoor::AObjectiveLockedDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	SetRootComponent(DoorMesh);
}

void AObjectiveLockedDoor::BeginPlay()
{
	Super::BeginPlay();
	EnemyRoomGameModeRef = Cast<AEnemyRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(EnemyRoomGameModeRef) EnemyRoomGameModeRef->LockedDoor = this;
}