// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericStructs.generated.h"


class RAIDINGHALFLIGHTCITY_API GenericStructs
{
public:
	GenericStructs();
	~GenericStructs();
};

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

	FGridData()
	{

	}
	
	FGridData(UStaticMesh* _TileMesh, float _TileRadius, float _GridSizeX, float _GridSizeY, FVector _GridWorldSize, FVector _WorldBottomLeft) : 
		TileMesh(_TileMesh), TileRadius(_TileRadius), GridSizeX(_GridSizeX), GridSizeY(_GridSizeY), GridWorldSize(_GridWorldSize), WorldBottomLeft(_WorldBottomLeft)
	{

	}
	
	~FGridData()
	{

	}
	
};

