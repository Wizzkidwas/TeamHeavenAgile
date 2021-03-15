// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveLockedDoor.generated.h"

class AEnemyRoomGameMode;

UCLASS()
class TEAMHEAVENAGILE_API AObjectiveLockedDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveLockedDoor();
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere) UStaticMeshComponent* DoorMesh;
	UPROPERTY() AEnemyRoomGameMode* EnemyRoomGameModeRef;
};
