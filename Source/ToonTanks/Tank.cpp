// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Move(float value)
{
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalOffset(FVector(value * Speed * deltaTime, 0, 0), true);
}

void ATank::Turn(float value)
{
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalRotation(FRotator(0,value * deltaTime * RotateSpeed,0), true);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerControllerRef) return;

	FHitResult hitResult;
	PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);

	if (!hitResult.GetActor()) return;

	RotateTurret(hitResult.ImpactPoint);
}
