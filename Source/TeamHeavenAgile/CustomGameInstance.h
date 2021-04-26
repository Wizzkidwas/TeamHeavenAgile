// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEAMHEAVENAGILE_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UCustomGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init();
	UFUNCTION(Exec)
		void ConsoleTest();
	UFUNCTION(Exec)
		void ConsoleTestParams(const FString MyString);

	UFUNCTION(Exec)
		void LoadNextLevel();
	UFUNCTION(Exec)
		int SelectRandomLevel();
	UFUNCTION(Exec)
		void LoadSelectedLevel(int LevelSelected);
	UFUNCTION(Exec)
		void RefreshLevelPickArray();

	UFUNCTION()
		void PlayerDied();
	UFUNCTION()
		void BeginPlayerRespawnProcess();
	UFUNCTION()
		void PlayerRespawnTimeUp();

	UFUNCTION(BlueprintPure)
		int GetMusicVolume();
	UFUNCTION(BlueprintPure)
		int GetSoundVolume();
	
	UFUNCTION(BlueprintPure)
		int GetCurrentRound();
	UFUNCTION(BlueprintPure)
		int GetPlayerCurrentLives();

private:
	UPROPERTY(EditAnywhere)
		int PlayersTotalLives = 3;
	UPROPERTY()
		int PlayersCurrentLives = PlayersTotalLives;
	UPROPERTY(EditAnywhere) 
		float PlayerRespawnDuration = 3.0f;				//Adjustable time it takes to respawn player.
	UPROPERTY() 
		FTimerHandle PlayerRespawnTimer;								//Handle for player respawn timer.

	UPROPERTY()
		int CurrentRound = 0;
	UPROPERTY(EditAnywhere)
		int RoundsTillBossOption = 5;
	UPROPERTY()
		int TotalPickableLevelAmount = 2;
	UPROPERTY()
		TArray<int> LevelPickArray;

	UPROPERTY()
		int MusicVolume = 100;
	UPROPERTY()
		int SoundVolume = 100;

	UPROPERTY(EditAnywhere)
		FName EndScreenLevel;
	UPROPERTY(EditAnywhere)
		int EndScreenLevelNum = -3;
	UPROPERTY(EditAnywhere)
		FName MainMenuLevel;
	UPROPERTY(EditAnywhere)
		int  MainMenuLevelNum = -2;
	UPROPERTY(EditAnywhere)
		FName BossLevel;
	UPROPERTY(EditAnywhere)
		int BossLevelNum = -1;
	UPROPERTY(EditAnywhere)
		FName SmallStaircaseLevel;
	UPROPERTY(EditAnywhere)
		int SmallStaircaseLevelNum = 0;
	UPROPERTY(EditAnywhere)
		FName PitLevel;
	UPROPERTY(EditAnywhere)
		int PitLevelNum = 1;
};
