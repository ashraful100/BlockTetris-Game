#include <iostream>
#include "myDerivedCLass.h"
#include "AI_player.h"
#include "userInterface.h"
#include "visualization.h"

using namespace std;

int main ()
{
    int choise;
    cout<<"Choose 1 for Autommatic Player Or 2 for User mood:";
    cin>>choise;
    while (cin.fail() || choise>2 || choise<1)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Wrong Input!!  1) for Autommatic Player || 2) for User mood:";
        cin>>choise;
    }

    if (choise==1)
    {
        myIBoard myGameBoard;
        visualization show(&myGameBoard);
        AI_player playGame(&myGameBoard,&show);
        playGame.properPosition (&myGameBoard);
        show.display();
     }

    else if (choise==2)
    {
        myIBoard myGameBoard;
        visualization show(&myGameBoard);
        userInterface playGame(&myGameBoard);
        playGame.Play(&myGameBoard,&show);
    }
}
