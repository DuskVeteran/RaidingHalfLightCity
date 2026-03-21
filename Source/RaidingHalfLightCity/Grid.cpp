// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Components/BoxComponent.h"
#include "Tile.h"

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

	//Grid prototyping
	TileRadius = TileClass.GetDefaultObject()->GetTileMeshSize().X + TileRadiusBuffer;
	TileDiameter = TileRadius * 2.0f;
	GridWorldSize = BoxExtent * 2.f;
	GridSizeX = BoxExtent.X * 2.0f / TileDiameter;
	GridSizeY = BoxExtent.Y * 2.0f / TileDiameter;
	CreateGrid();
	
}

void AGrid::CreateGrid()
{
	FVector WorldBottomLeft = GetActorLocation() - FVector::RightVector * GridWorldSize.X / 2 - FVector::ForwardVector * GridWorldSize.Y / 2;
	
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Bottom left : %s"), *WorldBottomLeft.ToCompactString()));
	for (int ix = 0; ix < GridSizeX; ix++)
	{
		for (int iy = 0; iy < GridSizeY; iy++)
		{
			
			FVector TileSpawnPoint = WorldBottomLeft + FVector::RightVector * (ix * TileDiameter + TileRadius) + FVector::ForwardVector * (iy * TileDiameter + TileRadius);
			ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, TileSpawnPoint, FRotator::ZeroRotator);
			if (NewTile)
			{
				NewTile->SetTileCoord(ix, iy, 0);
				Grid.Add(FVector2D(ix, iy), NewTile);
			}
		}
	}
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

