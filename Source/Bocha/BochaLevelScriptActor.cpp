// Fill out your copyright notice in the Description page of Project Settings.

#include "BochaLevelScriptActor.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

void ABochaLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false; 

	UBochaGameInstance *BGI = Cast<UBochaGameInstance>(GetWorld()->GetGameInstance());
	BGI->MovingBall = false;
	BGI->MyTurn = false;
	AdError = 100;
}

void ABochaLevelScriptActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UBochaGameInstance *BGI = Cast<UBochaGameInstance>(GetWorld()->GetGameInstance());

	if (BGI && !BGI->MovingBall && BGI->MyBalls == 4 && BGI->AdBalls == 4) {
		BGI->MovingBall = false;
		BGI->MyTurn = false;
		BGI->MyBalls = 0;
		BGI->AdBalls = 0;

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAdBall::StaticClass(), FoundActors);
		for (auto it : FoundActors)
		{
			AAdBall* AdBall = Cast<AAdBall>(it);
			AdBall->Destroy();
		}

		FoundActors.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyBall::StaticClass(), FoundActors);
		for (auto it : FoundActors)
		{
			AMyBall* MyBall = Cast<AMyBall>(it);
			MyBall->Destroy();
		}
	}

	if (BGI && !BGI->MyTurn && !BGI->MovingBall && BGI->AdBalls < 4) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AdBall"));
		BGI->MovingBall = true;
		BGI->MyTurn = true;
		BGI->AdBalls += 1;

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASmallBall::StaticClass(), FoundActors);
		FVector SmallBallLocation(0, 0, 0);
		for (auto it : FoundActors)
		{
			ASmallBall* SmallBall = Cast<ASmallBall>(it);
			SmallBallLocation = SmallBall->GetActorLocation();
		}

		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FVector Location = FVector(150.0f, FMath::RandRange(-100.0F, 100.0F), 100.0f);
		//UE_LOG(LogTemp, Warning, TEXT("AdBall Location: %s"), *Location.ToString());
		FActorSpawnParameters SpawnInfo;
		AAdBall *AdBall = GetWorld()->SpawnActor<AAdBall>(ToSpawn, Location, Rotation, SpawnInfo);
		AdBall->SetActorScale3D(FVector(0.4, 0.4, 0.4));

		FVector Error = FVector(FMath::RandRange(-AdError, AdError), FMath::RandRange(-AdError, AdError), 0);
		FVector Direction = Error + SmallBallLocation - Location;
		float VectorLength = 2 * 60;
		float speed_x = FMath::Sign(Direction.X)*FMath::Sqrt(FMath::Abs(Direction.X * VectorLength));
		float speed_y = FMath::Sign(Direction.Y)*FMath::Sqrt(FMath::Abs(Direction.Y * VectorLength));
		AdBall->SetVelocity(FVector(speed_x, speed_y, 0));
	}


}