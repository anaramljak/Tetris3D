// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <array>
#include "Block.h"

class TETRIS_API MyField
{
public:
	MyField(class AMyGameStateBase &);
	auto hasBlock(int x, int y) const -> bool;
	auto addBlock(int x, int y) -> void;
	auto deleteFullRow(int j) -> void;
	auto decreaseFullRow(int j) -> void;
	auto hasFullRow(int j) -> bool;
	auto hasFullCol() -> bool;
	~MyField();
private:
	std::array<std::array<ABlock*, 20>, 10> blocks;
	std::reference_wrapper<class AMyGameStateBase> gs;
};
