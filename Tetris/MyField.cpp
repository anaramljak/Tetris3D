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
	std::array<int,10> xs;
	int count = 0;
	for (int yy = 0; yy < 20; yy++)
	{
		for (int xx = 0; xx < 10; xx++)
		{
			if (hasBlock(xx, yy)) {
				xs[count] = xx;
				count++;
			}
			else {
				count = 0;
			}				
			
		}
		if (count == 10) {
			for (int i = 0; i < 10; i++) {
				int x = xs[i];
				blocks[x][yy]->SetActorHiddenInGame(true);
				blocks[x][yy]->SetActorEnableCollision(false);
				blocks[x][yy]->SetActorTickEnabled(false);
			}
		}
	}
		
}

MyField::~MyField()
{
}

