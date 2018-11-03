// Fill out your copyright notice in the Description page of Project Settings.

#include "Adversary.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
AAdversary::AAdversary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAdversary::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAdversary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UBochaGameInstance *BGI = Cast<UBochaGameInstance>(GetWorld()->GetGameInstance());
	if (BGI && !BGI->MyTurn && !BGI->MovingBall) {
		BGI->MovingBall = true;
		BGI->MyTurn = true;

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASmallBall::StaticClass(), FoundActors);
		FVector SmallBallLocation(0, 0, 0);
		for (auto it : FoundActors)
		{
			ASmallBall* SmallBall = Cast<ASmallBall>(it);
			SmallBallLocation = SmallBall->GetActorLocation();
		}

		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FVector Location = GetActorLocation(); 
		FActorSpawnParameters SpawnInfo;
		AAdBall *AdBall = GetWorld()->SpawnActor<AAdBall>(ToSpawn, Location, Rotation, SpawnInfo);
		AdBall->SetActorScale3D(FVector(0.5, 0.5, 0.5));

		FVector Direction = SmallBallLocation - Location;
		float VectorLength = 2 * 60;
		float speed_x = FMath::Sign(Direction.X)*FMath::Sqrt(FMath::Abs(Direction.X * VectorLength));
		float speed_y = FMath::Sign(Direction.Y)*FMath::Sqrt(FMath::Abs(Direction.Y * VectorLength));
		AdBall->SetVelocity(FVector(speed_x, speed_y, 0));
	}
}

