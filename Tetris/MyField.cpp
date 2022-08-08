#include "MyField.h"
#include "MyGameStateBase.h"

MyField::MyField(class AMyGameStateBase &gs) : gs(gs)
{
}

auto MyField::hasBlock(int x, int y) const -> bool
{
	return blocks[x][y] != nullptr;
}
auto MyField::addBlock(int x, int y) -> void
{
	if (blocks[x][y])
		return;
	blocks[x][y] = gs.get().createBlock();
	blocks[x][y]->SetActorLocation(FVector(-240, x * 100 - 760, 1970 - y * 100));

}

MyField::~MyField()
{
}

