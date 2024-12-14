#include <iostream>
#include <vector>
#include <ctime>
using std::cout, std::cin, std::string, std:: endl;

namespace pos {
    int choice = 0;
    std::vector<int> excludes = {};
    string elements[] = {" "," "," "," "," "," "," "," "," "};  
}
bool isExcluded(int num);
int check();
void intro();
void drawboard();
int computerguess();
int replay();
int update(int position);


int main()
{
    srand(time(0));
    intro();
    do {
        bool exitFlag = false;
        int position;
        drawboard();
        cout << "Enter your position of choice or 0 -> Exit: ";

        while(cin >> position && (position < 0 || position > 9))
        {
            cout << "Enter a valid position please :<" << endl;
            cin >> position;
            if (position == 0)
            {
                exitFlag = true;
                break;
            }
        }
        if(exitFlag == true || position == 0)
            cout << "See you later, have a nice day" << endl;
            break;
        
        if (!update(--position))
        {
            cout << "Please enter a position still not taken" << endl;
            continue;
        }
        

        if(!check())
        {
            cout << "See you later, have a nice day" << endl;
            break;
        }
    } while (true);

    return 0;
}

int update(int position)
{
    if (isExcluded(position))
    {
        return 0;
    }
    
    pos::excludes.push_back(position);
    if (pos::choice == 1)
    {
        pos::elements[position] = "X";
    }
    else
    {
        pos::elements[position] = "O";
    }
    if(!computerguess())
    {
        return 1;
    }
    return 1;
}

int check()
{
    if(
        (pos::elements[0] == "X" && pos::elements[1] == "X" && pos::elements[2] == "X") || 
        (pos::elements[0] == "X" && pos::elements[3] == "X" && pos::elements[6] == "X") ||
        (pos::elements[1] == "X" && pos::elements[4] == "X" && pos::elements[7] == "X") ||
        (pos::elements[2] == "X" && pos::elements[5] == "X" && pos::elements[8] == "X") ||
        (pos::elements[5] == "X" && pos::elements[7] == "X" && pos::elements[8] == "X") ||
        (pos::elements[0] == "X" && pos::elements[4] == "X" && pos::elements[8] == "X") ||
        (pos::elements[2] == "X" && pos::elements[4] == "X" && pos::elements[5] == "X")
    )
    {
        if(pos::choice == 1)
        {
            drawboard();
            cout << "Your win was a coincidence :<" << endl;
            return replay();
        }
        else
        {
            drawboard();
            cout << "OlaOla, did you looose :>" << endl;
            return replay();
        }
    }
    else if(
        (pos::elements[0] == "O" && pos::elements[1] == "O" && pos::elements[2] == "O") || 
        (pos::elements[0] == "O" && pos::elements[3] == "O" && pos::elements[6] == "O") ||
        (pos::elements[1] == "O" && pos::elements[4] == "O" && pos::elements[7] == "O") ||
        (pos::elements[2] == "O" && pos::elements[5] == "O" && pos::elements[8] == "O") ||
        (pos::elements[5] == "O" && pos::elements[7] == "O" && pos::elements[8] == "O") ||
        (pos::elements[0] == "O" && pos::elements[4] == "O" && pos::elements[8] == "O") ||
        (pos::elements[2] == "O" && pos::elements[4] == "O" && pos::elements[5] == "O")
    )
    {
        if(pos::choice == 2)
        {
            drawboard();
            cout << "Ahh shit! I lost for the first time, you cheater :<" << endl;
            return replay();
        }
        else
        {
            drawboard();
            cout << "HeeHeeHaawHaaw, you are a loooser! :>" << endl;
            return replay();
        }
    }

    if(pos::excludes.size() == 9)
    {
        drawboard();
        cout << "We both are having a bad day :<" << endl;
        return replay();
    }
    
    return 1;
}

bool isExcluded(int num) {
    for (int excluded : pos::excludes) {
        if (num == excluded) {
            return true;  
        }
    }
    return false;  
}


int replay()
{
    int response;
    cout << "Hey wanna play again ? It'll be fun.." << endl;
    cout << "Enter 1 -> Yes, 2 -> No: ";
    cin >>  response;
    if (response == 1)
    {
        for (int i = 0; i < 9; i++)
        {
            pos::elements[i] = " ";
        }
        pos::choice = 0;
        pos::excludes.clear();
        intro();
        return 1;
    }
    return 0;
       
}



void intro()
{
    cout << "***************************" << endl;
    cout << "        TIC TAC TOE        " << endl;
    cout << "***************************" << endl;
    cout << "Welcome these are the indices of your guesses" << endl;
    cout << "Do Remmember! :>" << endl;
    cout << "  1  |  2  |  3  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "  4  |  5  |  6  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "  7  |  8  |  9  " << endl;
    cout << "     |     |     " << endl;
    cout << "Enter 1 -> X, 2 -> O: ";
    while(cin >> pos::choice && (pos::choice != 1 && pos::choice != 2))
    {
        cout << "Invalid choice. Please enter 1 or 2: ";
    }
    return;
}

void drawboard()
{
    cout << "***************************" << endl;
    cout << "  "<< pos::elements[0] <<"  |  "<< pos::elements[1] <<"  |  "<< pos::elements[2] <<"  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "  "<< pos::elements[3] <<"  |  "<< pos::elements[4] <<"  |  "<< pos::elements[5] <<"  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "  "<< pos::elements[6] <<"  |  "<< pos::elements[7] <<"  |  "<< pos::elements[8] <<"  " << endl;
    cout << "     |     |     " << endl;
    cout << "***************************" << endl;
    return;
}

int computerguess()
{
    int position;
    if (pos::excludes.size() == 9){
        return 0;
    }
    do {
        position = rand() % 9;  
    } while (isExcluded(position));
    pos::excludes.push_back(position);
    if (pos::choice == 1)
    {
        pos::elements[position] = "O";
    }
    else 
    {
        pos::elements[position] = "X";
    }
    return 1;
}
