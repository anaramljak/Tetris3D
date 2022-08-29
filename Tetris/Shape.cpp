
#include "Shape.h"
#include "MyGameStateBase.h"
#include "Block.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include <unordered_map>
#include <map>

Shape::Shape(class AMyGameStateBase &gs, ShapeType type)
{
	static std::unordered_map<ShapeType, const char*> shapes = {
		{ShapeType::I,
		 " *  " //
		 " *  " //
		 " *  " //
		 " *  "},
		{ShapeType::O,
		 "    " //
		 " ** " //
		 " ** " //
		 "    "},
		{ShapeType::T,
		 "    " //
		 "*** " //
		 " *  " //
		 "    "},
		{ShapeType::S,
		 "    " //
		 "**  " //
		 " ** " //
		 "    "},
		{ShapeType::Z,
		 "    " //
		 " ** " //
		 "**  " //
		 "    "},
		{ShapeType::J,
		 "  * " //
		 "  * " //
		 " ** " //
		 "    "},
		{ShapeType::L,
		 " *  " //
		 " *  " //
		 " ** " //
		 "    "},
	};

	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (shapes[type][x + y * 4] != ' ') {
				blocks[x][y] = gs.createBlock(type);
			}
			else
				blocks[x][y] = nullptr;
}


auto Shape::moveTo(int xx, int yy) -> void
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (blocks[x][y])
			  blocks[x][y]->SetActorLocation(FVector(150, (xx + x) * 100 - 440, 2070 - (yy + y) * 100));
}


auto Shape::hasBlock(int x, int y) const -> bool
{
	return blocks[x][y] != nullptr;
}

auto Shape::rotL() -> void
{
	rotR();
	rotR();
	rotR();
}

auto Shape::rotR() -> void
{
	static std::map<std::pair<int, int>, std::pair<int, int>> rotMap = {
	{{0, 0}, {3, 0}},
	{{1, 0}, {3, 1}},
	{{2, 0}, {3, 2}},
	{{3, 0}, {3, 3}},
	{{0, 1}, {2, 0}},
	{{1, 1}, {2, 1}},
	{{2, 1}, {2, 2}},
	{{3, 1}, {2, 3}},
	{{0, 2}, {1, 0}},
	{{1, 2}, {1, 1}},
	{{2, 2}, {1, 2}},
	{{3, 2}, {1, 3}},
	{{0, 3}, {0, 0}},
	{{1, 3}, {0, 1}},
	{{2, 3}, {0, 2}},
	{{3, 3}, {0, 3}},
	};
	std::array<std::array<class ABlock*, 4>, 4> tmpBlocks;

	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
		{
			auto tmp = rotMap[std::make_pair(x, y)];
			tmpBlocks[x][y] = blocks[tmp.first][tmp.second];
		}
	blocks = tmpBlocks;
}

Shape::~Shape()
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (blocks[x][y])
				blocks[x][y]->Destroy();
}
