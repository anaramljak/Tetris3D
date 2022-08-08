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

auto AMyGameStateBase::Tick(float DeltaTime) -> void
{
	if (GetWorld()->GetTimeSeconds() > nextMove)
	{
		++y;
		currentShape->moveTo(x, y);
		nextMove = GetWorld()->GetTimeSeconds() + 1;
	}
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