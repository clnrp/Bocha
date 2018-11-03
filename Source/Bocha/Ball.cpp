// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshBall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshBall->SetupAttachment(RootComponent);
	MeshBall->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABall::Tick(float DeltaTime)
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
}

void ABall::SetVelocity(FVector velocity) {
	MeshBall->SetPhysicsLinearVelocity(velocity, false);
}
