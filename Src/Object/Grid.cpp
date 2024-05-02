#include <DxLib.h>
#include "Grid.h"

Grid::Grid(void)
{
}

Grid::~Grid(void)
{
}

void Grid::Init(void)
{
}

void Grid::Update(void)
{
}

void Grid::Draw(void)
{
	for (int x = -HNUM; x <= HNUM-1; x++)
	{
		// xü(Ô)
		VECTOR sPos = { -HLEN,0.0f,50.0f * x };
		VECTOR ePos = {  HLEN,0.0f,50.0f * x };
		DrawLine3D(sPos, ePos, 0xff0000);
		DrawSphere3D(ePos, 20.0f, 10, 0xff0000, 0xff0000, true);

		// zü(Â)
		sPos = { 50.0f * x,0.0f,HLEN };
		ePos = { 50.0f * x,0.0f,-HLEN };
		DrawLine3D(sPos, ePos, 0x0000ff);
		DrawSphere3D(sPos, 20.0f, 10, 0x0000ff, 0x0000ff, true);

	}

}

void Grid::Release(void)
{
}
