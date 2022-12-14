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
public:
	auto SetupPlayerInputComponent(UInputComponent *ic) -> void override;
	auto left() -> void;
	auto right() -> void;
	auto back() -> void;
	auto front() -> void;
	auto rotate() -> void;
	auto down() -> void;
	auto getGameState() const-> class AMyGameStateBase *;
};
