// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBall.h"
#include "AdBall.h"
#include "SmallBall.h"
#include "GameFramework/Actor.h"
#include "BochaGameInstance.h"
#include "Engine/LevelScriptActor.h"
#include "BochaLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class BOCHA_API ABochaLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AAdBall> ToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	float AdError;

};
