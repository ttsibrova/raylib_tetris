#pragma once
#include <core/block.h>
#include <functional/colors.h>


class LBlock: public Block
{
public:
    LBlock () :
        Block (0, 1)
    {
        std::array <std::vector <GridPosition>, 4> cells;
        cells[0] = {{0, 2}, {1, 0}, {1, 1}, {1, 2}};
        cells[1] = {{0, 1}, {1, 1}, {2, 1}, {2, 2}};
        cells[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 0}};
        cells[3] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
        SetCells (std::move (cells));

        std::array <GridPositionBBox, 4> bboxes;
        bboxes[0] = {{0, 0}, {1, 2}};
        bboxes[1] = {{0, 1}, {2, 2}};
        bboxes[2] = {{1, 0}, {2, 2}};
        bboxes[3] = {{0, 0}, {2, 1}};
        SetBBoxes (std::move (bboxes));
    }

};


class JBlock: public Block
{
public:
    JBlock ():
        Block (1, 2)
    {
        std::array <std::vector <GridPosition>, 4> cells;
        cells[0] = {{1, 0}, {1, 1}, {1, 2}, {2, 2}};
        cells[1] = {{0, 1}, {1, 1}, {2, 0}, {2, 1}};
        cells[2] = {{0, 0}, {1, 0}, {1, 1}, {1, 2}};
        cells[3] = {{0, 1}, {0, 2}, {1, 1}, {2, 1}};
        SetCells (std::move (cells));

        std::array <GridPositionBBox, 4> bboxes;
        bboxes[0] = {{1, 0}, {2, 2}};
        bboxes[1] = {{0, 0}, {2, 1}};
        bboxes[2] = {{0, 0}, {1, 2}};
        bboxes[3] = {{0, 1}, {2, 2}};
        SetBBoxes (std::move (bboxes));
    }

};

class IBlock: public Block
{
public:
    IBlock ():
        Block (2, 3)
    {
        std::array <std::vector <GridPosition>, 4> cells;
        cells[0] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
        cells[1] = {{0, 2}, {1, 2}, {2, 2}, {3, 2}};
        cells[2] = {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
        cells[3] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
        SetCells (std::move (cells));

        std::array <GridPositionBBox, 4> bboxes;
        bboxes[0] = {{1, 0}, {1, 3}};
        bboxes[1] = {{0, 2}, {3, 2}};
        bboxes[2] = {{2, 0}, {2, 3}};
        bboxes[3] = {{0, 1}, {3, 1}};
        SetBBoxes (std::move (bboxes));
    }
};

class OBlock: public Block
{
public:
    OBlock ():
        Block (3, 4)
    {
        std::array <std::vector <GridPosition>, 4> cells;
        cells[0] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        cells[1] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        cells[2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        cells[3] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
        SetCells (std::move (cells));

        std::array <GridPositionBBox, 4> bboxes;
        bboxes[0] = {{0, 0}, {1, 1}};
        bboxes[1] = {{0, 0}, {1, 1}};
        bboxes[2] = {{0, 0}, {1, 1}};
        bboxes[3] = {{0, 0}, {1, 1}};
        SetBBoxes (std::move (bboxes));
    }
};

class SBlock: public Block
{
public:
    SBlock ():
        Block (4, 5)
    {
        std::array <std::vector <GridPosition>, 4> cells;
        cells[0] = {{0, 1}, {0, 2}, {1, 0}, {1, 1}};
        cells[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 2}};
        cells[2] = {{1, 1}, {1, 2}, {2, 0}, {2, 1}};
        cells[3] = {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
        SetCells (std::move (cells));

        std::array <GridPositionBBox, 4> bboxes;
        bboxes[0] = {{0, 0}, {1, 2}};
        bboxes[1] = {{0, 1}, {2, 2}};
        bboxes[2] = {{1, 0}, {2, 2}};
        bboxes[3] = {{0, 0}, {2, 1}};
        SetBBoxes (std::move (bboxes));
    }
};


class TBlock: public Block
{
public:
    TBlock ():
        Block (5, 6)
    {
        std::array <std::vector <GridPosition>, 4> cells;
        cells[0] = {{0, 1}, {1, 0}, {1, 1}, {1, 2}};
        cells[1] = {{0, 1}, {1, 1}, {1, 2}, {2, 1}};
        cells[2] = {{1, 0}, {1, 1}, {1, 2}, {2, 1}};
        cells[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 1}};
        SetCells (std::move (cells));

        std::array <GridPositionBBox, 4> bboxes;
        bboxes[0] = {{0, 0}, {1, 2}};
        bboxes[1] = {{0, 1}, {2, 2}};
        bboxes[2] = {{1, 0}, {2, 2}};
        bboxes[3] = {{0, 0}, {2, 1}};
        SetBBoxes (std::move (bboxes));
    }
};

class ZBlock: public Block
{
public:
    ZBlock ():
        Block (6, 7)
    {
        std::array <std::vector <GridPosition>, 4> cells;
        cells[0] = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
        cells[1] = {{0, 2}, {1, 1}, {1, 2}, {2, 1}};
        cells[2] = {{1, 0}, {1, 1}, {2, 1}, {2, 2}};
        cells[3] = {{0, 1}, {1, 0}, {1, 1}, {2, 0}};
        SetCells (std::move (cells));

        std::array <GridPositionBBox, 4> bboxes;
        bboxes[0] = {{0, 0}, {1, 2}};
        bboxes[1] = {{0, 1}, {2, 2}};
        bboxes[2] = {{1, 0}, {2, 2}};
        bboxes[3] = {{0, 0}, {2, 1}};
        SetBBoxes (std::move (bboxes));
    }
};
