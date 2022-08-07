#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Shape.h"
#include <memory>
#include "MyGameStateBase.generated.h"

UCLASS()
class TETRIS_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	UClass* blockClass = nullptr;
	auto BeginPlay() -> void override;
	auto EndPlay
	(
		const EEndPlayReason::Type EndPlayReason
	) -> void override;
public:
	auto createBlock()-> AActor *;
private:
	std::unique_ptr<Shape> currentShape;
	
};
