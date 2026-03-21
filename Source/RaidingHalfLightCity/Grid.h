// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class UBoxComponent;
class ATile;

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
	void CreateGrid();

	TMap<FVector2D, ATile*> Grid;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATile> TileClass;

	FVector GridWorldSize;
	float TileRadius = 0.f;

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


};
