// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultTerrain.h"
#include "Components/BoxComponent.h"
#include "GridMeshComponent.h"
#include "GenericStructs.h"

// Sets default values
ADefaultTerrain::ADefaultTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(SceneRoot);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

	ClimbBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ClimbBox"));
	ClimbBox->SetupAttachment(BoxComponent);

	GridMesh = CreateDefaultSubobject<UGridMeshComponent>(TEXT("GridMesh"));
	GridMesh->SetupAttachment(BoxComponent);
	GridMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GridMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ADefaultTerrain::BeginPlay()
{
	Super::BeginPlay();

	//GridMesh->GetExistingGrid(GridKeyChain);
	
}

// Called every frame
void ADefaultTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultTerrain::ChangeTileColor(FVector MyWorldPos)
{
	FIntVector MapKey = GridMesh->MakeGridKey(MyWorldPos, GridData);
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *FVector(MapKey).ToCompactString()));
	GridMesh->ChangeColor(MapKey);
	
}

void ADefaultTerrain::SetGridData(FGridData& _GridData)
{
	GridData = _GridData;
}

void ADefaultTerrain::GetGrid(TMap<FIntVector, int32>& ExistingMap)
{
	GridMesh->GetExistingGrid(ExistingMap, GridData);
}

FIntVector ADefaultTerrain::MakeKey(FVector _WorldPos)
{
	FIntVector OutVector = GridMesh->MakeGridKey(_WorldPos, GridData);

	return OutVector;
}


