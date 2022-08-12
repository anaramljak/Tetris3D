// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "MyGameStateBase.h"
#include "MyPawn.generated.h"

UCLASS()
class TETRIS_API AMyPawn : public ADefaultPawn
{
	GENERATED_BODY()
	AMyPawn();
	auto SetupPlayerInputComponent(UInputComponent *) -> void override;
	auto left() -> void;
	auto right() -> void;
	auto rotate() -> void;
	auto getGameState() const->AMyGameStateBase*;
};
