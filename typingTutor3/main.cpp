#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

using namespace std;

#ifdef __unix__
char myGetch();
#endif

class typingTutor
{
public:
    int playGame();
    void instructions();
    void menu();
};

int typingTutor::playGame()
{
    const int borderWidth = 20; // Adjust the width of the border
    const int borderHeight = 10; // Adjust the height of the border
    const char borderChar = '*'; // Character used for the border
    int score = 0;
    char movingChar; // Initial character to move
    int rounds = 0;
    m:
    while (true) {

        if(rounds == 10)
        {
            cout<<"Congratulations! You Won!"<<endl;
            cout << "Final Score: " << score << endl;
            cout<<endl;
            cout<<"----1.play again----"<<endl;
            cout<<endl;
            o:
            int selec;
            cout<<"Select your choice : ";
            cin>>selec;

            switch(selec)
                {
                    case 1:
                    playGame();
                    break;

                    default:
                    cout<<"please select valid Number!"<<endl;
                    goto o;
                }
            return 0;
        }

        movingChar = 'A' + rand() % 26;
        for (int i = 0; i < borderHeight; i++) {
            system("cls"); // For Windows
            // system("clear"); // For Linux/Mac

            // Print the top border
            for (int j = 0; j < borderWidth; j++) {
                std::cout << borderChar;
            }
            std::cout << std::endl;

            // Print the vertical borders and moving character
            for (int j = 0; j < borderHeight; j++) {
                std::cout << borderChar;

                for (int k = 0; k < borderWidth - 2; k++) {
                    // Print spaces for the horizontal position
                    if (j == i && k == borderWidth / 2 - 1) {
                        std::cout << movingChar;// Print the moving character
                    } else {
                        std::cout << " ";
                    }
                }

                std::cout << borderChar << std::endl;
            }

            // Print the bottom border
            for (int j = 0; j < borderWidth; ++j) {
                std::cout << borderChar;
            }
            std::cout << std::endl;

            // Check if the moving character touches the bottom border
            if (i == borderHeight - 1) {
                cout << "Game Over!" << endl;
                cout << "Final Score: " << score << endl;
                cout<<endl;
                cout<<endl;
                cout<<"----1.play again----"<<endl;
                cout<<endl;
                n:
                int selec;
                cout<<"Select your choice : ";
                cin>>selec;

                switch(selec)
                {
                    case 1:
                    playGame();
                    break;

                    default:
                    cout<<"please select valid Number!"<<endl;
                    goto n;
                }
                return 0;
            }

            // Simple loop for a delay
            clock_t start_time = clock();
            while (clock() < start_time + 200); // Adjust the delay time (100 corresponds to 100 milliseconds)

#ifdef _WIN32
            // Read a key without Enter on Windows
            if (_kbhit()) {
                char userGuess = _getch();
                if (userGuess == movingChar) {
                    score++;
                    rounds++;
                    goto m;
                }
            }
#else
            // Read a character without Enter on Unix-based systems
            if (kbhit()) {
                char userGuess = myGetch();
                if (userGuess == movingChar) {
                    score++;
                    rounds++;
                    goto m;
                }
            }
#endif
        }
    }
}

#ifdef __unix__
char myGetch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}
#endif

void typingTutor::instructions()
{
    cout<<"-------------------------------Instructions---------------------------------"<<endl;
    cout<<"                                                                            "<<endl;
    cout<<"|You need to Type Random Generate Letter Before it Touch the Bottom Border!|"<<endl;
    cout<<"                                                                            "<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"  1.menu  "<<endl;
    cout<<endl;
    m:
    cout<<"Select your choice : ";
    int selec;
    cin>>selec;

    switch(selec)
    {
    case 1:
        menu();
        break;

    default:
        cout<<"please select valid Number!"<<endl;
        goto m;
    }
    cout<<endl;
}

void typingTutor::menu()
{
    cout<<"-----Typing Tutor------"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"  1.Instructions       "<<endl;
    cout<<"  2.Play Game          "<<endl;
    cout<<endl;

    m:
    int selec;
    cout<<"Select your choice : ";
    cin>>selec;

   switch(selec)
   {
   case 1:
    instructions();
    break;

   case 2:
    playGame();
    break;

   default:
    cout<<"please select valid Number!"<<endl;
    goto m;
   }
}

int main() {

    typingTutor obj;
    obj.menu();

}
