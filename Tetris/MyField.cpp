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
	blocks[x][y]->SetActorLocation(FVector(150, x * 100 - 440, 2070 - y * 100));

}

void MyField::hasFullRow()
{
	std::array<int, 10> xs;
	for (int j = 0; j < 20; j++)
	{
		int count = 0;
		for (int i = 0; i < 10; i++)
		{
			if (hasBlock(i, j)) {
				xs[count] = i;
				count++;
			}
			else {
				break;
			}				
			
		}

		if (count == 10) {
			for (int i = 0; i < 10; i++) {
				blocks[i][j]->SetActorHiddenInGame(true);
				blocks[i][j] = nullptr;
			}
		}
	} 	
}

bool MyField::hasFullCol()
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

