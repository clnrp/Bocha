// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterVR.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "EngineUtils.h"

// Sets default values
ACharacterVR::ACharacterVR()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneCamera = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneCamera->SetupAttachment(RootComponent);
	Camera1P = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera1P->SetupAttachment(SceneCamera);

	SceneRightMotion = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRightMotion"));
	SceneRightMotion->SetupAttachment(RootComponent);
	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	RightMotionController->Hand = EControllerHand::Right;
	RightMotionController->SetupAttachment(SceneRightMotion);

	MeshBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshBall->SetupAttachment(RightMotionController);
	MeshBall->SetVisibility(false);

}

// Called when the game starts or when spawned
void ACharacterVR::BeginPlay()
{
	Super::BeginPlay();
	Location = FVector(0, 0, 0);
	
}

// Called every frame
void ACharacterVR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MeshBall->IsVisible()) {
		BallSpeed = (MeshBall->GetComponentLocation() - Location) / DeltaTime;
		Location = MeshBall->GetComponentLocation();
	}
}

// Right Trigger Press
void ACharacterVR::TriggerPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Right trigger is PRESSED"));
	UBochaGameInstance *BGI = Cast<UBochaGameInstance>(GetWorld()->GetGameInstance());
	if (BGI && BGI->MyTurn && !BGI->MovingBall) {
		MeshBall->SetVisibility(true);
	}
}

// Right Trigger Release
void ACharacterVR::TriggerReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Right trigger is RELEASED"));
	UBochaGameInstance *BGI = Cast<UBochaGameInstance>(GetWorld()->GetGameInstance());
	if (BGI && BGI->MyTurn && !BGI->MovingBall && MeshBall->IsVisible() && BGI->MyBalls < 4) {
		BGI->MovingBall = true;
		BGI->MyTurn = false;
		BGI->MyBalls += 1;

		MeshBall->SetVisibility(false);

		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		AMyBall *MyBall = GetWorld()->SpawnActor<AMyBall>(ToSpawn, Location, Rotation, SpawnInfo);
		MyBall->SetActorScale3D(FVector(0.4, 0.4, 0.4));

		FVector ForwardVector = RightMotionController->GetForwardVector();
		ForwardVector.Normalize();
		float VectorLength = 2*BallSpeed.Size();
		float speed_x = ForwardVector.X * VectorLength;
		float speed_y = ForwardVector.Y * VectorLength;
		MyBall->SetVelocity(FVector(speed_x, speed_y, 0));
		//MyBall->SetVelocity(FVector(2 * BallSpeed.X, 2 * BallSpeed.Y, 0));
	}

}

void ACharacterVR::SlideX(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

// Called to bind functionality to input
void ACharacterVR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Trigger", EInputEvent::IE_Pressed, this, &ACharacterVR::TriggerPressed);
	InputComponent->BindAction("Trigger", EInputEvent::IE_Released, this, &ACharacterVR::TriggerReleased);
	InputComponent->BindAxis("SlideX", this, &ACharacterVR::SlideX);
}

