// Fill out your copyright notice in the Description page of Project Settings.


#include "BrawlerEnemy.h"
#include "EnemyRoomGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABrawlerEnemy::ABrawlerEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));

}

void ABrawlerEnemy::Initialise(int EnemyId)
{
	EnemyID = EnemyId;
	FString iD = FString::FromInt(EnemyID);
	Tags.Emplace(FName(*iD));
}

// Called when the game starts or when spawned
void ABrawlerEnemy::BeginPlay()
{
	Super::BeginPlay();
	AIControllerClass = ABrawlerAIController::StaticClass();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABrawlerEnemy::OnOverlapBegin);
	SpawnDefaultController();
	DisableComponentsSimulatePhysics();
}

// Called every frame
void ABrawlerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetSwiping()) {
		if (TempActorsHit.Num() != 0) {
			TempActorsHit.Empty();
		}
	}
}

void ABrawlerEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begun"));
	if (GetSwiping())
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle check worked"));
		if (OtherActor->ActorHasTag("Hitable")) {
			if (!TempActorsHit.Contains(OtherActor) || (TempActorsHit.Num() == 0)) {
				TempActorsHit.Emplace(OtherActor);
				UE_LOG(LogTemp, Warning, TEXT("Hit Made"));
				//UGameplayStatics::PlaySound2D(GetWorld(), SwingSoundEffect, SwingSoundVolume, 1.0f, 0.0f);
				UGameplayStatics::ApplyDamage(OtherActor, Damage, GetController(), this, UDamageType::StaticClass());
			}
		}
		else if (Cast<ATest_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) {
			if (!TempActorsHit.Contains(OtherActor) || (TempActorsHit.Num() == 0)) {
				TempActorsHit.Emplace(OtherActor);
				UE_LOG(LogTemp, Warning, TEXT("Hit Made"));
				//UGameplayStatics::PlaySound2D(GetWorld(), SwingSoundEffect, SwingSoundVolume, 1.0f, 0.0f);
				UGameplayStatics::ApplyDamage(OtherActor, Damage, GetController(), this, UDamageType::StaticClass());
			}
		}
	}
}

float ABrawlerEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	EnemyRoomGameModeRef = Cast<AEnemyRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	//Drops Ball and updates Game mode upon death. Also activates respawn timer.
	if (Health <= 0) {
		if (EnemyRoomGameModeRef) EnemyRoomGameModeRef->EnemyDefeated(EnemyID);
		Destroy();
	}
	return DamageAmount;
}

void ABrawlerEnemy::SetSwiping(bool IsSwiping)
{
	Swiping = IsSwiping;
}

bool ABrawlerEnemy::GetSwiping()
{
	return Swiping;
}

void ABrawlerEnemy::BeginSwipe()
{
	GetWorld()->GetTimerManager().SetTimer(SwipeTimer, this, &ABrawlerEnemy::SwipeOver, SwipeDuration, false);
	SetSwiping(true);
}

void ABrawlerEnemy::SwipeOver()
{
	SetSwiping(false);
}

