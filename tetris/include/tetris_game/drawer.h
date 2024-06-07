#pragma once

class Block;
class Grid;

struct Color;

class Drawer
{
public:
    static void DrawGrid (int posX, int posY, const Grid& grid, int cellSize);
    static void DrawBlock (int posX, int posY, const Block* block, int cellSize);
    static void DrawGhostBlock (int posX, int posY, const Block* block, int cellSize);
    static void DrawBlockShade (int posX, int posY, const Block* block, int cellSize, const Color& color);

};