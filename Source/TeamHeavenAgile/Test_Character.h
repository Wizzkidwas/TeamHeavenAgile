// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Test_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;

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

private:
	void ForwardMovement(float Value);
	void SidewaysMovement(float Value);
	void JumpCharacter();
	void Dodge();
	void LeftLightAttack();
	void LeftHeavyAttack();
	void RightLightAttack();
	void RightHeavyAttack();
	void ActionFinished();
	void VacantTimeUp();
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);                                         

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 100.0f;

	UPROPERTY()			    FTimerHandle DodgeTimer;
	UPROPERTY(EditAnywhere) float DodgeDuration = 2.0f;
	UPROPERTY()			    FTimerHandle DodgeActivateTimer;
	UPROPERTY(EditAnywhere) float DodgeActivateDuration = 2.0f;
	UPROPERTY()			    FTimerHandle LeftLightTimer;
	UPROPERTY(EditAnywhere) float LeftLightDuration = 2.0f;
	UPROPERTY()			    FTimerHandle LeftHeavyTimer;
	UPROPERTY(EditAnywhere) float LeftHeavyDuration = 2.0f;
	UPROPERTY()			    FTimerHandle RightLightTimer;
	UPROPERTY(EditAnywhere) float RightLightDuration = 2.0f;
	UPROPERTY()			    FTimerHandle RightHeavyTimer;
	UPROPERTY(EditAnywhere) float RightHeavyDuration = 2.0f;

	enum class States { idle, block, leftLight, leftHeavy, rightLight, rightHeavy, Dodge };
	States currentState = States::idle;
};
