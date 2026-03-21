// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Components/BoxComponent.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoundaryBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Boundary box"));
	SetRootComponent(BoundaryBox);

	BoundaryBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	FVector BoxExtent = BoundaryBox->GetUnscaledBoxExtent();
	FString BoxExtentString = BoxExtent.ToCompactString();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, FString::Printf(TEXT("%s"), *BoxExtentString));
	
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

