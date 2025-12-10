#include "Block.h"

Block::Block(BlockType blockType) : type(blockType) {
}

bool Block::isActive() const {
    return type != BlockType::AIR;
}