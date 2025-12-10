#ifndef CHUNK_H
#define CHUNK_H

#include "Block.h"
#include <glm/glm.hpp>


class Chunk {
	
public:
	static const int CHUNK_SIZE = 16;
	
	Chunk(glm::ivec3 chunkPosition);

	Block getBlock(int x, int y, int z) const;
	
	void setBlock(int x, int y, int z, BlockType type);

	glm::ivec3 getChunkPosition() const;

private:
	Block blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	glm::ivec3 chunkPos;

	bool isValidLocalCoord(int x, int y, int z) const;

};
#endif