// Fill out your copyright notice in the Description page of Project Settings.

#include "SlimeEnemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASlimeEnemy::ASlimeEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ASlimeAIController::StaticClass();
	//SpawnDefaultController();
	CollisionMesh = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(CollisionMesh);
	SlimeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slime"));
	SlimeMesh->SetupAttachment(RootComponent);
	SlimeMesh->SetNotifyRigidBodyCollision(true);
	SlimeMesh->SetSimulatePhysics(true);
}

void ASlimeEnemy::Initialise(int slimeSize)
{
	SlimeSize = slimeSize;
	//SlimeMesh->SetRelativeScale3D(FVector(slimeSize, slimeSize, slimeSize));
	Damage = BaseDamage * SlimeSize;
	Health = BaseHealth * SlimeSize;
}

// Called when the game starts or when spawned
void ASlimeEnemy::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ASlimeEnemy::OnOverlapBegin);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ASlimeEnemy::OnOverlapEnd);
}

// Called every frame
void ASlimeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlimeEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (!bHasHit) {
		AActor* tempActor = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
		if (OtherActor == tempActor) {
			bHasHit = true;
			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetController(), this, UDamageType::StaticClass());
		}
	}
}

void ASlimeEnemy::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	AActor* tempActor = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	if (OtherActor == tempActor) {
		bHasHit = false;
	}
}


float ASlimeEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	Health -= DamageAmount;

	if (Health <= 0) {
		if (SlimeSize > 1) {
			SlimeSize--;
			ASlimeEnemy* SlimeTemp1 = GetWorld()->SpawnActor<ASlimeEnemy>(SlimeClass, GetActorLocation(), GetActorRotation());
			//SlimeTemp1->Initialise(SlimeSize);
			ASlimeEnemy* SlimeTemp2 = GetWorld()->SpawnActor<ASlimeEnemy>(SlimeClass, GetActorLocation(), GetActorRotation());
			//SlimeTemp2->Initialise(SlimeSize);
		}
		Destroy();
	}
	return DamageAmount;
}