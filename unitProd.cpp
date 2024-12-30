#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <queue>
using namespace std;

void removeUnitProductions(map<char, set<string>> &grammar)
{
    map<char, set<string>> newGrammar;

    for (const auto &rule : grammar)
    {
        char variable = rule.first;
        queue<char> unitQueue;
        set<char> visited;

        unitQueue.push(variable);
        visited.insert(variable);

        while (!unitQueue.empty())
        {
            char current = unitQueue.front();
            unitQueue.pop();

            for (const string &production : grammar[current])
            {
                if (production.size() == 1 && isupper(production[0]))
                {
                    char target = production[0];
                    if (!visited.count(target))
                    {
                        unitQueue.push(target);
                        visited.insert(target);
                    }
                }
                else
                {
                    newGrammar[variable].insert(production);
                }
            }
        }
    }

    grammar = newGrammar;
}

void printGrammar(const map<char, set<string>> &grammar)
{
    for (const auto &rule : grammar)
    {
        cout << rule.first << " -> ";
        bool first = true;
        for (const string &production : rule.second)
        {
            if (!first)
            {
                cout << " | ";
            }
            first = false;
            cout << (production.empty() ? "ε" : production);
        }
        cout << endl;
    }
}

int main()
{
    int numRules;
    cout << "Enter the number of production rules: ";
    cin >> numRules;
    cin.ignore();

    map<char, set<string>> grammar;
    cout << "Enter the production rules (e.g., A -> aB | B):" << endl;

    for (int i = 0; i < numRules; ++i)
    {
        string line;
        getline(cin, line);

        size_t arrowPos = line.find("->");
        if (arrowPos == string::npos)
        {
            cout << "Invalid production rule format. Skipping: " << line << endl;
            continue;
        }

        char variable = line[0];
        string rhs = line.substr(arrowPos + 2);

        size_t pos = 0;
        while ((pos = rhs.find('|')) != string::npos)
        {
            string production = rhs.substr(0, pos);
            rhs.erase(0, pos + 1);
            grammar[variable].insert(production == "ε" ? "" : production);
        }
        grammar[variable].insert(rhs == "ε" ? "" : rhs);
    }

    cout << "\nOriginal Grammar:" << endl;
    printGrammar(grammar);

    removeUnitProductions(grammar);

    cout << "\nGrammar after removing unit productions:" << endl;
    printGrammar(grammar);

    return 0;
}
