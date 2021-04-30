// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Character.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Test_PlayerController.h"
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

	Health = HealthTotal;

	if (swordClass) {
		AASword* Sword = GetWorld()->SpawnActor<AASword>(swordClass, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
		Sword->SetActorRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
		Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
		ATest_PlayerController* controllerRef = Cast<ATest_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if(controllerRef) controllerRef->UpdateSwordRef(Sword);
	}
}

float ATest_Character::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	//Sends damage notification through to controller to handle.
	GetController()->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return DamageAmount;
}