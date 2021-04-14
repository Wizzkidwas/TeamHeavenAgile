// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargerAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AChargerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChargerAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (BT_ChargerAI != NULL) RunBehaviorTree(BT_ChargerAI);
	if (PlayerPawn != NULL) GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), PlayerPawn->GetActorLocation());
}