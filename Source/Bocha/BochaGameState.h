// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BochaGameState.generated.h"

/**
 * 
 */
UCLASS()
class BOCHA_API ABochaGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aux")
		bool MyTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aux")
		bool EndOfPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aux")
		int MyBalls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aux")
		int AdBalls;
	
};
