// Fill out your copyright notice in the Description page of Project Settings.


#include "ASword.h"
#include "Test_PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AASword::AASword()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SwordMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sword"));
	SetRootComponent(SwordMesh);
	collisionCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	collisionCollider->SetupAttachment(SwordMesh);
	collisionCollider->SetCapsuleSize(3.0f, 66.0f);
	collisionCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 66.0f));
	collisionCollider->SetCollisionProfileName("Trigger");
	collisionCollider->IgnoreActorWhenMoving(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), true);
}

// Called when the game starts or when spawned
void AASword::BeginPlay()
{
	Super::BeginPlay();
	collisionCollider->OnComponentBeginOverlap.AddDynamic(this, &AASword::OnOverlapBegin);
}

// Called every frame
void AASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	characterRef = Cast<ATest_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (characterRef) {
		if (characterRef->GetCurrentState() == States::Idle) {
			if (TempActorsHit.Num() != 0) {
				TempActorsHit.Empty();
			}
		}
	}
}

void AASword::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	characterRef = Cast<ATest_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (characterRef->GetCurrentState() != States::Idle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle check worked"));
		if (OtherActor->ActorHasTag("Hitable")) {
			if (!TempActorsHit.Contains(OtherActor) || (TempActorsHit.Num() == 0)) {
				TempActorsHit.Emplace(OtherActor);
				UE_LOG(LogTemp, Warning, TEXT("Hit Made"));
				UGameplayStatics::PlaySound2D(GetWorld(), SwingSoundEffect, SwingSoundVolume, 1.0f, 0.0f);
				if (characterRef->GetCurrentState() == States::LeftLight || characterRef->GetCurrentState() == States::RightLight) {
					UGameplayStatics::ApplyDamage(OtherActor, lightDamage, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, UDamageType::StaticClass());
				}
				else if (characterRef->GetCurrentState() == States::LeftHeavy || characterRef->GetCurrentState() == States::RightHeavy) {
					UGameplayStatics::ApplyDamage(OtherActor, heavyDamage, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, UDamageType::StaticClass());
				}
				else UE_LOG(LogTemp, Warning, TEXT("SomethingsBroke"));
			}
		}
	}
}
//crash caused by above code