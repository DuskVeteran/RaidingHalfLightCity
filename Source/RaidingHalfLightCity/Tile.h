// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"



#include "Components/BoxComponent.h"



#include "Tile.generated.h"

UCLASS()
class RAIDINGHALFLIGHTCITY_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TileModel;


	UPROPERTY(EditAnywhere)
	float CrossingCost = 10.0f;

	UPROPERTY(EditAnywhere)
	bool bObstructed;

	UPROPERTY(EditAnywhere)
	bool bWalkable;

	UPROPERTY(EditAnywhere)
	FVector TileCoord = FVector(0.f, 0.f, 0.f);
};
