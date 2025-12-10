#include "Chunk.h"

Chunk::Chunk(glm::ivec3 chunkPosition) : chunkPos(chunkPosition) {
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				blocks[x][y][z] = Block(BlockType::AIR);
			}
		}
	}

}

Block Chunk::getBlock(int x, int y, int z) const {
	if (!isValidLocalCoord(x, y, z)) {
		return Block(BlockType::AIR);
	}
	return blocks[x][y][z];	
}

void Chunk::setBlock(int x, int y, int z, BlockType type) {
	if (isValidLocalCoord(x, y, z)) {
		blocks[x][y][z] = Block(type);
	}
}

glm::ivec3  Chunk::getChunkPosition() const {
	return chunkPos;
}

bool Chunk::isValidLocalCoord(int x, int y, int z) const {
	return  x >= 0 && x < CHUNK_SIZE &&
			y >= 0 && y < CHUNK_SIZE &&
			z >= 0 && z < CHUNK_SIZE;
}