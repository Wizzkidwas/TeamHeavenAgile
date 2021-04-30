// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargerEnemy.h"
#include "EnemyRoomGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChargerEnemy::AChargerEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
}

void AChargerEnemy::Initialise(int EnemyId)
{
	EnemyID = EnemyId;
	FString iD = FString::FromInt(EnemyID);
	Tags.Emplace(FName(*iD));
}

// Called when the game starts or when spawned
void AChargerEnemy::BeginPlay()
{
	Super::BeginPlay();
	AIControllerClass = AChargerAIController::StaticClass();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AChargerEnemy::OnOverlapBegin);
	SpawnDefaultController();
	DisableComponentsSimulatePhysics();
}

// Called every frame
void AChargerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (State == ChargeStates::Idle) {
		if (TempActorsHit.Num() != 0) {
			TempActorsHit.Empty();
		}
	}
}

ChargeStates AChargerEnemy::GetCurrentState()
{
	return State;
}

void AChargerEnemy::BeginChargePrep()
{
	GetWorld()->GetTimerManager().SetTimer(ChargePrepTimer, this, &AChargerEnemy::BeginCharge, ChargePrepDuration, false);
	State = ChargeStates::ChargePrep;
}

void AChargerEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begun"));
	if (State == ChargeStates::Charge)
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle check worked"));
		if (OtherActor->ActorHasTag("Hitable")) {
			if (!TempActorsHit.Contains(OtherActor) || (TempActorsHit.Num() == 0)) {
				TempActorsHit.Emplace(OtherActor);
				UE_LOG(LogTemp, Warning, TEXT("Hit Made"));
				//UGameplayStatics::PlaySound2D(GetWorld(), SwingSoundEffect, SwingSoundVolume, 1.0f, 0.0f);
				UGameplayStatics::ApplyDamage(OtherActor, Damage, GetController(), this, UDamageType::StaticClass());
				BeginChargeRecov();
			}
		}
		else if (Cast<ATest_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) {
			if (!TempActorsHit.Contains(OtherActor) || (TempActorsHit.Num() == 0)) {
				TempActorsHit.Emplace(OtherActor);
				UE_LOG(LogTemp, Warning, TEXT("Hit Made"));
				//UGameplayStatics::PlaySound2D(GetWorld(), SwingSoundEffect, SwingSoundVolume, 1.0f, 0.0f);
				UGameplayStatics::ApplyDamage(OtherActor, Damage, GetController(), this, UDamageType::StaticClass());
				BeginChargeRecov();
			}
		}
	}
}

float AChargerEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	Health -= DamageAmount;
	EnemyRoomGameModeRef = Cast<AEnemyRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	State = ChargeStates::Idle;
	//Drops Ball and updates Game mode upon death. Also activates respawn timer.
	if (Health <= 0) {
		if (EnemyRoomGameModeRef) EnemyRoomGameModeRef->EnemyDefeated(EnemyID);
		Destroy();
	}
	return DamageAmount;
}

void AChargerEnemy::BeginCharge()
{
	GetWorld()->GetTimerManager().SetTimer(ChargeTimer, this, &AChargerEnemy::ReturnToIdle, ChargeDuration, false);
	State = ChargeStates::Charge;
}

void AChargerEnemy::BeginChargeRecov()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ChargeTimer))GetWorld()->GetTimerManager().ClearTimer(ChargeTimer);
	GetWorld()->GetTimerManager().SetTimer(ChargeRecovTimer, this, &AChargerEnemy::ReturnToIdle, ChargeRecovDuration, false);
	State = ChargeStates::ChargeRecov;
}

void AChargerEnemy::ReturnToIdle()
{
	State = ChargeStates::Idle;
}
