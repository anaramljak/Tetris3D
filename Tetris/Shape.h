// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include <array>

enum class ShapeType {I, O, T, S, Z, J, L, NONE};
class TETRIS_API Shape
{
public:
	Shape(class AMyGameStateBase &, ShapeType);
	~Shape();
	auto moveTo(int x, int y, int z) -> void;
	auto hasBlock(int x, int y, int z) const -> bool;
	auto rotL() -> void;
	auto rotR() -> void;
public:
	std::array<std::array<std::array<class ABlock*, 4>, 4>, 4> blocks;
};
