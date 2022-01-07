// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank() : ABasePawn()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring arm");
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}

void ATank::Move(float value)
{
	if (value != 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Value %f"), value);
	}

	AddActorLocalOffset(FVector(value * Speed, 0, 0));
}
