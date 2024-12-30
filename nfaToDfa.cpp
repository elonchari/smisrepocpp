#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
using namespace std;

struct NFA
{
    int states;
    map<int, map<char, set<int>>> transitions;
    set<int> startStates;
    set<int> acceptStates;
};

struct DFA
{
    int states;
    map<int, map<char, int>> transitions;
    int startState;
    set<int> acceptStates;
};

DFA convertNFAtoDFA(const NFA &nfa)
{
    DFA dfa;
    map<set<int>, int> stateMapping;
    queue<set<int>> stateQueue;
    int nextState = 0;

    set<int> startSet = nfa.startStates;
    stateQueue.push(startSet);
    stateMapping[startSet] = nextState++;
    dfa.startState = 0;

    while (!stateQueue.empty())
    {
        set<int> currentSet = stateQueue.front();
        stateQueue.pop();
        int currentState = stateMapping[currentSet];

        for (char symbol = 'a'; symbol <= 'z'; ++symbol)
        {
            set<int> newSet;
            for (int state : currentSet)
            {
                if (nfa.transitions.count(state) && nfa.transitions.at(state).count(symbol))
                {
                    newSet.insert(nfa.transitions.at(state).at(symbol).begin(), nfa.transitions.at(state).at(symbol).end());
                }
            }
            if (!newSet.empty())
            {
                if (!stateMapping.count(newSet))
                {
                    stateMapping[newSet] = nextState++;
                    stateQueue.push(newSet);
                }
                dfa.transitions[currentState][symbol] = stateMapping[newSet];
            }
        }

        for (int state : currentSet)
        {
            if (nfa.acceptStates.count(state))
            {
                dfa.acceptStates.insert(currentState);
                break;
            }
        }
    }

    dfa.states = nextState;
    return dfa;
}

void printDFA(const DFA &dfa)
{
    cout << "Number of states: " << dfa.states << endl;
    cout << "Start state: " << dfa.startState << endl;
    cout << "Accept states: ";
    for (int state : dfa.acceptStates)
    {
        cout << state << " ";
    }
    cout << endl;
    cout << "Transitions: " << endl;
    for (const auto &transition : dfa.transitions)
    {
        for (const auto &entry : transition.second)
        {
            cout << "State " << transition.first << " --" << entry.first << "--> " << entry.second << endl;
        }
    }
}

int main()
{
    NFA nfa;
    cout << "Enter the number of states in the NFA: ";
    cin >> nfa.states;

    int numTransitions;
    cout << "Enter the number of transitions: ";
    cin >> numTransitions;

    cout << "Enter transitions in the format (from_state input_char to_state):" << endl;
    for (int i = 0; i < numTransitions; ++i)
    {
        int from, to;
        char input;
        cin >> from >> input >> to;
        nfa.transitions[from][input].insert(to);
    }

    int numStartStates;
    cout << "Enter the number of start states: ";
    cin >> numStartStates;
    cout << "Enter start states: ";
    for (int i = 0; i < numStartStates; ++i)
    {
        int state;
        cin >> state;
        nfa.startStates.insert(state);
    }

    int numAcceptStates;
    cout << "Enter the number of accept states: ";
    cin >> numAcceptStates;
    cout << "Enter accept states: ";
    for (int i = 0; i < numAcceptStates; ++i)
    {
        int state;
        cin >> state;
        nfa.acceptStates.insert(state);
    }

    DFA dfa = convertNFAtoDFA(nfa);
    cout << "\nDFA generated from the NFA:\n";
    printDFA(dfa);

    return 0;
}
