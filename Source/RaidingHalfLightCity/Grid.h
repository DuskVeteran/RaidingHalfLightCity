// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericStructs.h"
#include "Grid.generated.h"


class UBoxComponent;
class UGridMeshComponent;
class ADefaultTerrain;

UCLASS()
class RAIDINGHALFLIGHTCITY_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TMap<FVector2D, int32> GridMap;

	UPROPERTY(EditAnywhere)
	UStaticMesh* TileMesh;

	UPROPERTY(EditAnywhere)
	UGridMeshComponent* GridMeshComp;

	FVector GridWorldSize;
	float TileRadius = 0.f;

	FGridData GridData;

	void SetupGridData(FGridData& _GridData);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoundaryBox;

	//Prototyping Grid Tiles spawning
	UPROPERTY(EditAnywhere)
	float TileRadiusBuffer = 1.f;

	float TileDiameter;
	int GridSizeX, GridSizeY;

	void ChangeTileColor(FVector MyWorldPos);
	FVector GridDimensions;

	FIntVector MakeGridKey(FVector WorldPos);

	void CompCreateGrid();

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere)
	FIntVector GridSizeSetting;

	TArray<ADefaultTerrain*> Terrains;
};
