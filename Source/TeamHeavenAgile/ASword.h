// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "AMelee.h"
#include "ASword.generated.h"

class ATest_PlayerController;

UCLASS()
class TEAMHEAVENAGILE_API AASword : public AAMelee
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere) USkeletalMeshComponent* SwordMesh;
	UPROPERTY(EditAnywhere) UCapsuleComponent* collisionCollider;
	UPROPERTY(EditAnywhere) float lightDamage = 15.0f;
	UPROPERTY(EditAnywhere) float heavyDamage = 40.0f;
	UPROPERTY() TArray<AActor*> TempActorsHit;
	UPROPERTY() ATest_PlayerController* characterRef;
	UPROPERTY(EditAnywhere)
		USoundBase* SwingSoundEffect;		//Sound played on swing.
	UPROPERTY(EditAnywhere)
		float SwingSoundVolume = 1.0f;		//Volume of sound played on swing.
};
