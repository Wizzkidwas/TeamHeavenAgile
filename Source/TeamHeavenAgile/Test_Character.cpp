// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Character.h"
#include "Engine/Engine.h"
// Sets default values
ATest_Character::ATest_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(GetMesh());
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(-400.0f, 0.0f, 350.0f), FRotator(-20.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 400.f;
	CameraSpringArm->CameraLagSpeed = 2.0f;
	CameraSpringArm->bEnableCameraLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ATest_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATest_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString Message = FString::Printf(TEXT("Current State: %s"), currentState));
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, Message);
}

// Called to bind functionality to input
void ATest_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forwards", this, &ATest_Character::ForwardMovement);
	PlayerInputComponent->BindAxis("Sideways", this, &ATest_Character::SidewaysMovement);
	PlayerInputComponent->BindAxis("CameraVertical", this, &ATest_Character::PitchCamera);
	PlayerInputComponent->BindAxis("CameraHorizontal", this, &ATest_Character::YawCamera);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATest_Character::JumpCharacter);
	PlayerInputComponent->BindAction("LeftAttack", IE_Pressed, this, &ATest_Character::LeftLightAttack);
	PlayerInputComponent->BindAction("RightAttack", IE_Pressed, this, &ATest_Character::RightLightAttack);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &ATest_Character::Dodge);
	PlayerInputComponent->BindAction("LeftHeavyAttack", IE_Pressed, this, &ATest_Character::LeftHeavyAttack);
	PlayerInputComponent->BindAction("RightHeavyAttack", IE_Pressed, this, &ATest_Character::RightHeavyAttack);

}

void ATest_Character::ForwardMovement(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ATest_Character::SidewaysMovement(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);

}

void ATest_Character::JumpCharacter()
{
	Jump();
}

void ATest_Character::Dodge()
{
	if (currentState == States::idle) {
		if (GetWorld()->GetTimerManager().IsTimerActive(DodgeActivateTimer)) {
			GetWorld()->GetTimerManager().SetTimer(DodgeTimer, this, &ATest_Character::ActionFinished, DodgeDuration, false);
			currentState = States::Dodge;
		}
		else {
			GetWorld()->GetTimerManager().SetTimer(DodgeActivateTimer, this, &ATest_Character::VacantTimeUp, DodgeActivateDuration, false);
		}
	}
}

void ATest_Character::LeftLightAttack()
{
	if (currentState == States::idle) {
		GetWorld()->GetTimerManager().SetTimer(LeftLightTimer, this, &ATest_Character::ActionFinished, LeftLightDuration, false);
		currentState = States::leftLight;
	}
}

void ATest_Character::LeftHeavyAttack()
{
	if (currentState == States::idle) {
		GetWorld()->GetTimerManager().SetTimer(LeftHeavyTimer, this, &ATest_Character::ActionFinished, LeftHeavyDuration, false);
		currentState = States::leftHeavy;
	}
}

void ATest_Character::RightLightAttack()
{
	if (currentState == States::idle) {
		GetWorld()->GetTimerManager().SetTimer(RightLightTimer, this, &ATest_Character::ActionFinished, RightLightDuration, false);
		currentState = States::rightLight;
	}
}

void ATest_Character::RightHeavyAttack()
{
	if (currentState == States::idle) {
		GetWorld()->GetTimerManager().SetTimer(RightHeavyTimer, this, &ATest_Character::ActionFinished, RightHeavyDuration, false);
		currentState = States::rightHeavy;
	}
}

void ATest_Character::ActionFinished()
{
	currentState = States::idle;
}

void ATest_Character::VacantTimeUp()
{
}

void ATest_Character::PitchCamera(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ATest_Character::YawCamera(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}