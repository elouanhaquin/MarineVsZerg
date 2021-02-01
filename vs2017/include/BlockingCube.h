#pragma once

#include <entity.h>

class BlockingCube : public Entity
{
private:
	bool blocking_cube_exist;

public:
	BlockingCube(Vector2D<int> position);
	~BlockingCube();

	bool exist() { return blocking_cube_exist; }

};

