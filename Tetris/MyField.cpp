#include "MyField.h"
#include "MyGameStateBase.h"

MyField::MyField(class AMyGameStateBase &gs) : gs(gs)
{
	for (int x = 0; x < 10; ++x)
		for (int y = 0; y < 20; ++y)
			blocks[x][y] = nullptr;
}

auto MyField::hasBlock(int x, int y) const -> bool
{
	if (x < 0 || x >= 10 || y < 0 || y >= 20)
		return true;
	return blocks[x][y] != nullptr;
}
auto MyField::addBlock(int x, int y) -> void
{
	if (blocks[x][y])
		return;
	blocks[x][y] = gs.get().createBlock();
	blocks[x][y]->SetActorLocation(FVector(-240, x * 100 - 760, 2070 - y * 100));

}

MyField::~MyField()
{
}

