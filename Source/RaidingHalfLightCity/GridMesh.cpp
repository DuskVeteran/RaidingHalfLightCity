// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMesh.h"
#include "Components/InstancedStaticMeshComponent.h"


// Sets default values
AGridMesh::AGridMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InstMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
	SetRootComponent(InstMesh);

	SetActorTickEnabled(false);
	
}

// Called when the game starts or when spawned
void AGridMesh::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AGridMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AGridMesh::CreateGrid(const FGridData& GridData)
{
	InstMesh->SetStaticMesh(GridData.TileMesh);
	InstMesh->SetNumCustomDataFloats(3);
	InstMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InstMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	float TileDiameter = GridData.TileRadius * 2;
	//FVector GridWorldSize = BoxExtent * 2.f;
	//float GridSizeX = BoxExtent.X * 2.0f / TileDiameter;
	//float GridSizeY = BoxExtent.Y * 2.0f / TileDiameter;
	//FVector WorldBottomLeft = GetOwner()->GetActorLocation() - FVector::RightVector * GridWorldSize.X / 2 - FVector::ForwardVector * GridWorldSize.Y / 2;

	FVector GridDimensions = FVector(0.f, 0.f, 0.f);

	for (int ix = 0; ix < GridData.GridSizeX; ix++)
	{
		for (int iy = 0; iy < GridData.GridSizeY; iy++)
		{

			FVector TileSpawnPoint = GridData.WorldBottomLeft + FVector::RightVector * (iy * TileDiameter + GridData.TileRadius) + FVector::ForwardVector * (ix * TileDiameter + GridData.TileRadius);
			
			FTransform SpawnTransform = FTransform(TileSpawnPoint);
			UE_LOG(LogTemp, Warning, TEXT("Adding instance"));
			int32 MapIndex = InstMesh->AddInstance(SpawnTransform);
			GridKeyChain.Add(FIntVector(ix, iy, 0), MapIndex);

			if (ix == 0 && iy == 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("FirstSpawnPoint : %s"), *TileSpawnPoint.ToCompactString()));
			}

			GridDimensions.Y = iy;
		}
		GridDimensions.X = ix;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 120.f, FColor::Blue, FString::Printf(TEXT("GridSize = %s"), *GridDimensions.ToCompactString()));
	return GridDimensions;
}

void AGridMesh::ChangeColor(FIntVector MapKey)
{
	int32* MapIndex = GridKeyChain.Find(MapKey);
	InstMesh->SetCustomDataValue(*MapIndex, 0, 1.0f);
}


