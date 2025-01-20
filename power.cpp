
#include "game.hpp"

#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

int main(void)
{
    srand(time(NULL));

    cout << "Welcome to Power-11!" << endl;

    bool continuePlaying = true;
    while(continuePlaying)
    {
        cout << "Please choose one of the options below" << endl
             << "e/E New easy game" << endl
             << "h/H New hard game" << endl
             << "r/R Resume game" << endl
             << "q/Q Quit" << endl;

        char choice;
        cin >> choice;

        switch(choice)
        {
            case 'e': case 'E':
            {
                Game power11(true);
                power11.play();
            }
            break;
            case 'h': case 'H':
            {
                Game power11(false);
                power11.play();
            }
            break;
            case 'r': case 'R':
            {
                ifstream is("saved_game.txt");

                int score;
                is >> score;

                string topBottomFrame;
                is >> topBottomFrame;

                size_t const size = (topBottomFrame.size() - 1) / 5;

                vector<int> board(size * size);
                for
                (
                    vector<int>::iterator tile = board.begin();
                    tile != board.end();
                    ++tile
                )
                {
                    char character;
                    is >> character;

                    is >> *tile;

                    if((tile - board.begin() + 1) % size == 0)
                        is >> character;
                }

                Game power11(board, score);
                power11.play();
            }
            break;
            case 'q': case 'Q':
                continuePlaying = false;
            break;
        }
    }

    return 0;
}

