// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBall.h"

#include "Components/StaticMeshComponent.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
AMyBall::AMyBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshBall->SetupAttachment(RootComponent);
	MeshBall->SetSimulatePhysics(true);

	Stopped = false;
}

// Called when the game starts or when spawned
void AMyBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector speed = MeshBall->GetPhysicsLinearVelocity();
	if (FMath::Abs(speed.X) > 0) {
		FVector XVelocity = FVector(FMath::Sign(speed.X) * DeltaTime * -60, 0, 0);
		MeshBall->SetPhysicsLinearVelocity(XVelocity, true);
	}

	if (FMath::Abs(speed.Y) > 0) {
		FVector YVelocity = FVector(0, FMath::Sign(speed.Y) * DeltaTime * -60, 0);
		MeshBall->SetPhysicsLinearVelocity(YVelocity, true);
	}

	if (!Stopped && speed.Size() < 1.0) {
		UBochaGameInstance *BGI = Cast<UBochaGameInstance>(GetWorld()->GetGameInstance());
		if (BGI && BGI->MovingBall) {
			Stopped = true;
			BGI->MovingBall = false;
		}
	}
}

void AMyBall::SetVelocity(FVector velocity) {
	MeshBall->SetPhysicsLinearVelocity(velocity, false);
}

