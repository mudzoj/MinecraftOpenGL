#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"
#include <unordered_map>
#include <glm/glm.hpp>

class World {
public:
	World();

	Block getBlock(int x, int y, int z) const;
	void setBlock(int x, int y, int z, BlockType type);

	void generateMap(int sizeX, int sizeZ);

	std::unordered_map<std::string, Chunk>& getChunks();

private:
	std::unordered_map<std::string, Chunk> chunks;

	glm::ivec3 worldToChunkCoord(int x, int y, int z) const;
	glm::ivec3 worldToLocalCoord(int x, int y, int z) const;
	
	std::string chunkKey(glm::ivec3 chunkPos) const;
	Chunk& getOrCreateChunk(glm::ivec3 chunkPos);
};

#endif
