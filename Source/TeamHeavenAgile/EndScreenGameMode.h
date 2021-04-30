// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameInstance.h"
#include "EndScreenGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API AEndScreenGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	//Spawns Menu UI and plays background music.
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void DisplayScreen();
	UFUNCTION()
		void BackToMenu();
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> EndScreenDisplayClass;						//Blueprint to create and attach Main Menu UI to viewport.
	UPROPERTY()
		UUserWidget* EndScreenDisplayCount;									//Monitors UI from Inception and is used as an interface to the UI.
	UPROPERTY()
		UCustomGameInstance* GameInstanceRef;
	UPROPERTY()			    FTimerHandle EndScreenTimer;
	UPROPERTY(EditAnywhere) float EndScreenDuration = 8.0f;
	UPROPERTY()			    FTimerHandle EndScreenDisplayTimer;
	UPROPERTY(EditAnywhere) float EndScreenDisplayDuration = 2.0f;
};
