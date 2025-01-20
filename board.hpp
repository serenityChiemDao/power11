
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <iostream>

class Board
{
    public:
        Board(size_t const& size);
        Board(std::vector<int> const& board);

        bool full(void) const;
        bool hasValue(int const& value) const;

        void display(std::ostream& os) const;

        void addRandomTile(void);

        bool canMove(void);
        bool canMoveUp(void);
        bool canMoveDown(void);
        bool canMoveLeft(void);
        bool canMoveRight(void);

        int moveUp(void);
        int moveDown(void);
        int moveLeft(void);
        int moveRight(void);

    private:
        size_t const size;
        std::vector<int> board;
        std::vector<int>::iterator furthestNonZeroTileIndex
        (
            std::vector<int>::iterator const& tileIndex,
            std::vector<int>::iterator const& firstTileOfLineIndex,
            int const& nextTileOffset
        );
        bool canMove
        (
            int const& onePastLastLineOffset, int const& nextLineOffset,
            int const& firstTileToMoveOffset,
            int const& onePastLastTileToMoveOffset, int const& nextTileOffset
        );
        int move
        (
            int const& onePastLastLineOffset, int const& nextLineOffset,
            int const& firstTileToMoveOffset,
            int const& onePastLastTileToMoveOffset, int const& nextTileOffset
        );
};

#endif

