// Fill out your copyright notice in the Description page of Project Settings.


#include "EndScreenGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AEndScreenGameMode::BeginPlay() {
	Super::BeginPlay();
	EndScreenDisplayCount = CreateWidget(GetWorld(), EndScreenDisplayClass);
	if (EndScreenDisplayCount) EndScreenDisplayCount->AddToViewport();
	GetWorld()->GetTimerManager().SetTimer(EndScreenDisplayTimer, this, &AEndScreenGameMode::DisplayScreen, EndScreenDisplayDuration, false);

}

void AEndScreenGameMode::DisplayScreen()
{
	
	GetWorld()->GetTimerManager().SetTimer(EndScreenTimer, this, &AEndScreenGameMode::BackToMenu, EndScreenDuration, false);

}

void AEndScreenGameMode::BackToMenu()
{
	GameInstanceRef = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstanceRef) GameInstanceRef->LoadSelectedLevel(-2);
}
