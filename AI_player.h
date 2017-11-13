#ifndef AI_PLAYER_H
#define AI_PLAYER_H
#include "Interfaces.h"
#include "visualization.h"
#include <vector>


class AI_player : public IPlayer
{
public:

    IBoard *pBoard;
    AI_player(IBoard *obj,visualization *obj1);
    visualization *show;
    void systemPause ();
    int a=0,b=0;
    void properPosition(IBoard * pBoard);
    void Play(IBoard * pBoard);
    int counter=0;
};

#endif // AI_PLAYER_H
