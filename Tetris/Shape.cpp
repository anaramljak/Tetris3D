
#include "Shape.h"
#include "MyGameStateBase.h"
#include <unordered_map>

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
			if (shapes[type][x + y * 4] != ' ')
				blocks[x][y] = gs.createBlock();
			else
				blocks[x][y] = nullptr;
}

Shape::~Shape()
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (blocks[x][y])
				blocks[x][y]->Destroy();
}

auto Shape::moveTo(int xx, int yy) -> void
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (blocks[x][y])
			  blocks[x][y]->SetActorLocation(FVector(-240, (xx + x) * 100 - 760, 1970 - (yy + y) * 100));
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
	{{2, 1}, {2, 3}},
	{{0, 2}, {1, 0}},
	{{1, 2}, {1, 1}},
	{{2, 2}, {1, 2}},
	{{3, 2}, {1, 3}},
	{{0, 3}, {0, 0}},
	{{1, 3}, {0, 1}},
	{{2, 3}, {0, 2}},
	{{2, 3}, {0, 3}},
	};
	std::array<std::array<class AActor*, 4>, 4> tmpBlocks;
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
		{
			auto tmp = rotMap[std::make_pair(x, y)];
			tmpBlocks[x][y] = blocks[tmp.first][tmp.second];
		}
	blocks = tmpBlocks;
}

