// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AimShootPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"

void UBTService_AimShootPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* EnemyAIController = OwnerComp.GetAIOwner();				 //Controller that possesses the Enemy.
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);		 //Player that the Enemy is trying to shoot.
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();					 //Enemy that is firing the shot.

	//Ensures Enemy is looking at Player when firing.
	EnemyAIController->SetFocus(PlayerPawn);

	//Plays gunfire sound at Enemy location
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShotSoundEffect, AIActor->GetActorLocation(), ShotSoundVolume, 1.0f, 0.0f);

	//Endpoint of line trace that checks if bullet hit Player.
	FVector end = AIActor->GetActorLocation() + AIActor->GetActorForwardVector() * castRange;

	FHitResult Hit;								   //Stores hit information after line trace.
	FCollisionQueryParams lineTraceParams;		   //Configuration for the line trace to stop Enemy shooting themselves.

	lineTraceParams.AddIgnoredActor(AIActor);
	bool bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, AIActor->GetActorLocation(), end, ECC_Pawn, lineTraceParams); //Checks hit was made to avoid possible memory leaks.
	if (bDidHit && Hit.GetActor() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *Hit.GetActor()->GetName());
		if (Hit.GetActor()->FindComponentByClass(UCharacterMovementComponent::StaticClass())) {		 //Stops physics force being applied to objects that can't handle physics.

		}
		else {
			UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());	//Retrieves actor that was shot to add force.
			RootComp->AddImpulse(AIActor->GetActorForwardVector() * impulseForce * RootComp->GetMass());
		}
		UGameplayStatics::ApplyDamage(Hit.GetActor(), gunBaseDamage, EnemyAIController, AIActor, UDamageType::StaticClass()); //Applies damage to shot actor. Requires them to have takeDamage function.
	}
}
