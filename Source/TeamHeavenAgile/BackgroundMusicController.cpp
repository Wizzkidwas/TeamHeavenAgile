// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundMusicController.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABackgroundMusicController::ABackgroundMusicController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABackgroundMusicController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("MusicBeginPlayCalled"));
	ChooseMusic();
}

void ABackgroundMusicController::ChooseMusic()
{
	PlaylistChoice = FMath::RandRange(1, 4);	// Chooses between the 4 playlists
	UE_LOG(LogTemp, Warning, TEXT("Playlist chosen: %d"), PlaylistChoice);
	if (PlaylistChoice == 4)
	{
		PlayBossMusic();	// As the boss playlist is only one song, it will be called instantly
	}
	else	// The other playlists have 5 songs each, so a specific song needs to be chosen now
	{
		int songIndex = FMath::RandRange(1, 5);
		UE_LOG(LogTemp, Warning, TEXT("Index chosen: %d"), songIndex);
		switch (PlaylistChoice)	// Determines which playlist to send the random index to
		{
		case 1:
			PlayCalmMusic(songIndex);
			break;
		case 2:
			PlayMediumMusic(songIndex);
			break;
		case 3:
			PlayIntenseMusic(songIndex);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Default Called"));
			break;
		}
	}
}

// Given the random index, plays the corresponding calm song
void ABackgroundMusicController::PlayCalmMusic(int index)
{
	UE_LOG(LogTemp, Warning, TEXT("Calm Playlist chosen"));
	switch (index)
	{
	case 1:
		UGameplayStatics::PlaySound2D(GetWorld(), Calm1, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Calm 1 Song Played"));
		break;
	case 2:
		UGameplayStatics::PlaySound2D(GetWorld(), Calm2, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Calm 2 Song Played"));
		break;
	case 3:
		UGameplayStatics::PlaySound2D(GetWorld(), Calm3, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Calm 3 Song Played"));
		break;
	case 4:
		UGameplayStatics::PlaySound2D(GetWorld(), Calm4, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Calm 4 Song Played"));
		break;
	case 5:
		UGameplayStatics::PlaySound2D(GetWorld(), Calm5, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Calm 5 Song Played"));
		break;
	}
}

// Given the random index, plays the corresponding calm song
void ABackgroundMusicController::PlayMediumMusic(int index)
{
	UE_LOG(LogTemp, Warning, TEXT("Medium Playlist chosen"));
	switch (index)
	{
	case 1:
		UGameplayStatics::PlaySound2D(GetWorld(), Medium1, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Medium 1 Song Played"));
		break;
	case 2:
		UGameplayStatics::PlaySound2D(GetWorld(), Medium2, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Medium 2 Song Played"));
		break;
	case 3:
		UGameplayStatics::PlaySound2D(GetWorld(), Medium3, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Medium 3 Song Played"));
		break;
	case 4:
		UGameplayStatics::PlaySound2D(GetWorld(), Medium4, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Medium 4 Song Played"));
		break;
	case 5:
		UGameplayStatics::PlaySound2D(GetWorld(), Medium5, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Medium 5 Song Played"));
		break;
	}
}

// Given the random index, plays the corresponding calm song
void ABackgroundMusicController::PlayIntenseMusic(int index)
{
	UE_LOG(LogTemp, Warning, TEXT("Intense Playlist chosen"));
	switch (index)
	{
	case 1:
		UGameplayStatics::PlaySound2D(GetWorld(), Intense1, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Intense 1 Song Played"));
		break;
	case 2:
		UGameplayStatics::PlaySound2D(GetWorld(), Intense2, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Intense 2 Song Played"));
		break;
	case 3:
		UGameplayStatics::PlaySound2D(GetWorld(), Intense3, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Intense 3 Song Played"));
		break;
	case 4:
		UGameplayStatics::PlaySound2D(GetWorld(), Intense4, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Intense 4 Song Played"));
		break;
	case 5:
		UGameplayStatics::PlaySound2D(GetWorld(), Intense5, BGMVolume, 1.0f, 0.0f);
		UE_LOG(LogTemp, Warning, TEXT("Intense 5 Song Played"));
		break;
	}
}

void ABackgroundMusicController::PlayBossMusic()
{
	UGameplayStatics::PlaySound2D(GetWorld(), BossMusic, BGMVolume, 1.0f, 0.0f);
	UE_LOG(LogTemp, Warning, TEXT("Boss Song Played"));
}

