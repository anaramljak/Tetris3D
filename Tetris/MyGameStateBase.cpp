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
			break;
		}
		case ShapeType::L:
		{
			block->changeColor(FLinearColor::Red);
			break;
		}
		case ShapeType::I:
		{
			block->changeColor(FLinearColor::Green);
			break;
		}
		case ShapeType::J:
		{
			block->changeColor(FLinearColor::Blue);
			break;
		}
		case ShapeType::S:
		{
			block->changeColor(FLinearColor(0.26f, 0.05f, 0.38f));
			break;
		}
		case ShapeType::T:
		{
			block->changeColor(FLinearColor(0.38f, 0.01f, 0.37f));
			break;
		}
		case ShapeType::Z:
		{
			block->changeColor(FLinearColor(0.62f, 0.25f, 0.05f));
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
		if (score > highScore)
		{
			highScore = score;
			score = 0;
		}
		BeginPlay();
	}

	for (int j = 0; j < 20; j++)
	{
		if (field->hasFullRow(j)) {
			field->deleteFullRow(j);
			field->decreaseFullRow(j);
			score += 100;
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
