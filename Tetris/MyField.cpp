
#include "MyField.h"
#include "MyGameStateBase.h"

MyField::MyField(class AMyGameStateBase &gs) : gs(gs)
{
	for (int x = 0; x < 10; ++x) {
		for (int y = 0; y < 20; ++y) {
			for (int z = 0; z < 10; ++z) {
				blocks[x][y][z] = nullptr;
			}
		}
	}
}

auto MyField::hasBlock(int x, int y, int z) const -> bool
{
	if (x < 0 || x >= 10 || y < 0 || y >= 20 || z < 0 || z >= 10)
		return true;
	return blocks[x][y][z] != nullptr;
}

auto MyField::addBlock(int x, int y, int z) -> void
{
	if (blocks[x][y][z])
		return;
	blocks[x][y][z] = gs.get().createBlock(ShapeType::NONE);
	blocks[x][y][z]->SetActorLocation(FVector(570 - (z-1)  *  100, x * 100 - 440, 2070 - y * 100));
	blocks[x][y][z]->changeColor(gs.get().currentColor);

}


auto MyField::hasFullRow(int j, int k) -> bool
{
	int count = 0;
	for (int i = 0; i < 10; i++) {
		if (hasBlock(i, j, k)) {
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

auto MyField::hasFullRowDiagonal(int j, int i) -> bool
{
	int count = 0;
	for (int k = 0; k < 10; k++) {
		if (hasBlock(i, j, k)) {
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

auto MyField::deleteFullRow(int j, int k) -> void
{ 
	for (int i = 0; i < 10; i++) {	
			blocks[i][j][k]->SetActorHiddenInGame(true);
			blocks[i][j][k] = nullptr;
	}

}

auto MyField::decreaseFullRow(int j, int l) -> void
{
	for (int k = j; k > 0; --k) {
		for (int i = 0; i < 10; i++) {
				if (hasBlock(i, k, l)) {
					blocks[i][k][l]->SetActorLocation(FVector(570 - (l - 1) * 100, i * 100 - 440, 2070 - (k + 1) * 100));
				}
				blocks[i][k][l] = blocks[i][k - 1][l];
		}
	}
}

auto MyField::deleteFullRowDiagonal(int j, int i) -> void
{
	for (int k = 0; k < 10; k++) {
		blocks[i][j][k]->SetActorHiddenInGame(true);
		blocks[i][j][k] = nullptr;
	}

}

auto MyField::decreaseFullRowDiagonal(int j, int l) -> void
{
	for (int k = j; k > 0; --k) {
		for (int i = 0; i < 10; i++) {
			if (hasBlock(l, k, i)) {
				blocks[l][k][i]->SetActorLocation(FVector(570 - (i - 1) * 100, l * 100 - 440, 2070 - (k + 1) * 100));
			}
			blocks[l][k][i] = blocks[i][k - 1][l];
		}
	}
}


auto MyField::hasFullCol() -> bool
{
	for (int i = 0; i < 10; i++) {
		for (int k = 0; k < 10; k++)
		{
			if (hasBlock(i, 1, k))
			{
				for (int x = 0; x < 10; ++x)
					for (int y = 0; y < 20; ++y) {
						for (int z = 0; z < 10; ++z) {
							if (hasBlock(x, y, z)) {
								blocks[x][y][z]->SetActorHiddenInGame(true);
								blocks[x][y][z] = nullptr;
							}
						}
					}

				return true;
			}
		}
	}
	return false;
}


MyField::~MyField()
{
}

