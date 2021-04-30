// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "ChargerAIController.h"
#include "ChargerEnemy.generated.h"

class AEnemyRoomGameMode;

UENUM()
enum class ChargeStates : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	ChargePrep	UMETA(DisplayName = "ChargePrep"),
	Charge   	UMETA(DisplayName = "Charge"),
	ChargeRecov	UMETA(DisplayName = "ChargeRecov"),
};

UCLASS()
class TEAMHEAVENAGILE_API AChargerEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChargerEnemy();
	UFUNCTION() void Initialise(int EnemyId);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() ChargeStates GetCurrentState();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status) TEnumAsByte<ChargeStates> State = ChargeStates::Idle;

	UFUNCTION()
		void BeginChargePrep();
private:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY() AEnemyRoomGameMode* EnemyRoomGameModeRef;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void BeginCharge();
	UFUNCTION()
		void BeginChargeRecov();
	UFUNCTION()
		void ReturnToIdle();

	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox;
	UPROPERTY() TArray<AActor*> TempActorsHit;
	UPROPERTY(EditAnywhere) float Damage = 40.0f;

	UPROPERTY()			    FTimerHandle ChargePrepTimer;
	UPROPERTY(EditAnywhere) float ChargePrepDuration = 2.0f;
	UPROPERTY()			    FTimerHandle ChargeTimer;
	UPROPERTY(EditAnywhere) float ChargeDuration = 5.0f;
	UPROPERTY()			    FTimerHandle ChargeRecovTimer;
	UPROPERTY(EditAnywhere) float ChargeRecovDuration = 2.0f;

	UPROPERTY(EditAnywhere) float Health = 100.0f;
	UPROPERTY() int EnemyID = -1;
};
