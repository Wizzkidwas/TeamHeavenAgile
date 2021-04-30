// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyRoomGameMode.h"

UCustomGameInstance::UCustomGameInstance(const FObjectInitializer& ObjectInitializer) {
	
	UE_LOG(LogTemp, Warning, TEXT("GameInstanceConstructor"));
}

void UCustomGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstanceInit"));
}

void UCustomGameInstance::ConsoleTest()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstanceConsoleTest"));
}

void UCustomGameInstance::ConsoleTestParams(const FString MyString)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstanceConsoleTestParams %s"), *MyString);
}

void UCustomGameInstance::LoadNextLevel()
{
	CurrentRound++;
	if (CurrentRound % RoundsTillBossOption == 0) LoadSelectedLevel(-1);
	else LoadSelectedLevel(SelectRandomLevel());
}

int UCustomGameInstance::SelectRandomLevel()
{
	if (LevelPickArray.Num() < 1) RefreshLevelPickArray();
	int randNum = FMath::RandRange(0, LevelPickArray.Num()-1);
	int returnNum = LevelPickArray[randNum];
	LevelPickArray.RemoveAt(randNum);
	return returnNum;
}

void UCustomGameInstance::LoadSelectedLevel(int LevelSelected)
{
	switch(LevelSelected) {
	case -3:
		UGameplayStatics::OpenLevel(GetWorld(), EndScreenLevel);
		break;
	case -2:
		UGameplayStatics::OpenLevel(GetWorld(), MainMenuLevel);
		break;
	case -1:
		UGameplayStatics::OpenLevel(GetWorld(), BossLevel);
		break;
	case 0:
		UGameplayStatics::OpenLevel(GetWorld(), SmallStaircaseLevel);
		break;
	case 1:
		UGameplayStatics::OpenLevel(GetWorld(), PitLevel);
		break;
	case 2:
		UGameplayStatics::OpenLevel(GetWorld(), CageLevel);
		break;
	}
}

void UCustomGameInstance::RefreshLevelPickArray()
{
	LevelPickArray.Reset();
	for (int i = 0; i < TotalPickableLevelAmount; i++) {
		LevelPickArray.Emplace(i);
	}
}

void UCustomGameInstance::PlayerDied()
{
	PlayersCurrentLives--;
	if (PlayersCurrentLives > 0) BeginPlayerRespawnProcess();
	else LoadSelectedLevel(EndScreenLevelNum);
}

void UCustomGameInstance::BeginPlayerRespawnProcess()
{
	GetWorld()->GetTimerManager().SetTimer(PlayerRespawnTimer, this, &UCustomGameInstance::PlayerRespawnTimeUp, PlayerRespawnDuration, false);
}

void UCustomGameInstance::PlayerRespawnTimeUp()
{
	if (UGameplayStatics::GetGameMode(GetWorld())->GetClass()->IsChildOf(AEnemyRoomGameMode::StaticClass())) {
		AEnemyRoomGameMode* GameModeRef = Cast<AEnemyRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameModeRef->RespawnPlayer();
	}
}

float UCustomGameInstance::GetMusicVolume()
{
	return MusicVolume;
}

void UCustomGameInstance::SetMusicVolume(float NewVolume)
{
	MusicVolume = NewVolume;
}

float UCustomGameInstance::GetSoundVolume()
{
	return SoundVolume;
}

void UCustomGameInstance::SetSoundVolume(float NewVolume)
{
	SoundVolume = NewVolume;
}

int UCustomGameInstance::GetCurrentRound()
{
	return CurrentRound;
}

int UCustomGameInstance::GetPlayerCurrentLives()
{
	return PlayersCurrentLives;
}

bool UCustomGameInstance::GetPaused()
{
	return Paused;
}

void UCustomGameInstance::SetPaused(bool isPaused)
{
	Paused = isPaused;
}
