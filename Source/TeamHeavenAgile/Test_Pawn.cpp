//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Test_Pawn.h"
//
//// Sets default values
//ATest_Pawn::ATest_Pawn()
//{
// 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//	testMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Test Mesh"));
//	testMesh->SetupAttachment(RootComponent);
//	AutoPossessPlayer = EAutoReceiveInput::Player0;
//	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
//	CameraSpringArm->SetupAttachment(testMesh);
//	CameraSpringArm->SetRelativeLocationAndRotation(FVector(-400.0f, 0.0f, 350.0f), FRotator(-20.0f, 0.0f, 0.0f));
//	CameraSpringArm->TargetArmLength = 400.f;
//	CameraSpringArm->bEnableCameraLag = true;
//	CameraSpringArm->CameraLagSpeed = 2.0f;
//	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
//	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
//
//	AutoPossessPlayer = EAutoReceiveInput::Player0;
//
//}
//
//// Called when the game starts or when spawned
//void ATest_Pawn::BeginPlay()
//{
//	Super::BeginPlay();	
//}
//
//// Called every frame
//void ATest_Pawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	// Rotate our pawn's X, which will turn our camera because we're attached to it
//	FRotator NewRotation = GetActorRotation();
//	NewRotation.Yaw += CameraInput.X;
//	SetActorRotation(NewRotation);
//
//	//Rotate our camera's Y, but limit it so we're always looking downward
//	NewRotation = CameraSpringArm->GetComponentRotation();
//	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
//	CameraSpringArm->SetWorldRotation(NewRotation);
//}
//
//// Called to bind functionality to input
//void ATest_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//	PlayerInputComponent->BindAxis("Forwards", this, &ATest_Pawn::ForwardMovement);
//	PlayerInputComponent->BindAxis("Sideways", this, &ATest_Pawn::SidewaysMovement);
//	PlayerInputComponent->BindAxis("CameraVertical", this, &ATest_Pawn::PitchCamera);
//	PlayerInputComponent->BindAxis("CameraHorizontal", this, &ATest_Pawn::YawCamera);
//}
//
//void ATest_Pawn::ForwardMovement(float Value)
//{
//	DeltaLocation = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f);
//	AddActorLocalOffset(DeltaLocation, true);
//}
//
//void ATest_Pawn::SidewaysMovement(float Value)
//{
//	DeltaLocation = FVector(0.0f, Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.0f);
//	AddActorLocalOffset(DeltaLocation, true);
//}
//
//void ATest_Pawn::Jump(float Value)
//{
//	DeltaLocation = FVector(0.0f, 0.0f, Value * MoveSpeed * GetWorld()->DeltaTimeSeconds);
//	AddActorLocalOffset(DeltaLocation, true);
//}
//
//void ATest_Pawn::PitchCamera(float AxisValue)
//{
//	CameraInput.Y = AxisValue;
//}
//
//void ATest_Pawn::YawCamera(float AxisValue)
//{
//	CameraInput.X = AxisValue;
//}