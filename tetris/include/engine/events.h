#pragma once


enum class ClassicTetrisGameScreenEvent
{
    SCORE_UPDATED,
    COMBO_UPDATED,
    HOLD_BLOCK_UPDATED,
    NEXT_BLOCK_UPDATED,
    NUM_REMOVED_LINES_UPDATED,
    SPEED_LVL_UPDATED,
    GAME_OVER,
    PAUSE,
    UNPAUSE
};