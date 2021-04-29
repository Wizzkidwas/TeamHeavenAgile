// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomGameInstance.h"
#include "BackgroundMusicController.generated.h"

UCLASS()
class TEAMHEAVENAGILE_API ABackgroundMusicController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABackgroundMusicController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
		UCustomGameInstance* GameInstanceRef;

public:	
	UPROPERTY(EditAnywhere) USoundBase* Calm1;
	UPROPERTY(EditAnywhere) USoundBase* Calm2;
	UPROPERTY(EditAnywhere) USoundBase* Calm3;
	UPROPERTY(EditAnywhere) USoundBase* Calm4;
	UPROPERTY(EditAnywhere) USoundBase* Calm5;
	UPROPERTY(EditAnywhere) USoundBase* Medium1;
	UPROPERTY(EditAnywhere) USoundBase* Medium2;
	UPROPERTY(EditAnywhere) USoundBase* Medium3;		// Sound bases to be allocated in blueprint
	UPROPERTY(EditAnywhere) USoundBase* Medium4;
	UPROPERTY(EditAnywhere) USoundBase* Medium5;
	UPROPERTY(EditAnywhere) USoundBase* Intense1;
	UPROPERTY(EditAnywhere) USoundBase* Intense2;
	UPROPERTY(EditAnywhere) USoundBase* Intense3;		
	UPROPERTY(EditAnywhere) USoundBase* Intense4;
	UPROPERTY(EditAnywhere) USoundBase* Intense5;
	UPROPERTY(EditAnywhere) USoundBase* BossMusic;
	UPROPERTY(EditAnywhere)
		float BGMVolume = 1.0f;		// Volume of BGM
private:
	UFUNCTION()
		void ChooseMusic();

	UFUNCTION()
		void GetVolume();

	UFUNCTION()
		void PlayCalmMusic(int index);

	UFUNCTION()
		void PlayMediumMusic(int index);

	UFUNCTION()
		void PlayIntenseMusic(int index);

	UFUNCTION()
		void PlayBossMusic();


	UPROPERTY() USoundBase* CalmMusicList[5] = { Calm1, Calm2, Calm3, Calm4, Calm5 };	// Array of songs to act as a "playlist"
	UPROPERTY() USoundBase* MediumMusicList[5] = { Medium1, Medium2, Medium3, Medium4, Medium5 };
	UPROPERTY() USoundBase* IntenseMusicList[5] = { Intense1, Intense2, Intense3, Intense4, Intense5 };

	UPROPERTY() int PlaylistChoice = 0;
};