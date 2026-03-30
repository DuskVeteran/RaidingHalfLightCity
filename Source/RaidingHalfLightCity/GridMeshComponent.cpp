// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMeshComponent.h"

void UGridMeshComponent::GetExistingGrid(TMap<FIntVector, int32>& ExistingMap, FGridData& _GridData)
{
	SetNumCustomDataFloats(3);

	int32 InstCount = GetInstanceCount();
	if (InstCount <= 0) return;

	for (int i = 0; i < InstCount; i++)
	{
		FTransform InstTransf;
		GetInstanceTransform(i, InstTransf, true);

		FIntVector CurrentKey = MakeGridKey(InstTransf.GetLocation(), _GridData);

		ComponentGridKeyChain.Add(CurrentKey, i);
		ExistingMap.Add(CurrentKey, i);

		//ChangeColor(CurrentKey);

		FVector DebugCurrentKey = FVector(CurrentKey);
		
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, FString::Printf(TEXT("Additional grid! %s"), *InstTransf.GetLocation().ToCompactString()));
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, FString::Printf(TEXT("Additional grid! %s"), *DebugCurrentKey.ToCompactString()));
	}


}

void UGridMeshComponent::ClearGrid()
{
	ClearInstances();
}

void UGridMeshComponent::MergeGrid(TMap<FIntVector, int32> NewGrid)
{
	ComponentGridKeyChain.Append(NewGrid);
}

FVector UGridMeshComponent::CreateGrid(const FGridData& GridData)
{
	SetStaticMesh(GridData.TileMesh);
	SetNumCustomDataFloats(3);

	
	float TileDiameter = GridData.TileRadius * 2;

	FVector GridDimensions = FVector(0.f, 0.f, 0.f);
	
	for (int ix = 0; ix < GridData.GridSizeX; ix++)
	{
		for (int iy = 0; iy < GridData.GridSizeY; iy++)
		{
			//FVector TileSpawnPoint = FVector::RightVector * (iy * TileDiameter + GridData.TileRadius) + FVector::ForwardVector * (ix * TileDiameter + GridData.TileRadius);
			FVector TileSpawnPoint = GridData.WorldBottomLeft + FVector::RightVector * (iy * TileDiameter + GridData.TileRadius) + FVector::ForwardVector * (ix * TileDiameter + GridData.TileRadius);

			FTransform SpawnTransform = FTransform(TileSpawnPoint);
			UE_LOG(LogTemp, Warning, TEXT("Adding instance"));
			int32 MapIndex = AddInstance(SpawnTransform);
			ComponentGridKeyChain.Add(FIntVector(ix, iy, 0), MapIndex);

			FVector CheckObstructedPoint = TileSpawnPoint + GetOwner()->GetActorLocation();

			bool IsObstructed = GetWorld()->OverlapBlockingTestByChannel(CheckObstructedPoint, FRotator::ZeroRotator.Quaternion(),
				ECC_GameTraceChannel2, FCollisionShape::MakeBox(FVector(GridData.TileRadius)));
			if (IsObstructed)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Magenta, FString::Printf(TEXT("%d"), MapIndex));
				//Make better color function
				SetCustomDataValue(MapIndex, 1, 1.0f);
			}

			if (ix == 0 && iy == 0)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("FirstSpawnPoint : %s"), *TileSpawnPoint.ToCompactString()));
			}

			GridDimensions.Y = iy;
		}
		GridDimensions.X = ix;
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 120.f, FColor::Blue, FString::Printf(TEXT("GridSize = %s"), *GridDimensions.ToCompactString()));
	GEngine->AddOnScreenDebugMessage(-1, 120.f, FColor::Blue, FString::Printf(TEXT("FunctionCalled")));
	return GridDimensions;
}

void UGridMeshComponent::ChangeColor(FIntVector MapKey)
{
	int32* MapIndex = ComponentGridKeyChain.Find(MapKey);
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("%s : %d"), *GetOwner()->GetActorNameOrLabel(), MapIndex));

	SetCustomDataValue(*MapIndex, 0, 1.0f);
}

FIntVector3 UGridMeshComponent::MakeGridKey(FVector WorldPos, FGridData &_GridData)
{
	FVector TileCenterOffset = FVector::One() / 2.0f;

	FVector SearchingForZero = (WorldPos - _GridData.WorldBottomLeft - _GridData.TileRadius) / _GridData.TileDiameter;

	SearchingForZero.Z = (WorldPos.Z) / _GridData.TileDiameter;

	SearchingForZero = SearchingForZero + TileCenterOffset;

	FIntVector Truncated = FIntVector(FMath::FloorToInt(SearchingForZero.X), FMath::FloorToInt(SearchingForZero.Y), FMath::FloorToInt(SearchingForZero.Z));

	return Truncated;
}

