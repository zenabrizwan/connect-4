#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int** modifyBoard(int** board,int yIndex,std::string playerMode);
bool evaluateBoard(int** board,std::string& winner,std::string& how);
int countHorizontally(int** board,int xIndex,int yIndex,int val);
int countVertically(int** board,int xIndex,int yIndex,int val);
int countDiagonally45(int** board,int xIndex,int yIndex,int val);
int countDiagonally_45(int** board,int xIndex,int yIndex,int val);
int countHorizontallyBef(int** board,int xIndex,int yIndex,int val);
int countHorizontallyAft(int** board,int xIndex,int yIndex,int val);
int countVerticallyBef(int** board,int xIndex,int yIndex,int val);
int countVerticallyAft(int** board,int xIndex,int yIndex,int val);
int countDiagonally_45Bef(int** board,int xIndex,int yIndex,int val);
int countDiagonally_45Aft(int** board,int xIndex,int yIndex,int val);
int countDiagonally45Bef(int** board,int xIndex,int yIndex,int val);
int countDiagonally45Aft(int** board,int xIndex,int yIndex,int val);
int heurstic(int** board);
void StartNewGame();
int check_input();
void Game(int** board);
void showBoard(int** board);
bool validModification(int** board,int y);
int** InitiateBoard();
void SaveGame(int** board);
int** LoadGame();

int main()
{
    //interface
    cout<<"Welcome To Connect_N Game"<<endl;
	StartNewGame();
    return 0;
}

//i will assume that player's game will be -1 in his chosen position and 1 for our algorithm yIndex is column number
int** modifyBoard(int** board,int yIndex,std::string playerMode)
{
    int** result = new int* [6];
    for(int i=0;i<6;i++)
    {
        result[i] = new int[7];
    }
    //board is arranged top down from row 0 to row 5
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            result[i][j] = board[i][j];
        }
    }
    if(playerMode == "us")
    {
        if(yIndex >= 0&&yIndex < 7)
        {
            for(int i=5;i>=0;i--)
            {
                if(result[i][yIndex] == 0)
                {
                    result[i][yIndex] = 1;
                    return result;
                }
            }  
        }
        
    }else if(playerMode == "them")
    {
        if(yIndex >= 0&&yIndex < 7)
        {
            for(int i=5;i>=0;i--)
            {
                if(result[i][yIndex] == 0)
                {
                    result[i][yIndex] = -1;
                    return result;
                }
            }  
        }
    }
}
//it will evaluate board and tell us who wins and how he won method 
bool evaluateBoard(int** board,string& winner,string& how)
{
    winner = "";
    how = "";
    bool flag = false;
    for(int i=0;i<6;i++)
    {
        if(flag)
        {
            break;
        }
        for(int j=0;j<7;j++)
        {
            if(board[i][j] == 1)
            {
                if(countHorizontally(board,i,j,1) >= 4)
                {
                    how += " Horizontally";   
                }
                if(countVertically(board,i,j,1) >= 4)
                {
                    how +=" Vertically";
                }
                if(countDiagonally45(board,i,j,1) >= 4)
                {
                    how +=" diagonally+45";
                }
                if(countDiagonally_45(board,i,j,1) >= 4)
                {
                    how +=" diagonally-45";
                }
                if(how != "")
                {
                    winner = "computer";
                    flag = true;
                    break;
                }
            }
            else if(board[i][j] == -1)
            {
                if(countHorizontally(board,i,j,-1) >= 4)
                {
                    how += " Horizontally";   
                }
                if(countVertically(board,i,j,-1) >= 4)
                {
                    how +=" Vertically";
                }
                if(countDiagonally45(board,i,j,-1) >= 4)
                {
                    how +=" diagonally+45";
                }
                if(countDiagonally_45(board,i,j,-1) >= 4)
                {
                    how +=" diagonally-45";
                }
                if(how != "")
                {
                    winner = "user";
                    flag = true;
                    break;
                }
            }        
        }
    }
    if(winner == "")
    {
        return false;
    }else
    {
        return true;
    }
}

int countHorizontally(int** board,int xIndex,int yIndex,int val)
{
    return -1 + countHorizontallyBef(board,xIndex,yIndex,val) + countHorizontallyAft(board,xIndex,yIndex,val);
}

int countHorizontallyBef(int** board,int xIndex,int yIndex,int val)
{
    if(yIndex < 0 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countHorizontallyBef(board,xIndex,yIndex-1,val);
}

int countHorizontallyAft(int** board,int xIndex,int yIndex,int val)
{
    if(yIndex > 6 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countHorizontallyAft(board,xIndex,yIndex+1,val);
}

int countVertically(int** board,int xIndex,int yIndex,int val)
{
    return -1 + countVerticallyBef(board,xIndex,yIndex,val) + countVerticallyAft(board,xIndex,yIndex,val);
}

int countVerticallyBef(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex < 0 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countVerticallyBef(board,xIndex-1,yIndex,val);
}

int countVerticallyAft(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex > 5 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countVerticallyAft(board,xIndex+1,yIndex,val);
}

int countDiagonally45(int** board,int xIndex,int yIndex,int val)
{
    return -1 + countDiagonally45Bef(board,xIndex,yIndex,val) + countDiagonally45Aft(board,xIndex,yIndex,val);
}

int countDiagonally45Bef(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex < 0 || yIndex < 0 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countDiagonally45Bef(board,xIndex-1,yIndex+1,val);
}

int countDiagonally45Aft(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex > 5 || yIndex > 6 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countDiagonally45Aft(board,xIndex+1,yIndex-1,val);
}

int countDiagonally_45(int** board,int xIndex,int yIndex,int val)
{
    return -1 + countDiagonally_45Bef(board,xIndex,yIndex,val) + countDiagonally_45Aft(board,xIndex,yIndex,val);
}

int countDiagonally_45Bef(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex < 0 || yIndex < 0 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countDiagonally_45Bef(board,xIndex-1,yIndex-1,val);
}

int countDiagonally_45Aft(int** board,int xIndex,int yIndex,int val)
{
    if(xIndex > 5 || yIndex > 6 || board[xIndex][yIndex]!=val)
    {
        return 0;
    }
    return 1 + countDiagonally_45Aft(board,xIndex+1,yIndex+1,val);
}

int heurstic(int** board)
{
    int score = 0;
    int horz , vert , dia45 , dia_45;
    for(int i = 5;i >= 0;i--)
    {
        for(int j = 0;j < 7;j++)
        {
            horz = 0 , vert = 0 , dia45 = 0 , dia_45 = 0;
            if(board[i][j] == 1)
            {
                horz = countHorizontally(board,i,j,1);
                vert = countVertically(board,i,j,1);
                dia45 = countDiagonally45(board,i,j,1);
                dia_45 = countDiagonally_45(board,i,j,1);
                if(horz == 2)
                {
                    score += 25;
                }else if(horz == 3)
                {
                    score += 50;
                }else if(horz == 4)
                {
                    score += 10000;
                }
                if(vert == 2)
                {
                    score += 25;
                }else if(vert == 3)
                {
                    score += 50;
                }else if(vert == 4)
                {
                    score += 10000;
                }
                if(dia_45 == 2)
                {
                    score += 25;
                }else if(dia_45 == 3)
                {
                    score += 50;
                }else if(dia_45 == 4)
                {
                    score += 10000;
                }
                if(dia45 == 2)
                {
                    score += 25;
                }else if(dia45 == 3)
                {
                    score += 50;
                }else if(dia45 == 4)
                {
                    score += 10000;
                }

            }else if(board[i][j] == -1)
            {
                horz = countHorizontally(board,i,j,-1);
                vert = countVertically(board,i,j,-1);
                dia45 = countDiagonally45(board,i,j,-1);
                dia_45 = countDiagonally_45(board,i,j,-1);
                if(horz == 2)
                {
                    score -= 25;
                }else if(horz == 3)
                {
                    score -= 50;
                }else if(horz == 4)
                {
                    score -= 1000000;
                }
                if(vert == 2)
                {
                    score -= 25;
                }else if(vert == 3)
                {
                    score -= 50;
                }else if(vert == 4)
                {
                    score -= 1000000;
                }
                if(dia_45 == 2)
                {
                    score -= 25;
                }else if(dia_45 == 3)
                {
                    score -= 50;
                }else if(dia_45 == 4)
                {
                    score -= 1000000;
                }
                if(dia45 == 2)
                {
                    score -= 25;
                }else if(dia45 == 3)
                {
                    score -= 50;
                }else if(dia45 == 4)
                {
                    score -= 1000000;
                }
            }
        }
    }
    return score;
}

int check_input()
{
	int inp;
	cin>>inp;
	while (true)
	{
		if(cin.fail())
		{
			cout << "Wrong value,Enter a number between 1 and 7, Try again" << endl << "Your move : ";
			cin.clear();
			cin.ignore(256,'\n');
			cin >> inp;
		}
		else if(inp == -1)
		{
			return inp;
		}
		else if (inp<1 || inp>7)
		{
			cout << "Wrong value,Enter a number between 1 and 7, Try again" << std::endl << "Your move : ";
			cin.clear();
			cin.ignore(256,'\n');
			cin >> inp;
		}
		else
		{
			break;
		}
	}
	return inp-1;

}

void StartNewGame()
{
	while (true)
	{
		cout<<"press N to start new game or L to load last game or Q to quit"<<std::endl;
		string np;
		cin>>np;
		if (np=="N" || np=="n")
		{
			int** board = InitiateBoard();
			while (true)
			{
				cout<<"Would you like to start first ? y/n"<<std::endl;
				string yn;
				cin>>yn;
				if (yn=="Y"|| yn=="y")
				{
					cout<<"Your move : ";
					int y1 = check_input();
					board=modifyBoard(board,y1,"them");
					showBoard(board);
					break;
				}
				else if (yn=="N" || yn=="n")
				{
					break;
				}
				else
				{
					 cout<<"Wrong input, Try again"<< endl;
				}
			}
			//Start game here
			Game(board);
		}
		else if (np=="L" || np=="l")
		{
			cout<<"Loading" << std::endl;
			int** lastboard=LoadGame();
			showBoard(lastboard);
			cout<<"Your move : ";
			int y1 = check_input();
			lastboard=modifyBoard(lastboard,y1,"them");
			showBoard(lastboard);
			Game(lastboard);
		}
		else if (np=="Q" || np=="q")
		{
			cout<<"Thank you for Playing" << std::endl;
			break;
		}
		else
		{
			cout<<"Wrong value, Try again" << std::endl;
		}
	}
}

void Game(int** board)
{
	string winner,method;
    bool flag = false;
	while (true)
	{
		int inp;
		cin>>inp;
		int x1 = inp;
		board=modifyBoard(board,x1,"us");
		showBoard(board);
		// Check Winning state
        if(evaluateBoard(board,winner,method))
        {
            flag = true; 
            break;
        } 
		cout<<"Your move : ";
		int y1 = check_input();
		if(y1==-1)
		{
			SaveGame(board);
			cout<<"Game has been saved"<<std::endl;
			break;
		}
		board=modifyBoard(board,y1,"them");
		showBoard(board);
		// Check Winning State
        if(evaluateBoard(board,winner,method))
        {
            flag = true; 
            break;
        } 
	}
    if(flag)
    {
        cout<<"Winner is "+winner+" by connecting 4 "+method<<endl;
    }
}


void showBoard(int** board)
{
	for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(board[i][j] == -1)
            {
                 cout<<"o ";
            }
            else if(board[i][j] == 1)
            {
                cout<<"x ";   
            }
            else
            {
                cout<<"- ";
            }
        }
        cout<<endl;
    }
}

bool validModification(int** board,int y)
{
    for(int i=5;i>=0;i--)
    {
        if(board[i][y] == 0)
        {
            return true;
        }
    }  
    return false;
}

int** InitiateBoard()
{
	//board is arranged top down from row 0 to row 5
    int** connectBoard = new int* [6];
    for(int i=0;i<6;i++)
	{
		connectBoard[i] = new int[7];
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			connectBoard[i][j]=0;
		}
	}

	return connectBoard;
}

void SaveGame(int** board)
{
	std::ofstream outfile;
	outfile.open("LastGame.txt");
	for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
		{
			outfile << board[i][j] << std::endl;
		}
	}
	outfile.close();
}

int** LoadGame()
{
	int** board=InitiateBoard();
	std::ifstream infile;
	infile.open("LastGame.txt");
	for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
		{
			infile >> board[i][j];
		}
	}
	infile.close();
	return board;
}
