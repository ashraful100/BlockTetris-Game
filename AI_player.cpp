#include "AI_player.h"
#include <iostream>
#include "time.h"


using namespace std;

AI_player::AI_player(IBoard *obj,visualization *obj1):pBoard(obj),show(obj1)
{



}
//*******  pause time**********//
void AI_player::systemPause () {
    struct timespec timeOut,remains;

    timeOut.tv_sec = 0;
    timeOut.tv_nsec = 300000000; /* 3 milliseconds */

    nanosleep(&timeOut, &remains);

}
//************Check the position********/////
void AI_player::properPosition(IBoard *pBoard)
{
    pBoard->InitBoard();  //Run Initiat board
    int x=4,y=0,z;    // set the postion of x and y
    int ax[4],ay[4];
    //********** play Ai ************//
    while (!pBoard->IsFinished())
    {
        while (!pBoard->GetField(x+1,y)) {
            ax[4]={};ay[4]={};
            pBoard->Move(MoveRight_e);// Move right and find out the last position value

            ++x;


        }

        z=x; // last postion value



        while (!pBoard->GetField(x-1,y)&&x!=0) {
            pBoard->Move(MoveLeft_e);  // again move the block left and set this as inital position

            --x;

        }
        a=0,b=0;

        for(int jj=0;jj<4;jj++) // check fixed block 4 side use rotate
        {
            if(jj==1||jj==3){
                pBoard->Move(MoveRight_e);} //shift block right side for ignore error
            pBoard->Move(RotateClockwise_e);
            if(jj==0||jj==2){
                pBoard->Move(MoveLeft_e);} //shift block left side for ignore error rotate
            a=0,b=0;


            for(int x=1;x<=z;x++)
            {   y=0;
                while (!pBoard->GetField(x,y+1))// calculate the hight of every y posion
                {
                    y++;

                }


                if(x==1) { b=y;a=x;ax[jj]=x;ay[jj]=y;}// save the value a,b,ay[jj],ax[jj]

                if(b<y && x>1) {a=x;b=y;ax[jj]=x;ay[jj]=y; }//check which value of y has height number




            }

        }
        int maxx=0;
        for(int i=0;i<4;i++)
        {

            if(maxx<ay[i])// check which value of y highst change position and rotate
            {
                maxx=ay[i];
            }

        }

        for(int j=0;j<4;j++)
        {
            if(maxx==ay[j]) //check which x position hight x & which rotate point
            {
                a=ax[j];
                b=j;
            }

        }


        Play(pBoard); // run play function

        x=4,y=0,a=0,b=0; //re-set all values
    }





}
//***********Ai play and release fixed position************//
void AI_player::Play(IBoard *pBoard)
{
    for(int ii=0;ii<=b;ii++){
        pBoard->Move(RotateClockwise_e);// rotate
    }
    if(b==0||b==2)
    {
        for(int i =1 ;i<a;i++)
        {
            if(a>1)
            {
                pBoard->Move(MoveRight_e);
                systemPause ();
            }
            show->display();
        }}
    else if(b==1 || b==3)
    {
        for(int i =1 ;i<a;i++)
        {
            if(a>1)
            {
                pBoard->Move(MoveRight_e);
                systemPause ();
            }
            show->display();
        }}
    pBoard->Move(Release_e);  //release
    systemPause ();
    show->display();


}
