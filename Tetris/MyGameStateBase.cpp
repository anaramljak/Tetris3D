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

	field->hasFullRow();
	
}

auto AMyGameStateBase::isCollide() const -> bool
{
	for (int xx = 0; xx < 4; ++xx)
		for (int yy = 0; yy < 4; ++yy)
			if (currentShape->hasBlock(xx, yy) && field->hasBlock(xx + x, yy + y))
				return true;
	return false;
}

auto AMyGameStateBase::createBlock() -> AActor *
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return GetWorld()->SpawnActor<ABlock>(blockClass, FVector{ 0, 0, 0 }, FRotator{ 0, 0, 0 }, param);

}

auto AMyGameStateBase::EndPlay(const EEndPlayReason::Type EndPlayReason) -> void
{
	field = nullptr;
	currentShape = nullptr;
}

auto AMyGameStateBase::putShapeOnTheFloor() -> void
{
	for (int xx = 0; xx < 4; ++xx)
		for (int yy = 0; yy < 4; ++yy)
		{
			if (currentShape->hasBlock(xx, yy))
				field->addBlock(xx + x, yy + y);
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