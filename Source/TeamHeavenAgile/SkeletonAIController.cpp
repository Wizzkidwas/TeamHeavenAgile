// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASkeletonAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkeletonAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (BT_SkeletonAI != NULL) RunBehaviorTree(BT_SkeletonAI);
	if (PlayerPawn != NULL) GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
}