#include "userInterface.h"

userInterface::userInterface(IBoard *obj)
{
    obj->InitBoard();


}

void userInterface::Play(IBoard *obj, visualization *showBoard)
{


    showBoard->display();
    cout<<"Move Left (a/A)                 Move Right(d/D)\n";
    cout<<"Rotate counter clockwise(k/K)   Rotate Clock wise(l/L)\n";
    cout<<"Release (x/X)\n";

    while (!obj->IsFinished())
    {
        char userInput;
        cin>>userInput;

        while (cin.fail() )
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Wrong Input!!! :";
            cin>>userInput;

        }

        switch (userInput)
        {
        case 'a':
        case 'A':
            obj->Move(MoveLeft_e);
            showBoard->display();
            break;
        case 'd':
        case 'D':
            obj->Move(MoveRight_e);
             showBoard->display();
            break;
        case 'x':
        case 'X':
            obj->Move(Release_e);
            showBoard->display();

            break;
        case 'k':
        case 'K':
            obj->Move(RotateCounterClockwise_e);
             showBoard->display();
            break;
        case 'l':
        case 'L':
            obj->Move(RotateClockwise_e);
             showBoard->display();

            break;

        }
        cout<<"Move Left (a/A)                 Move Right(d/D)\n";
        cout<<"Rotate counter clockwise(k/K)   Rotate Clock wise(l/L)\n";
        cout<<"Release (x/X)\n";


    }
}
