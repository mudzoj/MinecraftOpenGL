#ifndef BLOCK_H
#define BLOCK_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



enum class BlockType {
	AIR = 0,
	GRASS = 1,
	DIRT = 2,
	STONE = 3
};
struct Block{
	BlockType type;
	bool isActive() const;

	Block(BlockType blockType = BlockType::AIR);  //default to these params if (any or all) are missing

};


#endif
