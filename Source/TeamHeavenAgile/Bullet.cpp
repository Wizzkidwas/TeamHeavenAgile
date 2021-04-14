// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates mesh for Ball and enables collision
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	SetRootComponent(BulletMesh);
	BulletMesh->SetNotifyRigidBodyCollision(true);
	BulletMesh->SetSimulatePhysics(true);

	//Initiates Ball as a projectile to give it momentum upon creation. Also stops it despawning.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 2;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlayCalled"));
	OnActorHit.AddDynamic(this, &ABullet::OnHit);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	AActor* ProjectileOwner = GetOwner();
	if (!ProjectileOwner) return;
	UE_LOG(LogTemp, Warning, TEXT("Bullet Hit"));
	UE_LOG(LogTemp, Warning, TEXT("Bullet Hit 2nd Call"));
	UE_LOG(LogTemp, Warning, TEXT("Bullet Hit 3rd Call"));

	//Upon hit plays sound and applies damage if above certain force.
	//if (NormalImpulse.Size() > ForceSoundCutoffAmount) {
	UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
	Destroy();
	//}
}