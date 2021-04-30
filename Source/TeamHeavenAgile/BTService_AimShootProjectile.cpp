// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AimShootProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"

void UBTService_AimShootProjectile::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* EnemyAIController = OwnerComp.GetAIOwner();				 //Controller that possesses the Enemy.
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);		 //Player that the Enemy is trying to shoot.
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();					 //Enemy that is firing the shot.

	//Ensures Enemy is looking at Player when firing.
	EnemyAIController->SetFocus(PlayerPawn);

	//Plays gunfire sound at Enemy location
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShotSoundEffect, AIActor->GetActorLocation(), ShotSoundVolume, 1.0f, 0.0f);

	if (BulletClass) {
		FVector SpawnLocation = AIActor->GetActorLocation();
		FRotator SpawnRotation = AIActor->GetActorRotation();
		ABullet* TempBall = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation);
		TempBall->SetOwner(AIActor);
	}
}
