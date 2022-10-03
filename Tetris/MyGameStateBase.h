#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Shape.h"
#include <memory>
#include "MyField.h"
#include "Block.h"
#include "MyGameStateBase.generated.h"

UCLASS()
class TETRIS_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	UClass *blockClass = nullptr;
	AMyGameStateBase();
	auto BeginPlay() -> void override;
	auto EndPlay(const EEndPlayReason::Type EndPlayReason) -> void override;
	auto Tick(float DeltaTime) -> void override;
public:
	FLinearColor currentColor;
	auto createBlock(ShapeType type) -> ABlock *;
	auto left() -> void;
	auto right() -> void;
	auto back() -> void;
	auto front() -> void;
	auto rotate() -> void;
	auto down() -> void;
private:
	std::unique_ptr<Shape> currentShape;
	std::unique_ptr<MyField> field;
	int y = 0;
	int x = 3;
	int z = 5;
	float nextMove = 0;
	auto newShape() -> void;
	auto putShapeOnTheFloor() -> void;
	auto isCollide() const -> bool;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int score = 0;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int highScore = 0;

};
