#include <tetris_game/blocks_factory.h>

#include <tetris_game/blocks.h>
#include <ctime>

BlocksFactory::BlocksFactory ():
    m_ranEng (std::time (0)),
    m_dist (0, 6)
{
}

BlocksFactory::BlocksFactory (size_t seed) :
    m_ranEng (seed),
    m_dist (0, 6)
{
}

std::unique_ptr<Block> BlocksFactory::GenerateBlock()
{
    switch (m_dist(m_ranEng))
    {
    case 0: return std::make_unique <JBlock>();
    case 1: return std::make_unique <LBlock>();
    case 2: return std::make_unique <IBlock>();
    case 3: return std::make_unique <OBlock>();
    case 4: return std::make_unique <SBlock>();
    case 5: return std::make_unique <TBlock>();
    case 6: return std::make_unique <ZBlock>();
    }
    return nullptr;
}
