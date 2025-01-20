
#include "game.hpp"

#include <iostream>
#include <fstream>

using namespace std;

Game::Game(bool const& easy) :
    board(4 + easy)
{
    score = 0;
}

Game::Game(std::vector<int> const& board, int const& score) :
    board(board)
{
    this->score = score;
}

void Game::play(void)
{
    bool continuePlaying = true;
    bool couldMove = false;

    while
    (
        !board.hasValue(2048) && !(board.full() && !board.canMove()) &&
        continuePlaying
    )
    {
        displayState();
        displayChoices();

        char choice;
        cin >> choice;

        switch(choice)
        {
            case 'u': case 'U':
                if((couldMove = board.canMoveUp()))
                    score += board.moveUp();
            break;
            case 'd': case 'D':
                if((couldMove = board.canMoveDown()))
                    score += board.moveDown();
            break;
            case 'l': case 'L':
                if((couldMove = board.canMoveLeft()))
                    score += board.moveLeft();
            break;
            case 'r': case 'R':
                if((couldMove = board.canMoveRight()))
                    score += board.moveRight();
            break;
            case 'b': case 'B':
            break;
            case 's': case 'S':
                save();
                couldMove = false;
            break;
            case 'q': case 'Q':
                continuePlaying = false;
            break;
            default:
                couldMove = false;
        }

        if(couldMove)
            board.addRandomTile();
    }
    if(board.hasValue(2048))
    {
        displayState();

        cout << "YOU WON WITH A SCORE OF " << score << endl;
        char input;
        cin >> input;
    }
    else if(board.full() && !board.canMove())
    {
        displayState();

        cout << "YOU LOST!";
        char input;
        cin >> input;
    }
}

void Game::displayChoices(void) const
{
    cout << " u/U up " << endl
         << " d/D down " << endl
         << " l/L left " << endl
         << " r/R right " << endl
         << " b/B undo " << endl
         << " s/S save " << endl
         << " q/Q quit game (back to the welcome screen) " << endl;
}

void Game::displayState(void) const
{
    cout << "** Power-11 **" << endl;
    cout << "Score: " << score << endl;

    board.display(cout);
}

void Game::save(void) const
{
    ofstream savedGameFile("saved_game.txt");

    savedGameFile << score << endl;
    board.display(savedGameFile);
}

