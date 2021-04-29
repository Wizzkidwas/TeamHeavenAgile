// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuGameMode.h"
#include "Blueprint/UserWidget.h"

void AStartMenuGameMode::BeginPlay() {
	//Spawns Menu UI.
	Super::BeginPlay();
	MainMenuCount = CreateWidget(GetWorld(), MainMenuClass);
	if (MainMenuCount) MainMenuCount->AddToViewport();
}