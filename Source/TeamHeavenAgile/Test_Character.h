// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Test_Character.generated.h"

UCLASS()
class TEAMHEAVENAGILE_API ATest_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATest_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

<<<<<<< Updated upstream
=======
private:
	void ForwardMovement(float Value);
	void SidewaysMovement(float Value);
	void JumpCharacter();
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void SwordAttack();
	void FireDecider();

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 100.0f;

	FVector DeltaLocation;
	FVector2D CameraInput;
	
	UPROPERTY(EditAnywhere)
		bool CanAttack = true;
>>>>>>> Stashed changes
};
