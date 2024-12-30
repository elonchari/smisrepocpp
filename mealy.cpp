#include <iostream>
#include <vector>
#include <string>

class MealyMachine
{
public:
    MealyMachine(int numStates, const std::vector<std::vector<std::string>> &output,
                 const std::vector<std::vector<int>> &transitions)
        : numStates(numStates), outputTable(output), transitionTable(transitions), currentState(0) {}

    void reset()
    {
        currentState = 0;
    }

    void input(char symbol)
    {
        std::cout << "Current State: " << currentState << ", Input: " << symbol << std::endl;

        int symbolIndex = symbol - '0';

        if (symbolIndex >= 0 && symbolIndex < transitionTable[currentState].size())
        {

            std::cout << "Output: " << outputTable[currentState][symbolIndex] << std::endl;
            currentState = transitionTable[currentState][symbolIndex];
        }
        else
        {
            std::cout << "Invalid input symbol!" << std::endl;
        }
    }

private:
    int numStates;
    int currentState;
    std::vector<std::vector<std::string>> outputTable;
    std::vector<std::vector<int>> transitionTable;
};

int main()
{

    int numStates = 3;

    std::vector<std::vector<std::string>> outputs = {
        {"X", "Y"},
        {"Z", "W"},
        {"V", "U"}};

    std::vector<std::vector<int>> transitions = {
        {1, 0},
        {2, 0},
        {2, 1}};

    MealyMachine machine(numStates, outputs, transitions);

    std::string inputSequence;
    std::cout << "Enter the input sequence (only 0's and 1's, type 'end' to stop): ";

    while (true)
    {
        std::cin >> inputSequence;

        if (inputSequence == "end")
        {
            break;
        }

        bool validInput = true;
        for (char c : inputSequence)
        {
            if (c != '0' && c != '1')
            {
                validInput = false;
                break;
            }
        }

        if (!validInput)
        {
            std::cout << "Invalid input! Please enter only 0's and 1's." << std::endl;
        }
        else
        {
            for (char input : inputSequence)
            {
                machine.input(input);
            }
        }

        std::cout << "\nEnter the input sequence (only 0's and 1's, type 'end' to stop): ";
    }

    std::cout << "Program ended." << std::endl;

    return 0;
}
