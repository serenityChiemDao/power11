
#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"

class Game
{
    public:
        Game(bool const& easy);
        Game(std::vector<int> const& board, int const& score);

        void play(void);

    private:
        Board board;
        int score;

        void displayChoices(void) const;
        void displayState(void) const;

        void save(void) const;
};

#endif

