#include "myDerivedCLass.h"
#include <time.h>



myIBoard::myIBoard()
{

}
/*---------------------------------------------------------------------
            Initially generate  blocks
----------------------------------------------------------------------*/
void myIBoard::InitBoard()
{
    
    for(int i=0;i<17;i++)
    {
        for (int j=0;j<17;j++)
        {
            if(j==0 || j==11)
            {
                if(i<4)
                {
                    gameField[i][j]=3;
                    temp[i][j]=3;

                }
                else {gameField[i][j]=5; temp[i][j]=5;}
            }
            else if(i==16 &&j<11 ) {gameField[i][j]=5; temp[i][j]=5;}


            else {gameField[i][j]=0; temp[i][j]=0;}
        }
    }

    // small box design

    for(int i=0;i<17;i++)
    {
        for (int j=16;j<22;j++)
        {
            if((j==16 || j==21) && i<6)
            {
                gameField[i][j]=3;
            }


            else if((i==0 || i==5) )
            {
                gameField[i][j]=3;
            }


            else if(i==8 && j==16)
            {
                gameField[i][j]=6;

            }
            else if(i==9  && j==16)
            {
                gameField[i][j]=7;

            }
            else if(i==11 && j==16)
            {
                gameField[i][j]=8;

            }
            else if(i==12 && j==16)
            {
                gameField[i][j]=9;

            }
            else if(i==13 && j==16)
            {
                gameField[i][j]=10;

            }

            else
            {
                gameField[i][j]=0;
            }
        }
    }

    for (int i=0;i<4;i++){
        for(int j=0;j<4;j++){

            block[0][i][j]=tetrisBlock[GetNextBlockType()][i][j];
        }
    }

    //Initailly block Generate
    int rand1,rand2;

    srand(time(NULL));

    rand1=rand()%7;

    rand2=rand()%7;

    for(int i=0;i<4;i++)
    {for (int j=0;j<4;j++)
        {
            block [0][i][j]=tetrisBlock[rand1][i][j] ; //block[0] initialize at top of the board
            block [1][i][j]=tetrisBlock[rand2][i][j] ;//block[1] initialize as next block

        }
    }
    initiallyBlockGenerate(); //this function will update the board with block[0] & block [1]

}
/*---------------------------------------------------------------------
            Get Field
----------------------------------------------------------------------*/

unsigned int myIBoard::GetField(unsigned int PosX, unsigned int PosY) const
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[0][i][j] && (temp[PosY + i][PosX + j] != 0))
            {

                return 1;

            }
        }
    }

    return 0;
}

/*---------------------------------------------------------------------
            Move Function
----------------------------------------------------------------------*/


void myIBoard::Move(Movement_E Movement)
{
    switch (Movement) {
    case MoveLeft_e:
        if (!GetField(x-1,y))
        {
            updateGameField(x-1,y,gameField);

        }

        break;
    case MoveRight_e:
        if (!GetField(x+1,y))
        {
            updateGameField(x+1,y,gameField);
        }

        break;
    case RotateClockwise_e:
        RotateTetrisBlock(1);

        break;

    case RotateCounterClockwise_e:
        RotateTetrisBlock(2);

        break;
    case Release_e:
        while (!GetField(x,y+1))
        {
            updateGameField(x,y+1,gameField);
        }
        for (int i=0;i<4;i++){
            for(int j=0;j<4;j++){

                block[0][i][j]=block[1][i][j]; //copying the next block into current block
            }
        }
        for(int i=0;i<17;i++)
        {
            for(int j=0;j<22;j++) {temp[i][j]=gameField[i][j];}
        }

        getTheNextBlock(GetNextBlockType()); //generate new block

        x=4;y=0;    // set the default coordinates for new block
        if(!IsFinished()) {initiallyBlockGenerate();}; // Again initialize the block

        certainGetRemovedRow(); // if any rows filled the it will remove that row and update the board


        break;


    }
}

/*---------------------------------------------------------------------
            Cheaking whether the game if finised or not
----------------------------------------------------------------------*/

bool myIBoard::IsFinished() const
{
    for (int i=0;i<3;i++){
        for (int j=0;j<10;j++)
        {
            if(temp[i+1][j+1]!=0 ) {return true;} //cheaking at the top of the 4 rows. if there is something game is over

        }
    }
    return false;
}
/*---------------------------------------------------------------------
            Generate the random number which will be the next block
----------------------------------------------------------------------*/
BlockType_E myIBoard::GetNextBlockType() const
{

    srand (time(NULL));
    switch (rand()%7)
    {
    case 0:

        return I_Block_e;

        break;
    case 1:
        return L_Block_e;
        break;
    case 2:
        return T_Block_e;
        break;
    case 3:
        return J_Block_e;
        break;
    case 4:
        return S_Block_e;
        break;
    case 5:
        return O_Block_e;
        break;
    case 6:
        return Z_Block_e;
        break;
    }

}
/*---------------------------------------------------------------------
            This function will show the total points
----------------------------------------------------------------------*/
unsigned int myIBoard::GetPoints() const
{
    return totalPoints;

}

/*---------------------------------------------------------------------
            Total Removed rows
----------------------------------------------------------------------*/

unsigned int myIBoard::GetRemovedRows() const
{
    return noOfRemovedRow;
    
}
/*---------------------------------------------------------------------
            After the move command updates the current board
----------------------------------------------------------------------*/

void myIBoard::updateGameField(unsigned int PosX, unsigned int PosY, int arr[][22]) //array is the gamefield;
{
    
    
    for (int i =0;i<4;i++){
        for(int j=0;j<4;j++){

            arr[y + i][x + j]-=block[0][i][j]; //vanishing the block from its old position and will be updated new position
                                                // after updating the coordinates in next section
        }
    }
    x=PosX; y=PosY; //updating coordinate

    
    for (int i =0;i<4;i++){
        for(int j=0;j<4;j++){

            arr[y + i][x + j]+=block[0][i][j]; // then add this block with the update coordinates
        }
    }
    


}
/*-----------------------------------------------------------------------------------
Will rotate the current block, for 1 =rotate clockwise, for 2 rotate counter clockwise
-------------------------------------------------------------------------------------*/
int myIBoard::RotateTetrisBlock(int rotateDirection)
{
    if(rotateDirection==1){

        for(int i=0;i<4;i++){
            for (int j=0;j<4;j++)
            {
                rotateTemp[i][j] = block[0][i][j]; //first saving the unrotated block in a temp variable

            }
        }
        for(int i=0;i<4;i++){
            for (int k=0 , j=3;k<4,j>=0;k++,j--){

                block[0][i][k]=rotateTemp[j][i]; //now rotating the temp variable and save it to block [0]
                                                   //block[0] is updated with the rotate block

            }
        }
        if (GetField(x,y)) //after rotation if there is something, block[0] will be updated again with its previous condition
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    block[0][i][j] = rotateTemp[i][j];
                }
            }
            return true;
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                gameField[y + i][x + j] -= rotateTemp[i][j]; // vanishing the old block
                gameField[y + i][x + j] += block[0][i][j]; //update the rotated block
            }
        }


    }

    //for Counter Clock wise  block rotation
    else {

        for(int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                rotateTemp[i][j] = block[0][i][j];  //first saving the unrotated block in a temp variable


            }
        }
        for(int i=0;i<4;i++){
            for (int j=3;j>=0;j--){

                block[0][i][j]=rotateTemp[j][3-i]; //now rotating the temp variable and save it to block [0]
                                                   //block[0] is updated with the rotate block

            }
        }
        if (GetField(x,y))  //after rotation if there is something, block[0] will be updated again with its previous condition
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    block[0][i][j] = rotateTemp[i][j];
                }
            }
            return true;
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                gameField[y + i][x + j] -= rotateTemp[i][j]; // vanishing the old block
                gameField[y + i][x + j] += block[0][i][j]; // Updating with rotated block
            }
        }


    }
    
return 0;
}
/*-----------------------------------------------------------------------------------
        It will update the block[1],which is the next block
-------------------------------------------------------------------------------------*/

int myIBoard::getTheNextBlock(BlockType_E blockType)
{

    switch (blockType) {
    case I_Block_e:
        for (int i=0;i<4;i++){
            for(int j=0;j<4;j++){

                block[1][i][j]=tetrisBlock[I_Block_e][i][j]; //updating the next block from tetrisBlock
            }
        }
        break;
    case L_Block_e:
        for (int i=0;i<4;i++){
            for(int j=0;j<4;j++){

                block[1][i][j]=tetrisBlock[L_Block_e][i][j]; //updating the next block from tetrisBlock
            }
        }

        break;
    case T_Block_e:
        for (int i=0;i<4;i++){
            for(int j=0;j<4;j++){

                block[1][i][j]=tetrisBlock[T_Block_e][i][j]; //updating the next block from tetrisBlock
            }
        }

        break;
    case J_Block_e:
        for (int i=0;i<4;i++){
            for(int j=0;j<4;j++){

                block[1][i][j]=tetrisBlock[J_Block_e][i][j]; //updating the next block from tetrisBlock
            }
        }

        break;
    case S_Block_e:
        for (int i=0;i<4;i++){
            for(int j=0;j<4;j++){

                block[1][i][j]=tetrisBlock[S_Block_e][i][j]; //updating the next block from tetrisBlock
            }
        }

        break;
    case O_Block_e:
        for (int i=0;i<4;i++){
            for(int j=0;j<4;j++){

                block[1][i][j]=tetrisBlock[O_Block_e][i][j];//updating the next block from tetrisBlock
            }
        }

        break;
    case Z_Block_e:
        for (int i=0;i<4;i++){
            for(int j=0;j<4;j++){

                block[1][i][j]=tetrisBlock[Z_Block_e][i][j]; //updating the next block from tetrisBlock
            }
        }

        break;
    }
    return 0;



}
/*-----------------------------------------------------------------------------------
        It will clear the screen
-------------------------------------------------------------------------------------*/
void myIBoard::clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    // Assume Linux
    std::system ("clear");
#endif
}
/*-----------------------------------------------------------------------------------
        this function will say how many coloum is filled with block.
-------------------------------------------------------------------------------------*/

int myIBoard:: filledRowCheck(int b)
{

    for(unsigned int i=0;i<filledRow.size();i++)
    {
        if(b==filledRow[i]) {return filledRow[i];}
    }

    return 0;
}
/*-----------------------------------------------------------------------------------
        This function will update the board with block [0] as current blcok
        & blcok[1] as next block.
-------------------------------------------------------------------------------------*/
void myIBoard::initiallyBlockGenerate()
{

    for(int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {gameField[i+y][j+x]=temp[i+y][j+x]+ block[0][i][j];} // updating the board with with block[0] as current block
    }
    //Sub field initialize with block
    for(int i=0;i<6;i++)
    {
        for (int j=16;j<22;j++)
        {
            if((j>16 && j<21) && (i>0 && i<5)){
                gameField[i][j]=block[1][i-1][j-17];} // updating the board with blcok [1] as next block
        }
    }
}
/*-----------------------------------------------------------------------------------
        This function will removed any filled rows and update the board
-------------------------------------------------------------------------------------*/


int myIBoard::certainGetRemovedRow()
{
    int totalRow=0;
    for (int i =1;i<17;i++){
        for(int j=1;j<12;j++){

            if(gameField[i][j]==0) {isFilled=false;}
            else if(gameField[i][j]==1) {isFilled=true;c++;} //checking every rows
        }

        if(isFilled && c==10) //c==10 means, 10 rows is filled with something
        {
            filledRow.push_back(i);  isFilled=false;c=0;
        }
        c=0;
    }


    if(!filledRow.empty())
    {
        for (int i=15,k=15;i>=4,k>=4;i--,--k){
            for (int j=0;j<12;j++){
                if(k==filledRowCheck(k)) {--k ;if(k==filledRowCheck(k)){--k;if(k==filledRowCheck(k)){--k;}}}
                if(k!=filledRowCheck(k)){

                    gameField[i][j]=temp[k][j];

                }

            }
        }
    }
    totalRow=filledRow.size();
    if(totalRow)
    {
        for (int i=4;i<4+totalRow;i++)
        { for (int j=1;j<10;j++)
            {
                gameField[i][j]=0;

            }
        }

        for(int i=4;i<16;i++)
        {
            for (int j=1;j<12;j++)
            {
                temp[i][j]=gameField[i][j];
            }
        }
    }

    if(totalRow)
    {
        totalPoints+=100*totalRow*totalRow;
        noOfRemovedRow+=totalRow;

    }




    isFilled=false;
    filledRow.clear();
    return 0;

}

