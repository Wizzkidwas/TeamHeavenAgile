// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Test_Character.h"
#include "Math/UnrealMathUtility.h"
#include "Test_PlayerController.generated.h"

/**
 *
 */

UENUM()
enum class States : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Block		UMETA(DisplayName = "Block"),
	LeftLight	UMETA(DisplayName = "LeftLight"),
	LeftHeavy	UMETA(DisplayName = "LeftHeavy"),
	RightLight	UMETA(DisplayName = "RightLight"),
	RightHeavy	UMETA(DisplayName = "RightHeavy"),
	Dodge		UMETA(DisplayName = "Dodge"),
};

UCLASS()
class TEAMHEAVENAGILE_API ATest_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent();

	UFUNCTION() States GetCurrentState();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status) TEnumAsByte<States> State = States::Idle;

	UPROPERTY()
		ATest_Character* PlayerCharacter;
private:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void ForwardMovement(float Value);
	void SidewaysMovement(float Value);
	void ActivateDodge();
	void ActivateCrouch();
	void CancelCrouch();
	void LeftLightAttack();
	void LeftHeavyAttack();
	void ActionFinished();
	void StaminaRegen();
	void VacantTimeUp();
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);

	UFUNCTION(BlueprintPure)
		float GetHealth();
	UFUNCTION(BlueprintPure)
		float GetHealthTotal();
	UFUNCTION(BlueprintPure)
		float GetStamina();
	UFUNCTION(BlueprintPure)
		float GetStaminaTotal();

	UPROPERTY(EditAnywhere)
		float HealthTotal = 100.0f;
	UPROPERTY()
		float Health = HealthTotal;

	UPROPERTY(EditAnywhere)
		float StaminaTotal = 100.0f;
	UPROPERTY()
		float Stamina = StaminaTotal;

	UPROPERTY(EditAnywhere)
		float DodgeStaminaCost = 40.0f;
	UPROPERTY(EditAnywhere)
		float LightStaminaCost = 20.0f;
	UPROPERTY(EditAnywhere)
		float HeavyStaminaCost = 40.0f;

	UPROPERTY(EditAnywhere)
		float DodgeForce = 100.0f;

	UPROPERTY()			    FTimerHandle DodgeTimer;
	UPROPERTY(EditAnywhere) float DodgeDuration = 2.0f;
	UPROPERTY()			    FTimerHandle DodgeActivateTimer;
	UPROPERTY(EditAnywhere) float DodgeActivateDuration = 2.0f;
	UPROPERTY()			    FTimerHandle LeftLightTimer;
	UPROPERTY(EditAnywhere) float LeftLightDuration = 2.0f;
	UPROPERTY()			    FTimerHandle LeftHeavyTimer;
	UPROPERTY(EditAnywhere) float LeftHeavyDuration = 2.0f;
	UPROPERTY()			    FTimerHandle RightLightTimer;
	UPROPERTY(EditAnywhere) float RightLightDuration = 2.0f;
	UPROPERTY()			    FTimerHandle RightHeavyTimer;
	UPROPERTY(EditAnywhere) float RightHeavyDuration = 2.0f;
	UPROPERTY()			    FTimerHandle StaminaRegenDelayTimer;
	UPROPERTY(EditAnywhere) float StaminaRegenDelayDuration = 2.0f;
	UPROPERTY()			    FTimerHandle StaminaRegenTimer;
	UPROPERTY(EditAnywhere) float StaminaRegenDuration = 0.25f;
	UPROPERTY(EditAnywhere) float StaminaRegenStepAmount = 5.0f;
	UPROPERTY(EditAnywhere)
		USoundBase* HealSoundEffect;		//Sound played when healing.
	UPROPERTY(EditAnywhere)
		float HealSoundVolume = 1.0f;		//Volume of sound played when healing.
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> PlayerHUDClass;
	UPROPERTY() UUserWidget* PlayerHUDCount;
};