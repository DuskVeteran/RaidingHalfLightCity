// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GenericStructs.h"
#include "GridMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultTerrain.h"


// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoundaryBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Boundary box"));
	SetRootComponent(BoundaryBox);

	BoundaryBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);	

	GridMeshComp = CreateDefaultSubobject<UGridMeshComponent>(TEXT("GridMeshComp"));
	GridMeshComp->SetupAttachment(RootComponent);
	GridMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GridMeshComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	GridSizeSetting = FIntVector(1, 1, 1);

}

void AGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GridMeshComp->ClearGrid();
	CompCreateGrid();
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	SetupGridData(GridData);
	GridMeshComp->ClearGrid();
	CompCreateGrid();

	TArray<AActor*> TerrainActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultTerrain::StaticClass(), TerrainActors);
	for (int i = 0; i < TerrainActors.Num(); i++)
	{
		Terrains.Add(Cast<ADefaultTerrain>(TerrainActors[i]));
	}

	if (Terrains.Num() > 0)
	{
		for (ADefaultTerrain* T : Terrains)
		{
			T->SetGridData(GridData);
			TMap<FIntVector, int32> NewGrid;
			T->GetGrid(NewGrid);
			GridMeshComp->MergeGrid(NewGrid);

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("Its calling")));

		}
	}
}

void AGrid::SetupGridData(FGridData& _GridData)
{
	TileRadius = TileMesh->GetBounds().BoxExtent.X + TileRadiusBuffer;
	TileDiameter = TileRadius * 2;
	BoundaryBox->SetBoxExtent(FVector(GridSizeSetting) * TileDiameter / 2.f);
	FVector BoxExtent = BoundaryBox->GetUnscaledBoxExtent();

	GridWorldSize = BoxExtent * 2.f;
	GridSizeX = BoxExtent.X * 2.0f / TileDiameter;
	GridSizeY = BoxExtent.Y * 2.0f / TileDiameter;
	FVector WorldBottomLeft = -1.f * (FVector::RightVector * GridWorldSize.Y / 2 + FVector::ForwardVector * GridWorldSize.X / 2);
	_GridData = FGridData(TileMesh, TileRadius,TileDiameter, GridSizeX, GridSizeY, GridWorldSize, WorldBottomLeft);
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrid::CompCreateGrid()
{
	SetupGridData(GridData);
		
	GridDimensions = GridMeshComp->CreateGrid(GridData);
}

void AGrid::ChangeTileColor(FVector MyWorldPos)
{
	FIntVector MapKey = GridMeshComp->MakeGridKey(MyWorldPos, GridData);
	GridMeshComp->ChangeColor(MapKey);

}

FIntVector3 AGrid::MakeGridKey(FVector WorldPos)
{
	return GridMeshComp->MakeGridKey(WorldPos, GridData);

/*
	//1
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("1 : %s"), *WorldPos.ToString()));

	FVector TileCenterOffset = FVector::One() / 2.0f;
	
	FVector SearchingForZero = (WorldPos - GridData.WorldBottomLeft - TileRadius)/TileDiameter;
	//FVector SearchingForZero = (WorldPos  - TileRadius) / TileDiameter;

	//2
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("2 : %s"), *SearchingForZero.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("2 TileDiameter: %f"), TileDiameter));

	SearchingForZero = SearchingForZero + TileCenterOffset;

	//3
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("3 : %s"), *SearchingForZero.ToString()));

	FIntVector Truncated = FIntVector(FMath::FloorToInt(SearchingForZero.X), FMath::FloorToInt(SearchingForZero.Y), FMath::FloorToInt(SearchingForZero.Z));

	//4
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, FString::Printf(TEXT("%s"), *Truncated.ToString()));
	return Truncated;
*/
}

