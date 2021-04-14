// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateInRange.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Math/Vector.h"

void UBTService_UpdateInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	float Distance = -1;
	if (AIActor && PlayerPawn) Distance = FVector::Dist(AIActor->GetActorLocation(), PlayerPawn->GetActorLocation());

	if (Distance < 0) {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
	else if (Distance < DistanceFromPlayerCutoff) {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}