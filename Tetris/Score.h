// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Tetris/Score.h>
#include "MyGameStateBase.h"
#include "Score.generated.h"

class UWrapBox;
class UTextBlock;
class UScoreComponent;
class AWidgetTutorialCharacter;


UCLASS()
class TETRIS_API UScore : public UUserWidget
{
	GENERATED_BODY()

public:
	AMyGameStateBase* gameStateBase;

protected:
	void NativeOnInitialized() override;

};
