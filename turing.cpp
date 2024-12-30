#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>

using namespace std;

class TuringMachine
{
public:
    TuringMachine(const vector<string> &states, const string &startState,
                  const string &acceptState, const vector<string> &inputAlphabet,
                  const vector<string> &tapeAlphabet, const string &blankSymbol)
        : states(states), startState(startState), acceptState(acceptState),
          inputAlphabet(inputAlphabet), tapeAlphabet(tapeAlphabet), blankSymbol(blankSymbol)
    {
        currentState = startState;
        tape = vector<string>(tapeLength, blankSymbol);
        tapeHead = tapeLength / 2;
    }

    void addTransition(const string &currentState, const string &inputSymbol,
                       const string &nextState, const string &writeSymbol, const string &direction)
    {
        transitions[{currentState, inputSymbol}] = {nextState, writeSymbol, direction};
    }

    void run(const string &input)
    {

        for (size_t i = 0; i < input.size(); ++i)
        {
            tape[tapeLength / 2 + i] = string(1, input[i]);
        }

        while (currentState != acceptState)
        {
            string currentSymbol = tape[tapeHead];
            auto transition = transitions.find({currentState, currentSymbol});

            if (transition == transitions.end())
            {
                cout << "No transition found. Machine halting." << endl;
                break;
            }

            tuple<string, string, string> trans = transition->second;
            string nextState = get<0>(trans);
            string writeSymbol = get<1>(trans);
            string direction = get<2>(trans);

            tape[tapeHead] = writeSymbol;
            currentState = nextState;

            if (direction == "L")
            {
                tapeHead--;
            }
            else if (direction == "R")
            {
                tapeHead++;
            }

            printTape();
        }

        if (currentState == acceptState)
        {
            cout << "\nMachine accepted the input!" << endl;
        }
        else
        {
            cout << "\nMachine halted in non-accepting state." << endl;
        }
    }

private:
    vector<string> states;
    string startState;
    string acceptState;
    vector<string> inputAlphabet;
    vector<string> tapeAlphabet;
    string blankSymbol;
    string currentState;
    vector<string> tape;
    int tapeHead;

    static const int tapeLength = 50;

    map<pair<string, string>, tuple<string, string, string>> transitions;

    void printTape() const
    {
        cout << "Tape: ";
        for (int i = 0; i < tapeLength; ++i)
        {
            if (i == tapeHead)
            {
                cout << "[" << tape[i] << "]";
            }
            else
            {
                cout << tape[i];
            }
        }
        cout << endl;
    }
};

int main()
{
    vector<string> states = {"q0", "q1", "qAccept"};
    string startState = "q0";
    string acceptState = "qAccept";

    vector<string> inputAlphabet = {"0", "1"};
    vector<string> tapeAlphabet = {"0", "1", "B"};
    string blankSymbol = "B";

    TuringMachine tm(states, startState, acceptState, inputAlphabet, tapeAlphabet, blankSymbol);

    tm.addTransition("q0", "0", "q1", "1", "R");
    tm.addTransition("q0", "1", "qAccept", "1", "R");

    tm.addTransition("q1", "1", "qAccept", "1", "R");

    string input;
    cout << "Enter the input string (over alphabet {0, 1}): ";
    cin >> input;

    tm.run(input);

    return 0;
}
