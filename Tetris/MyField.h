// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <array>

class TETRIS_API MyField
{
public:
	MyField(class AMyGameStateBase &);
	auto hasBlock(int x, int y) const -> bool;
	auto addBlock(int x, int y) -> void;
	void hasFullRow();
	~MyField();
private:
	std::array<std::array<AActor*, 20>, 10> blocks;
	std::reference_wrapper<class AMyGameStateBase> gs;
};
