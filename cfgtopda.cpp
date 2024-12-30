#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <sstream>

using namespace std;

class PDA
{
public:
    PDA(const vector<string> &states, const string &startState,
        const string &acceptState, const vector<string> &inputAlphabet,
        const vector<string> &stackAlphabet)
        : states(states), startState(startState), acceptState(acceptState),
          inputAlphabet(inputAlphabet), stackAlphabet(stackAlphabet) {}

    void addTransition(const string &currentState, const string &input,
                       const string &stackTop, const string &nextState,
                       const string &stackPush)
    {
        transitions[{currentState, input, stackTop}] = {nextState, stackPush};
    }

    void displayTransitions() const
    {
        cout << "\nPDA Transitions: \n";
        for (const auto &transition : transitions)
        {
            const auto &key = transition.first;
            const auto &value = transition.second;

            cout << "(" << std::get<0>(key) << ", " << std::get<1>(key) << ", " << std::get<2>(key)
                 << ") -> (" << value.first << ", " << value.second << ")\n";
        }
    }

private:
    vector<string> states;
    string startState;
    string acceptState;
    vector<string> inputAlphabet;
    vector<string> stackAlphabet;
    map<tuple<string, string, string>, pair<string, string>> transitions;
};

PDA convertCFGtoPDA(const vector<string> &nonTerminals, const vector<string> &terminals,
                    const string &startSymbol, const vector<string> &productionRules)
{
    vector<string> states = {"q0", "qAccept"};
    string startState = "q0";
    string acceptState = "qAccept";

    vector<string> inputAlphabet = terminals;
    vector<string> stackAlphabet = nonTerminals;

    PDA pda(states, startState, acceptState, inputAlphabet, stackAlphabet);

    pda.addTransition("q0", "", "$", "q0", startSymbol);

    for (const string &rule : productionRules)
    {
        size_t arrowPos = rule.find("->");
        string leftSide = rule.substr(0, arrowPos);
        string rightSide = rule.substr(arrowPos + 2);

        if (rightSide == "")
        {
            pda.addTransition("q0", "", leftSide, "q0", "");
        }
        else
        {
            pda.addTransition("q0", rightSide.substr(0, 1), leftSide, "q0", rightSide.substr(1));
        }
    }

    pda.addTransition("q0", "", "$", "qAccept", "");

    return pda;
}

int main()
{
    int n;
    cout << "Enter the number of non-terminals: ";
    cin >> n;
    vector<string> nonTerminals(n);
    cout << "Enter the non-terminals: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> nonTerminals[i];
    }

    cout << "\nEnter the number of terminals: ";
    cin >> n;
    vector<string> terminals(n);
    cout << "Enter the terminals: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> terminals[i];
    }

    string startSymbol;
    cout << "\nEnter the start symbol: ";
    cin >> startSymbol;

    int m;
    cout << "\nEnter the number of production rules: ";
    cin >> m;
    vector<string> productionRules(m);
    cout << "Enter the production rules in the format 'A->aB':\n";
    cin.ignore();
    for (int i = 0; i < m; ++i)
    {
        getline(cin, productionRules[i]);
    }

    PDA pda = convertCFGtoPDA(nonTerminals, terminals, startSymbol, productionRules);

    pda.displayTransitions();

    return 0;
}
