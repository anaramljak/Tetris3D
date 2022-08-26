// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <array>

enum class ShapeType {I, O, T, S, Z, J, L};
class TETRIS_API Shape
{
public:
	Shape(class AMyGameStateBase &, ShapeType);
	~Shape();
	auto moveTo(int x, int y) -> void;
	auto moveToSpeed(int x, int y) -> void;
	auto hasBlock(int x, int y) const -> bool;
	auto rotL() -> void;
	auto rotR() -> void;

private:
	std::array<std::array<class AActor*, 4>, 4> blocks;
};
