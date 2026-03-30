// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GenericStructs.h"
#include "GridMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class RAIDINGHALFLIGHTCITY_API UGridMeshComponent : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TMap<FIntVector, int32> ComponentGridKeyChain;
public:
	FVector CreateGrid(const FGridData& GridData);
	void ChangeColor(FIntVector MapKey);
	void GetExistingGrid(TMap<FIntVector, int32>& ExistingMap, FGridData &_GridData);

	void ClearGrid();
	void MergeGrid(TMap<FIntVector, int32> NewGrid);

	FIntVector MakeGridKey(FVector WorldPos, FGridData &_GridData);

	

};
