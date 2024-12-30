#include <iostream>
#include <vector>
#include <string>

class MooreMachine
{
public:
    MooreMachine(int numStates, const std::vector<std::string> &output, const std::vector<std::vector<int>> &transitions)
        : numStates(numStates), stateOutput(output), transitionTable(transitions), currentState(0) {}

    void reset()
    {
        currentState = 0;
    }

    void input(char symbol)
    {
        std::cout << "Current Output: " << stateOutput[currentState] << std::endl;

        int symbolIndex = symbol - '0';

        if (symbolIndex >= 0 && symbolIndex < transitionTable[currentState].size())
        {
            currentState = transitionTable[currentState][symbolIndex];
        }
        else
        {
            std::cout << "Invalid input symbol!" << std::endl;
        }

        std::cout << "New Output: " << stateOutput[currentState] << std::endl;
    }

private:
    int numStates;
    int currentState;
    std::vector<std::string> stateOutput;
    std::vector<std::vector<int>> transitionTable;
};

int main()
{
    int numStates = 3;
    std::vector<std::string> outputs = {"A", "B", "C"};

    std::vector<std::vector<int>> transitions = {
        {1, 0},
        {2, 0},
        {2, 1}};

    MooreMachine machine(numStates, outputs, transitions);

    std::string inputSequence;
    std::cout << "Enter the input sequence (only 0's and 1's): ";
    std::cin >> inputSequence;

    for (char c : inputSequence)
    {
        if (c != '0' && c != '1')
        {
            std::cout << "Invalid input! Please enter only 0's and 1's." << std::endl;
            return 1;
        }
    }

    for (char input : inputSequence)
    {
        machine.input(input);
    }

    return 0;
}
