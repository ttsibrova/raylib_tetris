#pragma once
#include <core/grid.h>

class DrawSettings;
class Block;

class Drawer
{
public:
    static void DrawGrid (int posX, int posY, const Grid& grid, const DrawSettings& settings);
    static void DrawBlock (int posX, int posY, const Block*, const DrawSettings& settings);

};