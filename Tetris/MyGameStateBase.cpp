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
	for (int xx = 0; xx < 4; ++xx)
		for (int yy = 0; yy < 4; ++yy)
			if (currentShape->hasBlock(xx, yy) && field->hasBlock(xx + x, yy + y))
				return true;
	return false;
}

auto AMyGameStateBase::createBlock(ShapeType type) -> ABlock *
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ABlock* a = GetWorld()->SpawnActor<ABlock>(blockClass, FVector{ 0, 0, 0 }, FRotator{ 0, 0, 0 }, param);
	switch (type) {
		case ShapeType::O:
		{
			
			a->changeColor(FLinearColor::Yellow);
			break;
		}
		case ShapeType::L:
		{
			a->changeColor(FLinearColor::Red);
			break;
		}
		case ShapeType::I:
		{
			a->changeColor(FLinearColor::Green);
			break;
		}
		case ShapeType::J:
		{
			a->changeColor(FLinearColor::Blue);
			break;
		}
		case ShapeType::S:
		{
			a->changeColor(FLinearColor(0.26f, 0.05f, 0.38f));
			break;
		}
		case ShapeType::T:
		{
			a->changeColor(FLinearColor(0.38f, 0.01f, 0.37f));
			break;
		}
		case ShapeType::Z:
		{
			a->changeColor(FLinearColor(0.62f, 0.25f, 0.05f));
			break;
		}
		default:
		{
			a->changeColor(FLinearColor::White);
		}
		break;

	}
	return a;

}

auto AMyGameStateBase::putShapeOnTheFloor() -> void
{
	for (int xx = 0; xx < 4; ++xx)
		for (int yy = 0; yy < 4; ++yy)
		{
			if (currentShape->hasBlock(xx, yy))
				field->addBlock(xx + x, yy + y);
		}

	if (field->hasFullCol())
	{
		BeginPlay();
	}

	field->cleanFullRow();
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
