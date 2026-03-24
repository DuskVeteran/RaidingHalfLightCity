// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Tile.h"
#include "GridMesh.h"
#include "GenericStructs.h"


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

	CreateGrid();
}



// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrid::CreateGrid()
{
	FVector BoxExtent = BoundaryBox->GetUnscaledBoxExtent();

	TileRadius = TileMesh->GetBounds().BoxExtent.X + TileRadiusBuffer;
	TileDiameter = TileRadius * 2;
	GridWorldSize = BoxExtent * 2.f;
	GridSizeX = BoxExtent.X * 2.0f / TileDiameter;
	GridSizeY = BoxExtent.Y * 2.0f / TileDiameter;
	FVector WorldBottomLeft = GetActorLocation() - FVector::RightVector * GridWorldSize.X / 2 - FVector::ForwardVector * GridWorldSize.Y / 2;

	GridData = FGridData(TileMesh, TileRadius, GridSizeX, GridSizeY, GridWorldSize, WorldBottomLeft);

	GridMesh = GetWorld()->SpawnActor<AGridMesh>(AGridMesh::StaticClass(), FTransform(FVector(0.f, 0.f, 0.f)));
	GridMesh->SetOwner(this);
	GridDimensions = GridMesh->CreateGrid(GridData);
}

void AGrid::ChangeTileColor(FVector MyWorldPos)
{
	FIntVector MapKey = MakeGridKey(MyWorldPos);
	GridMesh->ChangeColor(MapKey);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("ChangeColor on %s"), *MapKey.ToString()));

}

FIntVector3 AGrid::MakeGridKey(FVector WorldPos)
{
	FVector TileCenterOffset = FVector::One() / 2.0f;
	FVector SearchingForZero = (WorldPos - GridData.WorldBottomLeft - TileRadius)/TileDiameter;

	SearchingForZero = SearchingForZero + TileCenterOffset;

	FIntVector Truncated = FIntVector(FMath::FloorToInt(SearchingForZero.X), FMath::FloorToInt(SearchingForZero.Y), FMath::FloorToInt(SearchingForZero.Z));


	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("%s"), *Truncated.ToString()));
	return Truncated;
}

