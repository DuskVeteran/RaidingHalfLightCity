// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//Add your includes here
#include "GenericStructs.h"
#include "GridMesh.generated.h"

UCLASS()
class RAIDINGHALFLIGHTCITY_API AGridMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridMesh();

private:
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void CreateGrid(const FGridData &GridData);

	UPROPERTY()
	UInstancedStaticMeshComponent* InstMesh;
	UPROPERTY()
	TMap<FIntVector, int32> GridKeyChain;

	FVector CreateGrid(const FGridData& GridData);
	void ChangeColor(FIntVector MapKey);

};
