// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player", meta=(AllowPrivateAccess="true"))
	float Speed = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player", meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player", meta=(AllowPrivateAccess="true"))
	class UCameraComponent* CameraComponent;

	void Move(float value);
};
