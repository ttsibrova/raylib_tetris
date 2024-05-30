#pragma once

class Block;
class DrawSettings;
class Grid;

struct Color;

class Drawer
{
public:
    static void DrawGrid (int posX, int posY, const Grid& grid, const DrawSettings& settings);
    static void DrawBlock (int posX, int posY, const Block* block, const DrawSettings& settings);
    static void DrawGhostBlock (int posX, int posY, const Block* block, const DrawSettings& settings);
    static void DrawBlockShade (int posX, int posY, const Block* block, int cellSize, const Color& color);

};