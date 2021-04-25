// Fill out your copyright notice in the Description page of Project Settings.


#include "BrawlerAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ABrawlerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrawlerAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (BT_BrawlerAI != NULL) RunBehaviorTree(BT_BrawlerAI);
	if (PlayerPawn != NULL) GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
}