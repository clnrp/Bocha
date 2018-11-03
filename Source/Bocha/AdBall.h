// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BochaGameInstance.h"
#include "AdBall.generated.h"

UCLASS()
class BOCHA_API AAdBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdBall();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshBall;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		virtual void SetVelocity(FVector velocity);

private:
	bool Stopped;
	
};