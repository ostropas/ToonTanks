// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "BasePawn.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank && ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
		GameOver(false);
	}
	else if (--TargetTowers == 0)
	{
		GameOver(true);
	}
	
	if (ABasePawn* DestroyedBasePawn = Cast<ABasePawn>(DeadActor))
	{
		DestroyedBasePawn->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (!ToonTanksPlayerController) return;

	ToonTanksPlayerController->SetPlayerEnabledState(false);

	FTimerHandle PlayerEnabledTimerHandle;
	FTimerDelegate PlayerEnabledTimerDelegate =
		FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
	GetWorldTimerManager().SetTimer(PlayerEnabledTimerHandle, PlayerEnabledTimerDelegate, StartDelay, false);
}

int32 AToonTanksGameMode::GetTargetTowerCount() const
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), OutActors);
	return OutActors.Num();
}
