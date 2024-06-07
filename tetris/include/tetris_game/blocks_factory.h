#pragma once

#include <tetris_game/block.h>
#include <memory>
#include <random>

class BlocksFactory
{
public:
    BlocksFactory ();
    BlocksFactory (size_t seed);
    std::unique_ptr<Block> GenerateBlock();

private:
    std::mt19937 m_ranEng;
    std::uniform_int_distribution <int> m_dist;
};
