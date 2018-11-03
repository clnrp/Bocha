// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BochaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BOCHA_API UBochaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "R1")
		float Reduce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "R2")
		bool MyTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "R2")
		bool MovingBall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "R2")
		int MyBalls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "R2")
		int AdBalls;
	
};
