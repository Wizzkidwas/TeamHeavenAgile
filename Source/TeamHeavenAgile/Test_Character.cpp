// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Character.h"

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

void ATest_Character::PitchCamera(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ATest_Character::YawCamera(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}