// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereBase.h"

// Sets default values
ASphereBase::ASphereBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereBase"));
	SphereBase->SetSimulatePhysics(true);


}

// Called when the game starts or when spawned
void ASphereBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASphereBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASphereBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

