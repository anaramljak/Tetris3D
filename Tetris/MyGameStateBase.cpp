#include "MyGameStateBase.h"
#include "Block.h"
#include "Shape.h"
#include "MyField.h"

AMyGameStateBase::AMyGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

auto AMyGameStateBase::BeginPlay() -> void
{
	Super::BeginPlay();
	blockClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Game/Block_BP.Block_BP_C"));
	check(blockClass);
	field = std::make_unique<MyField>(*this);
	newShape();
}

auto AMyGameStateBase::newShape() -> void
{
	x = 3;
	y = 0;
	currentShape = std::make_unique<Shape>(*this, static_cast<ShapeType>(rand() % 7));
	currentShape->moveTo(x, y);
}

void AMyGameStateBase::Tick(float DeltaTime) 
{
	if (GetWorld()->GetTimeSeconds() > nextMove)
	{
		++y;
		if (isCollide())
		{
			--y;
			putShapeOnTheFloor();
		}  
		currentShape->moveTo(x, y);
		nextMove = GetWorld()->GetTimeSeconds() + 0.5;
	}

}

auto AMyGameStateBase::isCollide() const -> bool
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (currentShape->hasBlock(i, j) && field->hasBlock(i + x, j + y))
				return true;
	return false;
}

auto AMyGameStateBase::createBlock(ShapeType type) -> ABlock *
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ABlock* block = GetWorld()->SpawnActor<ABlock>(blockClass, FVector{ 0, 0, 0 }, FRotator{ 0, 0, 0 }, param);
	switch (type) {
		case ShapeType::O:
		{
			
			block->changeColor(FLinearColor::Yellow);
			currentColor = FLinearColor::Yellow;
			break;
		}
		case ShapeType::L:
		{
			block->changeColor(FLinearColor::Red);
			currentColor = FLinearColor::Red;
			break;
		}
		case ShapeType::I:
		{
			block->changeColor(FLinearColor::Green);
			currentColor = FLinearColor::Green;
			break;
		}
		case ShapeType::J:
		{
			block->changeColor(FLinearColor::Blue);
			currentColor = FLinearColor::Blue;
			break;
		}
		case ShapeType::S:
		{
			block->changeColor(FLinearColor(0.26f, 0.05f, 0.38f));
			currentColor = FLinearColor(0.26f, 0.05f, 0.38f);
			break;
		}
		case ShapeType::T:
		{
			block->changeColor(FLinearColor(2.0f, 0.5f, 0.6f));
			currentColor = FLinearColor(2.0f, 0.5f, 0.6f);
			break;
		}
		case ShapeType::Z:
		{
			block->changeColor(FLinearColor(0.1f, 0.5f, 0.5f));
			currentColor = FLinearColor(0.1f, 0.5f, 0.5f);
			break;
		}
		default:
		{
			block->changeColor(FLinearColor::White);
		}
		break;

	}
	return block;

}

auto AMyGameStateBase::putShapeOnTheFloor() -> void
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			if (currentShape->hasBlock(i, j))
				field->addBlock(i + x, j + y);
		}

	if (field->hasFullCol())
	{
		score = 0;
		BeginPlay();
	}

	for (int j = 0; j < 20; j++)
	{
		if (field->hasFullRow(j)) {
			field->deleteFullRow(j);
			field->decreaseFullRow(j);
			score += 100;
			if (score > highScore)
			{
				highScore = score;
			}
		}
	}
	newShape();
}

auto AMyGameStateBase::left() -> void
{
	--x;
	if (isCollide())
		++x;
	else
		currentShape->moveTo(x, y);
}

auto AMyGameStateBase::right() -> void
{
	++x;
	if (isCollide())
		--x;
	else
		currentShape->moveTo(x, y);
}

auto AMyGameStateBase::rotate() -> void
{
	currentShape->rotL();
	if (isCollide())
		currentShape->rotR();
	else
		currentShape->moveTo(x, y);

}

auto AMyGameStateBase::down() -> void
{
	++y;
	if (isCollide()) {
		--y;
		putShapeOnTheFloor();
	}
	else {
		currentShape->moveTo(x, y);
	}
}

auto AMyGameStateBase::EndPlay(const EEndPlayReason::Type EndPlayReason) -> void
{
	field = nullptr;
	currentShape = nullptr;
}
