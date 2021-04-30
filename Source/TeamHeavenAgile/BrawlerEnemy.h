// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "BrawlerAIController.h"
#include "BrawlerEnemy.generated.h"

class AEnemyRoomGameMode;

UCLASS()
class TEAMHEAVENAGILE_API ABrawlerEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABrawlerEnemy();
	UFUNCTION() void Initialise(int EnemyId);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void BeginSwipe();
private:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY() AEnemyRoomGameMode* EnemyRoomGameModeRef;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox;
	UPROPERTY() TArray<AActor*> TempActorsHit;
	UPROPERTY(EditAnywhere) float Damage = 15.0f;
	UPROPERTY() bool Swiping = false;
	UFUNCTION(BlueprintCallable)
		void SetSwiping(bool IsSwiping);
	UFUNCTION(BlueprintPure)
		bool GetSwiping();
	UFUNCTION()
		void SwipeOver();
	UPROPERTY()			    FTimerHandle SwipeTimer;
	UPROPERTY(EditAnywhere) float SwipeDuration = 2.0f;

	UPROPERTY(EditAnywhere) float Health = 100.0f;
	UPROPERTY() int EnemyID = -1;
};
