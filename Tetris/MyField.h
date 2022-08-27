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
	void hasFullRow();
	bool hasFullCol();
	~MyField();
private:
	std::array<std::array<ABlock*, 20>, 10> blocks;
	std::reference_wrapper<class AMyGameStateBase> gs;
};
