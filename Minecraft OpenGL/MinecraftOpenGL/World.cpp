#include "World.h"
#include "Block.h"
#include <sstream>

World::World() {
}

Block World::getBlock(int x, int y, int z) const {
    glm::ivec3 chunkPos = worldToChunkCoord(x, y, z);
    glm::ivec3 localPos = worldToLocalCoord(x, y, z);

    std::string key = chunkKey(chunkPos);
    auto it = chunks.find(key);

    if (it == chunks.end()) {
        return Block(BlockType::AIR);
    }

    return it->second.getBlock(localPos.x, localPos.y, localPos.z);
}

void World::setBlock(int x, int y, int z, BlockType type) {
    glm::ivec3 chunkPos = worldToChunkCoord(x, y, z);
    glm::ivec3 localPos = worldToLocalCoord(x, y, z);

    Chunk& chunk = getOrCreateChunk(chunkPos);
    chunk.setBlock(localPos.x, localPos.y, localPos.z, type);
}

void World::generateMap(int sizeX, int sizeZ) {
    for (int x = 0; x < sizeX; x++) {
        for (int z = 0; z < sizeZ; z++) {
            Chunk& chunk = getOrCreateChunk(glm::ivec3(x, 0, z));

            for (int blockX = 0; blockX < chunk.CHUNK_SIZE; blockX++) {
                for (int blockY = 0; blockY < chunk.CHUNK_SIZE; blockY++) {
                    for (int blockZ = 0; blockZ < chunk.CHUNK_SIZE; blockZ++) {
                        chunk.setBlock(blockX, blockY, blockZ, BlockType::GRASS);
                    }
                }
            }
        }
    }
    
}

std::unordered_map<std::string, Chunk>& World::getChunks() {
    return chunks;
}

glm::ivec3 World::worldToChunkCoord(int x, int y, int z) const {
    
    int chunkX = (x < 0) ? ((x + 1) / Chunk::CHUNK_SIZE - 1) : (x / Chunk::CHUNK_SIZE);
    int chunkY = (y < 0) ? ((y + 1) / Chunk::CHUNK_SIZE - 1) : (y / Chunk::CHUNK_SIZE);
    int chunkZ = (z < 0) ? ((z + 1) / Chunk::CHUNK_SIZE - 1) : (z / Chunk::CHUNK_SIZE);
        
    return glm::ivec3(chunkX,chunkY,chunkZ);
}

glm::ivec3 World::worldToLocalCoord(int x, int y, int z) const {    
    //normalize to 0->CHUNK_SIZE
    //negative coord turns to positive equiv: -5%16 = -5 -----> 11
    int localX = ((x % Chunk::CHUNK_SIZE) + Chunk::CHUNK_SIZE) % Chunk::CHUNK_SIZE;
    int localY = ((y % Chunk::CHUNK_SIZE) + Chunk::CHUNK_SIZE) % Chunk::CHUNK_SIZE;
    int localZ = ((z % Chunk::CHUNK_SIZE) + Chunk::CHUNK_SIZE) % Chunk::CHUNK_SIZE;

    return glm::ivec3(localX, localY, localZ);
}

std::string World::chunkKey(glm::ivec3 chunkPos) const {
    
    return std::to_string(chunkPos.x) + "," +
        std::to_string(chunkPos.y) + "," +
        std::to_string(chunkPos.z);
}

Chunk& World::getOrCreateChunk(glm::ivec3 chunkPos) {
    std::string key = chunkKey(chunkPos);
    auto it = chunks.find(key);

    if (it == chunks.end()) {
        auto result = chunks.emplace(key, Chunk(chunkPos));
        it = result.first;
        
    }

     return it->second;

}