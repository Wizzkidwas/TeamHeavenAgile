// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateIsPaused.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_UpdateIsPaused::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	GameInstanceRef = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	bool IsPaused = false;
	if (GameInstanceRef) IsPaused = GameInstanceRef->GetPaused();
	
	if (!IsPaused) {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
}
