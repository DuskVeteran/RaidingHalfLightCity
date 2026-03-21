// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayer.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/FloatingPawnMovement.h"

#include "Components/CapsuleComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ADefaultPlayer::ADefaultPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovementComponent"));

	//TimelineStuff
	T_RotatePlayer = CreateDefaultSubobject<UTimelineComponent>(TEXT("T_RotatePlayer"));
	OnTimeline_Update.BindUFunction(this, FName("Handle_RotatePlayer_Update"));
	OnTimeline_Finished.BindUFunction(this, FName("Handle_RotatePlayer_Finished"));
}



// Called when the game starts or when spawned
void ADefaultPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}

		PlayerController->bShowMouseCursor = true;
	}	

	//TimelineStuff
	if (Curve)
	{
		T_RotatePlayer->AddInterpFloat(Curve, OnTimeline_Update, FName("Alpha"));
		T_RotatePlayer->SetTimelineFinishedFunc(OnTimeline_Finished);
		T_RotatePlayer->SetLooping(false);
		T_RotatePlayer->SetIgnoreTimeDilation(true);
	}
}



// Called every frame
void ADefaultPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADefaultPlayer::MoveInput);
		EIC->BindAction(PivotAction, ETriggerEvent::Started, this, &ADefaultPlayer::PivotInput);
		EIC->BindAction(LeftClickAction, ETriggerEvent::Started, this, &ADefaultPlayer::LeftClickInput);
	}

}

void ADefaultPlayer::MoveInput(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2d>();

	FString value = InputValue.ToString();

	UE_LOG(LogTemp, Warning, TEXT("Moving, %s"), *value);

	Move(InputValue.X, InputValue.Y);
}

void ADefaultPlayer::Move(float InputX, float InputY)
{
	if (GetController() != nullptr)
	{
		FVector ForwardDirection = GetActorForwardVector();
		FVector RightDirection = GetActorRightVector();

		// add movement 
		AddMovementInput(ForwardDirection, InputX);
		AddMovementInput(RightDirection, InputY);
	}
}

void ADefaultPlayer::Pivot(float Direction)
{
	YawInitialRotation = GetActorRotation().Yaw;
	YawTargetRotation = YawInitialRotation + Direction * 45.f;

	StartPlayerRotation();
}

void ADefaultPlayer::PivotInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();

	Pivot(InputValue);
}

void ADefaultPlayer::LeftClickInput(const FInputActionValue& Value)
{
	bool InputValue = Value.Get<bool>();

	UE_LOG(LogTemp, Warning, TEXT("LeftClicking"));

	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, HitResult);
		if (HitResult.bBlockingHit)
		{
			AActor* hitActor = HitResult.GetActor();

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("HittingStuff %s"), *hitActor->GetActorNameOrLabel()));
		}
	}
}

void ADefaultPlayer::Handle_RotatePlayer_Update(float val)
{
	UE_LOG(LogTemp, Warning, TEXT("StartPivor"));
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("From %f to %f"), YawInitialRotation, YawTargetRotation));

	SetActorRelativeRotation(FRotator(0.f, FMath::Lerp(YawInitialRotation, YawTargetRotation, val), 0.f));
}

void ADefaultPlayer::Handle_RotatePlayer_Finished()
{
	StopPlayerRotation();
}

void ADefaultPlayer::StartPlayerRotation()
{
	T_RotatePlayer->PlayFromStart();
}

void ADefaultPlayer::StopPlayerRotation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("FinishedPivoting")));
}