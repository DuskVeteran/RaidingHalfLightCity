// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"



#include "Components/TimelineComponent.h"
#include "DefaultPlayer.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UCapsuleComponent;
class UFloatingPawnMovement;

UCLASS()
class RAIDINGHALFLIGHTCITY_API ADefaultPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADefaultPlayer();

private:
	//PrivateTimeline Declarations More in Protected
	FOnTimelineFloat OnTimeline_Update;
	FOnTimelineEventStatic OnTimeline_Finished;
	UFUNCTION()
	void Handle_RotatePlayer_Update(float val);
	UFUNCTION()
	void Handle_RotatePlayer_Finished();
	void StartPlayerRotation();
	void StopPlayerRotation();
	float PlayerRotationDir = 0.f;

	float YawInitialRotation;
	float YawTargetRotation;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* PivotAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LeftClickAction;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* MovementComponent;

	void Move(float InputX, float InputY);
	void Pivot(float Direction);

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
	float CameraMovementSpeed = 100.f;

	//Timeline Declarations
	UPROPERTY()
	TObjectPtr<UTimelineComponent> T_RotatePlayer;
	UPROPERTY(EditAnywhere)
	UCurveFloat* Curve;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveInput(const FInputActionValue& Value);
	void PivotInput(const FInputActionValue& Value);
	void LeftClickInput(const FInputActionValue& Value);

};
