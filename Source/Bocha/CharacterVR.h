// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBall.h"
#include "BochaGameInstance.h"
#include "BochaGameState.h"
#include "CharacterVR.generated.h"

UCLASS()
class BOCHA_API ACharacterVR : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterVR();

	UPROPERTY(EditAnywhere)
		USceneComponent* SceneCamera;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera1P;

	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRightMotion;

	UPROPERTY(EditAnywhere)
		class UMotionControllerComponent* RightMotionController;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshBall;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMyBall> ToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		virtual void TriggerPressed();

	UFUNCTION()
		virtual void TriggerReleased();

	UFUNCTION()
		virtual void SlideX(float Value);

private:
	FVector Location;
	FVector BallSpeed;
};
