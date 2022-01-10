// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

bool ATower::IsTankInFireRange()
{
	float DistanceToTank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	return DistanceToTank < MaxDistanceToTank;
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsTankInFireRange()) return;

	RotateTurret(Tank->GetActorLocation());
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (!IsTankInFireRange()) return;
	Fire();
}
