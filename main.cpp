#include <iostream>
#include <vector>
#include <ctime>
using std::cout, std::cin, std::endl, std::string;

namespace glb {

    bool running = true;  //This is to ensure the termination from the replay function
    int choice = 0;
    std::vector<int> exnum = {};
    string spaces[] = {" ", " ", " ", " ", " ", " ", " ", " ", " "};
}

void intro();
void drawboard();
bool posExists(int pos);
bool update(int user_pos);
void winCheck();
void tieCheck();
void cguess();
void replay();



int main()
{
    intro();
    do
    {
        int position;
        bool exitFlag = false;
        srand(time(0));
        
        // Welcome for the game and further showing the empty 
        // board and in the further repetetion display the 
        // updated board
        drawboard();

        cout << "Enter your position of choice or 0 -> Exit: ";
        // Loop for validation of the input
        while(cin >> position && (position < 0 || position > 9))
        {
            cout << "Enter a valid position please: ";
            if (position == 0)
            {
                exitFlag = true;
                break;
            }
        }
        if(exitFlag == true || position == 0){
            cout << "See you later, have a nice day" << endl;
            break;
        }
        
        // Updating and verifying
        while(!update(position))
        {
            cout << "Please enter a unoccupied position: ";
            cin >> position;
        }
        // Now we'll check for a win and tie and also check the running status 
        // after every win and tie check

        winCheck();
        if(!glb::running)
        {
            cout << "See you again, have nice day!" << endl;
            break;
        }
        tieCheck();
        if(!glb::running)
        {
            cout << "See you again, have nice day!" << endl;
            break;
        }
        // Now it's time for the computer to make a guess
        cguess();
        // Now we'll check for a win and tie and also check the running status 
        // after every win and tie check

        winCheck();
        if(!glb::running)
        {
            cout << "See you again, have nice day!" << endl;
            break;
        }
        tieCheck();
        if(!glb::running)
        {
            cout << "See you again, have nice day!" << endl;
            break;
        }
    } while (glb::running);
    
    return 0;
}


void cguess()
{
    int cpos;
    do
    {
        // Keeps on guessing a untill a unoccupied position is guessed
        cpos = rand() % 9;
    } while (posExists(cpos));
    // Updating the occupied positions list
    glb::exnum.push_back(cpos);
    // Updating the space in the board
    if (glb::choice == 1)
    {
        glb::spaces[cpos] = "O";
    }
    else 
    {
        glb::spaces[cpos] = "X";
    }

}

// This checks if anyone has won and return the control to the function replay
void winCheck()
{
    if(
        // All the possible combinations to win
        (glb::spaces[0] == "X" && glb::spaces[1] == "X" && glb::spaces[2] == "X") || 
        (glb::spaces[0] == "X" && glb::spaces[3] == "X" && glb::spaces[6] == "X") ||
        (glb::spaces[1] == "X" && glb::spaces[4] == "X" && glb::spaces[7] == "X") ||
        (glb::spaces[2] == "X" && glb::spaces[5] == "X" && glb::spaces[8] == "X") ||
        (glb::spaces[6] == "X" && glb::spaces[7] == "X" && glb::spaces[8] == "X") ||
        (glb::spaces[0] == "X" && glb::spaces[4] == "X" && glb::spaces[8] == "X") ||
        (glb::spaces[2] == "X" && glb::spaces[4] == "X" && glb::spaces[6] == "X") ||
        (glb::spaces[3] == "X" && glb::spaces[4] == "X" && glb::spaces[5] == "X")
    )
    {
        if(glb::choice == 1)
        {
            // Board is drawn for the last time for user satisfaction
            drawboard();
            cout << "Your win was a coincidence :<" << endl;
            replay();
        }
        else
        {
            drawboard();
            cout << "OlaOla, did you looose :>" << endl;
            replay();
        }
    }
    else if(
        // All the possible combinations to win
        (glb::spaces[0] == "O" && glb::spaces[1] == "O" && glb::spaces[2] == "O") || 
        (glb::spaces[0] == "O" && glb::spaces[3] == "O" && glb::spaces[6] == "O") ||
        (glb::spaces[1] == "O" && glb::spaces[4] == "O" && glb::spaces[7] == "O") ||
        (glb::spaces[2] == "O" && glb::spaces[5] == "O" && glb::spaces[8] == "O") ||
        (glb::spaces[6] == "O" && glb::spaces[7] == "O" && glb::spaces[8] == "O") ||
        (glb::spaces[0] == "O" && glb::spaces[4] == "O" && glb::spaces[8] == "O") ||
        (glb::spaces[2] == "O" && glb::spaces[4] == "O" && glb::spaces[6] == "O") ||
        (glb::spaces[3] == "O" && glb::spaces[4] == "O" && glb::spaces[5] == "O")
    )
    {
        if(glb::choice == 2)
        {
            drawboard();
            cout << "Ahh shit! I lost for the first time, you cheater :<" << endl;
            replay();
        }
        else
        {
            drawboard();
            cout << "HeeHeeHaawHaaw, you are a loooser! :>" << endl;
            replay();
        }
    }
}

// Check for a tie
void tieCheck()
{
    if(glb::exnum.size() == 9)
    {
        cout << "We both are having a bad day :<" << endl;
        replay();
    }
}

void drawboard()
{
    cout << "***************************" << endl;
    cout << "  "<< glb::spaces[0] <<"  |  "<< glb::spaces[1] <<"  |  "<< glb::spaces[2] <<"  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "  "<< glb::spaces[3] <<"  |  "<< glb::spaces[4] <<"  |  "<< glb::spaces[5] <<"  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "  "<< glb::spaces[6] <<"  |  "<< glb::spaces[7] <<"  |  "<< glb::spaces[8] <<"  " << endl;
    cout << "     |     |     " << endl;
    cout << "***************************" << endl;
    return;
}

void replay(){
    int response;
    cout << "Hey wanna play again ? It'll be fun.." << endl;
    cout << "Choose 1 -> Yes, 2 -> No: ";
    cin >>  response;
    if (response == 1)
    {
        for (int i = 0; i < 9; i++)
        {
            glb::spaces[i] = " ";
        }
        glb::choice = 0;
        glb::exnum.clear();
        intro();
        glb::running = true;
        return;
    }
    glb::running = false;
    return;
}
// This function sets the choice of the user
void intro()
{
    cout << "***************************************************" << endl;
    cout << "                    TIC TAC TOE                    " << endl;
    cout << "***************************************************" << endl;
    cout << "   Welcome these are the indices of your guesses   " << endl;
    cout << "                  Do Remmember! :>                 " << endl;
    cout << "                   1  |  2  |  3                   " << endl;
    cout << "                 _____|_____|_____                 " << endl;
    cout << "                   4  |  5  |  6                   " << endl;
    cout << "                 _____|_____|_____                 " << endl;
    cout << "                   7  |  8  |  9                   " << endl;
    cout << "                      |     |                      " << endl;
    cout << "Choose 1 -> X, 2 -> O: ";
    // Loop for validate input
    while(cin >> glb::choice && (glb::choice != 1 && glb::choice != 2))
    {
        cout << "Invalid choice. Please enter 1 or 2: ";
    }
    return;
}

// This checks if a position is already taken or not
bool posExists(int pos)
{
    for (int occupied : glb::exnum) {
        if (pos == occupied) {
            return true;  
        }
    }
    return false;  
}

bool update(int user_pos)
{
    user_pos--;
    if (posExists(user_pos))
    {
        return false;
    }
    
    glb::exnum.push_back(user_pos);
    if (glb::choice == 1)
    {
        glb::spaces[user_pos] = "X";
    }
    else
    {
        glb::spaces[user_pos] = "O";
    }
    return true;
}