// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateEnemyInPlay.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_UpdateEnemyInPlay::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	int tempId = -1;
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();
	if (AIActor) {
		if (UGameplayStatics::GetGameMode(GetWorld())->GetClass()->IsChildOf(AEnemyRoomGameMode::StaticClass())) {
			EnemyRoomGameModeRef = Cast<AEnemyRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			tempId = EnemyRoomGameModeRef->GetId();
			FString iD = FString::FromInt(tempId);
			//UE_LOG(LogTemp, Warning, TEXT("CurrentEnemyInPlay is %s"), *iD);
			if (AIActor->ActorHasTag(FName(*iD))) OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
			else OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}
		/*else if (UGameplayStatics::GetGameMode(GetWorld())->GetClass()->IsChildOf(AWaveRoomGameMode::StaticClass())) {
			WaveRoomGameModeRef = Cast<AWaveRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			tempId = WaveRoomGameModeRef->GetId();
			FString iD = FString::FromInt(tempId);
			if (AIActor->ActorHasTag(FName(*iD))) OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
			else OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}*/
	}
}
