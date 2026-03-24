// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericStructs.h"
#include "Grid.generated.h"

class AGridMesh;
class UBoxComponent;
class ATile;

/*
USTRUCT(BlueprintType)
struct FGridData
{
	GENERATED_BODY()
	
	UPROPERTY()
	UStaticMesh* TileMesh;
	
	UPROPERTY()
	float TileRadius;
	UPROPERTY()
	float GridSizeX;
	UPROPERTY()
	float GridSizeY;
	UPROPERTY()
	FVector GridWorldSize;
	UPROPERTY()
	FVector WorldBottomLeft;

	FGridData(UStaticMesh* _TileMesh, float _TileRadius, float _GridSizeX, float _GridSizeY, FVector _GridWorldSize, FVector _WorldBottomLeft) :
		TileMesh(_TileMesh), TileRadius(_TileRadius), GridSizeX(_GridSizeX), GridSizeY(_GridSizeY), GridWorldSize(_GridWorldSize), WorldBottomLeft(_WorldBottomLeft)
	{

	}

	~FGridData()
	{

	}
	
};
*/
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

	UPROPERTY(VisibleAnywhere)
	AGridMesh* GridMesh;

	FVector GridWorldSize;
	float TileRadius = 0.f;

	FGridData GridData;

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

	void CreateGrid();
	void ChangeTileColor(FVector MyWorldPos);
	FVector GridDimensions;

	FIntVector MakeGridKey(FVector WorldPos);
};
