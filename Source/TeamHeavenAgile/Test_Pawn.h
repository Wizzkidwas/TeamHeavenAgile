//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Pawn.h"
//#include "Camera/CameraComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Math/UnrealMathUtility.h"
//#include "Test_Pawn.generated.h"
//
//class UCameraComponent;
//class USpringArmComponent;
//
//UCLASS()
//class TEAMHEAVENAGILE_API ATest_Pawn : public APawn
//{
//	GENERATED_BODY()
//
//public:
//	// Sets default values for this pawn's properties
//	ATest_Pawn();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//
//	void ForwardMovement(float Value);
//	void SidewaysMovement(float Value);
//	void Jump(float Value);
//	void PitchCamera(float AxisValue);
//	void YawCamera(float AxisValue);
//
//private:
//	UPROPERTY(EditAnywhere)
//	UStaticMeshComponent* testMesh;
//
//	UPROPERTY(EditAnywhere)
//	UCameraComponent* Camera;
//
//	UPROPERTY(EditAnywhere)
//	USpringArmComponent* CameraSpringArm;
//
//	UPROPERTY(EditAnywhere)
//	float MoveSpeed = 100.0f;
//
//	FVector DeltaLocation;
//	FVector2D CameraInput;
//};
