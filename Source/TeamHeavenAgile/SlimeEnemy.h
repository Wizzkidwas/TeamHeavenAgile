// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "SlimeAIController.h"
#include "SlimeEnemy.generated.h"

UCLASS()
class TEAMHEAVENAGILE_API ASlimeEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASlimeEnemy();
	UFUNCTION() void Initialise(int slimeSize);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UPROPERTY(EditAnywhere) TSubclassOf<ASlimeEnemy> slimeClass;
	UPROPERTY(EditAnywhere) UStaticMeshComponent* SlimeMesh;
	UPROPERTY(EditAnywhere) USphereComponent* CollisionMesh;
	UPROPERTY(EditAnywhere) int SlimeSize = 3;
	UPROPERTY(EditAnywhere) float BaseDamage = 10.0f;
	UPROPERTY(EditAnywhere) float SpawnOffset = 10.0f;
	UPROPERTY() float Damage = BaseDamage * SlimeSize;
	UPROPERTY(EditAnywhere) float BaseHealth = 20.0f;
	UPROPERTY() float Health = BaseHealth * SlimeSize;
	UPROPERTY() bool bHasHit = false;
};
