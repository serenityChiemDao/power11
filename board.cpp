
#include "board.hpp"

#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>

#include <cstdlib>

using namespace std;

typedef std::vector <int> matrix;

typedef matrix::iterator matrixIt;
typedef matrix::const_iterator cMatrixIt;

Board::Board(std::vector<int> const& board) :
    size(sqrt(board.size()))
{
    this->board = board;
}

Board::Board(const size_t& size) :
    size(size)
{
    board = matrix(size * size);

    addRandomTile();
    addRandomTile();
}

bool Board::full(void) const
{
    for
    (
        cMatrixIt tileIterator = board.begin();
        tileIterator != board.end();
        ++tileIterator
    )
        if(*tileIterator == 0)
            return false;
    return true;
}

bool Board::hasValue(int const& value) const
{
    return find(board.begin(), board.end(), value) != board.end();
}

void Board::display(std::ostream& os) const
{
    const string frameTopAndBottom = string(5 * size + 1, '#');

    os << frameTopAndBottom << endl;
    for
    (
        cMatrixIt lineIterator = board.begin();
        lineIterator != board.end();
        lineIterator += size
    )
    {
        os << "#";
        for
        (
            cMatrixIt tileIterator = lineIterator;
            tileIterator != lineIterator + size - 1;
            ++tileIterator
        )
            os << setw(4) << *tileIterator << "|";
        os << setw(4) << *(lineIterator + size - 1) << "#";
        os << endl;
    }
    os << frameTopAndBottom << endl;
}

void Board::addRandomTile(void)
{
    vector<matrixIt> emptyTileIterators;

    for
    (
        matrixIt tileIterator = board.begin();
        tileIterator != board.end();
        ++tileIterator
    )
        if(*tileIterator == 0)
            emptyTileIterators.push_back(tileIterator);

    vector<matrixIt>::size_type size = emptyTileIterators.size();

    if(size != 0)
        *emptyTileIterators[rand() % size] = rand() % 10 < 9 ? 2 : 4;
}

bool Board::canMove(void)
{
    return canMoveUp() | canMoveDown() | canMoveLeft() | canMoveRight();
}

bool Board::canMoveUp(void)
{
    return canMove(size, 1, size, size * size, size);
}

bool Board::canMoveDown(void)
{
    return canMove(size, 1, (size - 2) * size, -size, - size);
}

bool Board::canMoveLeft(void)
{
    return canMove(size * size, size, 1, size, 1);
}

bool Board::canMoveRight(void)
{
    return canMove(size * size, size, size - 2, -1, -1);
}

int Board::moveUp(void)
{
    return move(size, 1, size, size * size, size);
}

int Board::moveDown(void)
{
    return move(size, 1, (size - 2) * size, -size, - size);
}

int Board::moveLeft(void)
{
    return move(size * size, size, 1, size, 1);
}

int Board::moveRight(void)
{
    return move(size * size, size, size - 2, -1, -1);
}

matrixIt Board::furthestNonZeroTileIndex
(
    matrixIt const& tileIterator, matrixIt const& firstTileOfLineIndex,
    int const& nextTileOffset
)
{
    matrixIt furthestNonZeroTileIndex;
    for
    (
        furthestNonZeroTileIndex = tileIterator;
        furthestNonZeroTileIndex != firstTileOfLineIndex &&
        *(furthestNonZeroTileIndex - nextTileOffset) == 0;
        furthestNonZeroTileIndex -= nextTileOffset
    );
    return furthestNonZeroTileIndex;
}

bool Board::canMove
(
    int const& onePastLastLineOffset, int const& nextLineOffset,
    int const& firstTileToMoveOffset, int const& onePastLastTileToMoveOffset,
    int const& nextTileOffset
)
{
    for
    (
        matrixIt lineIterator = board.begin();
        lineIterator != board.begin() + onePastLastLineOffset;
        lineIterator += nextLineOffset
    )
    {
        matrixIt const firstTileOfLineIndex =
        lineIterator + firstTileToMoveOffset - nextTileOffset;
        matrixIt lastMergedTileIndex = board.begin() - 1;
        for
        (
            matrixIt tileIterator = lineIterator + firstTileToMoveOffset;
            tileIterator != lineIterator + onePastLastTileToMoveOffset;
            tileIterator += nextTileOffset
        )
        {
            int tile;
            if((tile = *tileIterator) != 0)
            {
                matrixIt furthestNZeroTileIndex =
                furthestNonZeroTileIndex
                (tileIterator, firstTileOfLineIndex, nextTileOffset);

                matrixIt const mergeCandidateTileIndex =
                furthestNZeroTileIndex - nextTileOffset;

                if(furthestNZeroTileIndex == firstTileOfLineIndex)
                    return true;
                else if
                (
                    lastMergedTileIndex != mergeCandidateTileIndex &&
                    *mergeCandidateTileIndex == tile
                )
                    return true;
                else if(furthestNZeroTileIndex != tileIterator)
                    return true;
            }
        }
    }
    return false;
}

int Board::move
(
    int const& onePastLastLineOffset, int const& nextLineOffset,
    int const& firstTileToMoveOffset, int const& onePastLastTileToMoveOffset,
    int const& nextTileOffset
)
{
    int score = 0;
    for
    (
        matrixIt lineIterator = board.begin();
        lineIterator != board.begin() + onePastLastLineOffset;
        lineIterator += nextLineOffset
    )
    {
        matrixIt const firstTileOfLineIndex =
        lineIterator + firstTileToMoveOffset - nextTileOffset;
        matrixIt lastMergedTileIndex = board.begin() - 1;
        for
        (
            matrixIt tileIterator = lineIterator + firstTileToMoveOffset;
            tileIterator != lineIterator + onePastLastTileToMoveOffset;
            tileIterator += nextTileOffset
        )
        {
            int tile;
            if((tile = *tileIterator) != 0)
            {
                matrixIt furthestNZeroTileIndex =
                furthestNonZeroTileIndex
                (tileIterator, firstTileOfLineIndex, nextTileOffset);

                *tileIterator = 0;

                matrixIt const mergeCandidateTileIndex =
                furthestNZeroTileIndex - nextTileOffset;

                if(furthestNZeroTileIndex == firstTileOfLineIndex)
                    *firstTileOfLineIndex = tile;
                else if
                (
                    lastMergedTileIndex != mergeCandidateTileIndex &&
                    *mergeCandidateTileIndex == tile
                )
                {
                    lastMergedTileIndex = mergeCandidateTileIndex;
                    *mergeCandidateTileIndex += tile;
                    score += tile * 2;
                }
                else
                    *furthestNZeroTileIndex = tile;
            }
        }
    }
    return score;
}

