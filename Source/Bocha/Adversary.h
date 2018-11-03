// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdBall.h"
#include "SmallBall.h"
#include "GameFramework/Actor.h"
#include "BochaGameInstance.h"
#include "Adversary.generated.h"

UCLASS()
class BOCHA_API AAdversary : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdversary();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AAdBall> ToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
