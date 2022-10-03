// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <array>
#include "Block.h"

class TETRIS_API MyField
{
public:
	MyField(class AMyGameStateBase &);
	auto hasBlock(int x, int y, int z) const -> bool;
	auto addBlock(int x, int y, int z) -> void;
	auto deleteFullRow(int j, int k) -> void;
	auto decreaseFullRow(int j, int l) -> void;
	auto deleteFullRowDiagonal(int j, int i) -> void;
	auto decreaseFullRowDiagonal(int j, int l) -> void;
	auto hasFullRow(int j, int k) -> bool;
	auto hasFullRowDiagonal(int j, int i) -> bool;
	auto hasFullCol() -> bool;
	~MyField();
private:
	std::array<std::array<std::array<ABlock*, 10>, 20>, 10> blocks;
	std::reference_wrapper<class AMyGameStateBase> gs;
};
