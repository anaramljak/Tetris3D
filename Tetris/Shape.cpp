
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
