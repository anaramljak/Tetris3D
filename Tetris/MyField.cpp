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
	blocks[x][y] = gs.get().createBlock(ShapeType::NONE);
	blocks[x][y]->SetActorLocation(FVector(150, x * 100 - 440, 2070 - y * 100));
	blocks[x][y]->changeColor(gs.get().currentColor);

}

auto MyField::hasFullRow(int j) -> bool
{
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		if (hasBlock(i, j)) {
			count++;
		}
		else {
			break;
		}
	}

	if (count == 10) {
		return true;
	}
	return false;
}

auto MyField::deleteFullRow(int j) -> void
{
	for (int i = 0; i < 10; i++) {
		blocks[i][j]->SetActorHiddenInGame(true);
		blocks[i][j] = nullptr;
	}

}

auto MyField::decreaseFullRow(int j) -> void
{
	for (int k = j; k > 0; --k) {
		for (int i = 0; i < 10; i++) {
			if (hasBlock(i, k)) {
				blocks[i][k]->SetActorLocation(FVector(150, i * 100 - 440, 2070 - (k + 1) * 100));
			}
			blocks[i][k] = blocks[i][k - 1];
		}
	}
}

auto MyField::hasFullCol() -> bool
{
	for (int i = 0; i < 10; i++)
	{
		if (hasBlock(i, 1))
		{
			for (int x = 0; x < 10; ++x)
				for (int y = 0; y < 20; ++y) {
					if (hasBlock(x, y)) {
						blocks[x][y]->SetActorHiddenInGame(true);
						blocks[x][y] = nullptr;
					}
				}
			return true;
		}
	}
	return false;
}


MyField::~MyField()
{
}

