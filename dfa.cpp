#include <iostream>
#include <string>
using namespace std;

class DFA
{
private:
    int currentState; 

   
    int transition(int state, char input)
    {
        switch (state)
        {
        case 0:
            return (input == '0') ? 1 : 0;
        case 1:
            return (input == '1') ? 2 : 1;
        case 2:
            return (input == '0') ? 1 : 0;
        default:
            return -1; 
        }
    }

    bool isAcceptingState()
    {
        return currentState == 2;
    }

public:
    DFA() : currentState(0) {} 

    bool processString(const string &input)
    {
        currentState = 0; 
        for (char c : input)
        {
            if (c != '0' && c != '1')
            {
                cout << "Invalid character in input. DFA only supports binary strings." << endl;
                return false;
            }
            currentState = transition(currentState, c);
        }
        return isAcceptingState();
    }
};

int main()
{
    DFA dfa;
    string input;

    cout << "Enter a binary string: ";
    cin >> input;

    if (dfa.processString(input))
    {
        cout << "The string is accepted by the DFA." << endl;
    }
    else
    {
        cout << "The string is rejected by the DFA." << endl;
    }

    return 0;
}
