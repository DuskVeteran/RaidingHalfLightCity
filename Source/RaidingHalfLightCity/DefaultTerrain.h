// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericStructs.h"
#include "DefaultTerrain.generated.h"

class UBoxComponent;
class UGridMeshComponent;

UCLASS()
class RAIDINGHALFLIGHTCITY_API ADefaultTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultTerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeTileColor(FVector MyWorldPos);

	void SetGridData(FGridData& _GridData);
	void GetGrid(TMap<FIntVector, int32>& ExistingMap);

	FIntVector MakeKey(FVector _WorldPos);

	

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	UBoxComponent* ClimbBox;

	UPROPERTY(EditAnywhere)
	UGridMeshComponent* GridMesh;

	UPROPERTY()
	TMap<FIntVector, int32> GridKeyChain;

	FGridData GridData;

	

};
