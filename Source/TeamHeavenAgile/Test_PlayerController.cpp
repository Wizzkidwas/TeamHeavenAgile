// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_PlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"


void ATest_PlayerController::BeginPlay() {
	Super::BeginPlay();

	MainMenuCount = CreateWidget(GetWorld(), MainMenuClass);

	PrimaryActorTick.bCanEverTick = true;
	//Obtains Player character and a reference to AGameDev1AssGameModeBase.
	PlayerCharacter = Cast<ATest_Character>(GetPawn());
	//Sets health and ammo to Blueprinted amount and displays counters.
	Health = HealthTotal;
	Stamina = StaminaTotal;
	PlayerHUDCount = CreateWidget(this, PlayerHUDClass);
	if (PlayerHUDCount) PlayerHUDCount->AddToViewport();
}


void ATest_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString message = TEXT("Error Message");

	switch (State)
	{
	case States::LeftLight:
		message = TEXT("State: leftLight");
		break;
	case States::LeftHeavy:
		message = TEXT("State: leftHeavy");
		break;
	case States::RightLight:
		message = TEXT("State: rightLight");
		break;
	case States::RightHeavy:
		message = TEXT("State: rightHeavy");
		break;
	case States::Dodge:
		message = TEXT("State: Dodge");
		break;
	case States::Block:
		message = TEXT("State: Block");
	case States::Idle:
		message = TEXT("State: idle");
		break;
	}
	//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, message);
}

void ATest_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAxis("Forwards", this, &ATest_PlayerController::ForwardMovement);
	InputComponent->BindAxis("Sideways", this, &ATest_PlayerController::SidewaysMovement);
	InputComponent->BindAxis("CameraVertical", this, &ATest_PlayerController::PitchCamera);
	InputComponent->BindAxis("CameraHorizontal", this, &ATest_PlayerController::YawCamera);
	//InputComponent->BindAction("Jump", IE_Pressed, this, &ATest_PlayerController::JumpCharacter);
	InputComponent->BindAction("LeftAttack", IE_Pressed, this, &ATest_PlayerController::LeftLightAttack);
	InputComponent->BindAction("RightAttack", IE_Pressed, this, &ATest_PlayerController::LeftHeavyAttack);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &ATest_PlayerController::ActivateDodge);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &ATest_PlayerController::ActivateCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &ATest_PlayerController::CancelCrouch);
	InputComponent->BindAction("Menu", IE_Pressed, this, &ATest_PlayerController::Menu);
	//InputComponent->BindAction("LeftHeavyAttack", IE_Pressed, this, &ATest_PlayerController::LeftHeavyAttack);
	//InputComponent->BindAction("RightHeavyAttack", IE_Pressed, this, &ATest_PlayerController::RightHeavyAttack);

}

States ATest_PlayerController::GetCurrentState()
{
	return State;
}

float ATest_PlayerController::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	//Tells GameMode to begin Respawn timer while dropping any Ball held and finally destroying Player Character.
	if (Health <= 0) {
		GameInstanceRef = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (GameInstanceRef) GameInstanceRef->PlayerDied();
		PlayerCharacter->Destroy();
		if (SwordRef) {
			SwordRef->Destroy();
			SwordRef = nullptr;
		}
	}
	return DamageAmount;
}

void ATest_PlayerController::ForwardMovement(float Value)
{
	if (PlayerCharacter && MenuNotOpened) PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector() * Value);
}

void ATest_PlayerController::SidewaysMovement(float Value)
{
	if (PlayerCharacter && MenuNotOpened) PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector() * Value);
}

//void ATest_PlayerController::JumpCharacter()
//{
//	if (PlayerCharacter) PlayerCharacter->Jump();
//}

void ATest_PlayerController::ActivateDodge()
{
	if (State == States::Idle && MenuNotOpened) {
		if (GetWorld()->GetTimerManager().IsTimerActive(DodgeActivateTimer) && Stamina >= DodgeStaminaCost) {
			if (PlayerCharacter) {
				FVector DodgeVector = FVector(PlayerCharacter->GetActorForwardVector().X * DodgeForce, PlayerCharacter->GetActorForwardVector().Y * DodgeForce, 0.0f);
				PlayerCharacter->LaunchCharacter(DodgeVector, true, false); //<-Need to swap FVector for current movement vector (i.e. rightback if s and d  pressed)
			}
			Stamina -= DodgeStaminaCost;
			GetWorld()->GetTimerManager().SetTimer(DodgeTimer, this, &ATest_PlayerController::ActionFinished, DodgeDuration, false);
			State = States::Dodge;
		}
		else if (MenuNotOpened) {
			GetWorld()->GetTimerManager().SetTimer(DodgeActivateTimer, this, &ATest_PlayerController::VacantTimeUp, DodgeActivateDuration, false);
		}
	}
}

void ATest_PlayerController::ActivateCrouch()
{
	if (State == States::Idle && PlayerCharacter->CanCrouch() && MenuNotOpened) {
		PlayerCharacter->Crouch();
	}
}

void ATest_PlayerController::CancelCrouch()
{
	if (State == States::Idle && MenuNotOpened) {
		PlayerCharacter->UnCrouch();
	}
}

void ATest_PlayerController::LeftLightAttack()
{
	if (State == States::Idle && Stamina >= LightStaminaCost && MenuNotOpened) {
		Stamina -= LightStaminaCost;
		GetWorld()->GetTimerManager().SetTimer(LeftLightTimer, this, &ATest_PlayerController::ActionFinished, LeftLightDuration, false);
		State = States::LeftLight;
	}
}

void ATest_PlayerController::LeftHeavyAttack()
{
	if (State == States::Idle && Stamina >= HeavyStaminaCost && MenuNotOpened) {
		Stamina -= HeavyStaminaCost;
		GetWorld()->GetTimerManager().SetTimer(LeftHeavyTimer, this, &ATest_PlayerController::ActionFinished, LeftHeavyDuration, false);
		State = States::LeftHeavy;
	}
}

void ATest_PlayerController::Menu()
{
	UE_LOG(LogTemp, Warning, TEXT("Menu called"));

	MenuNotOpened = !MenuNotOpened;
	bShowMouseCursor = !MenuNotOpened;
	bEnableClickEvents = !MenuNotOpened;
	bEnableMouseOverEvents = !MenuNotOpened;
	if (MainMenuCount) {
		UE_LOG(LogTemp, Warning, TEXT("Menu Count Exists"));
		GameInstanceRef = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (GameInstanceRef) {
			if (MenuNotOpened && MainMenuCount->IsInViewport()) {
				UE_LOG(LogTemp, Warning, TEXT("Menu visible and Menu Not opened"));
				MainMenuCount->RemoveFromViewport();
				GameInstanceRef->SetPaused(false);
			}
			else if (!MenuNotOpened && !(MainMenuCount->IsInViewport())) {
				UE_LOG(LogTemp, Warning, TEXT("Menu not visible and menu opened"));
				MainMenuCount->AddToViewport();
				GameInstanceRef->SetPaused(true);
				State = States::Idle;
			}
		}
	}
}

//void ATest_PlayerController::RightLightAttack()
//{
//	if (State == States::Idle) {
//
//		GetWorld()->GetTimerManager().SetTimer(RightLightTimer, this, &ATest_PlayerController::ActionFinished, RightLightDuration, false);
//		State = States::RightLight;
//	}
//}
//
//void ATest_PlayerController::RightHeavyAttack()
//{
//	if (State == States::Idle) {
//
//		GetWorld()->GetTimerManager().SetTimer(RightHeavyTimer, this, &ATest_PlayerController::ActionFinished, RightHeavyDuration, false);
//		State = States::RightHeavy;
//	}
//}

void ATest_PlayerController::ActionFinished()
{
	State = States::Idle;
	GetWorld()->GetTimerManager().SetTimer(StaminaRegenDelayTimer, this, &ATest_PlayerController::StaminaRegen, StaminaRegenDelayDuration, false);
}

void ATest_PlayerController::StaminaRegen()
{
	if (State == States::Idle && Stamina != StaminaTotal && MenuNotOpened)
	{
		if ((Stamina + StaminaRegenStepAmount) < StaminaTotal)
		{
			Stamina += StaminaRegenStepAmount;
		}
		else
		{
			Stamina = StaminaTotal;
			UGameplayStatics::PlaySound2D(GetWorld(), HealSoundEffect, HealSoundVolume, 1.0f, 0.0f);
			UE_LOG(LogTemp, Warning, TEXT("Stamina Sound Played"));
		}
		GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimer, this, &ATest_PlayerController::StaminaRegen, StaminaRegenDuration, false);
	}
}

void ATest_PlayerController::VacantTimeUp()
{
}

void ATest_PlayerController::PitchCamera(float AxisValue)
{
	if (PlayerCharacter && MenuNotOpened) PlayerCharacter->AddControllerPitchInput(AxisValue);
}

void ATest_PlayerController::YawCamera(float AxisValue)
{
	if (PlayerCharacter && MenuNotOpened) PlayerCharacter->AddControllerYawInput(AxisValue);
}

void ATest_PlayerController::ResumeGameButtonPressed()
{
	Menu();
}

void ATest_PlayerController::RecastPlayerCharacter()
{
	//Regrabs new PlayerCharacter after respawn.
	PlayerCharacter = Cast<ATest_Character>(GetPawn());
}

float ATest_PlayerController::GetHealth()
{
	return Health;
}

float ATest_PlayerController::GetHealthTotal()
{
	return HealthTotal;
}

void ATest_PlayerController::ResetHealth()
{
	Health = HealthTotal;
}

float ATest_PlayerController::GetStamina()
{
	return Stamina;
}

float ATest_PlayerController::GetStaminaTotal()
{
	return StaminaTotal;
}

void ATest_PlayerController::UpdateSwordRef(AASword* newRef)
{
	SwordRef = newRef;
}
