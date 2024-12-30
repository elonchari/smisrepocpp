#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

void removeNullProductions(map<char, set<string>> &grammar)
{
    set<char> nullable;

    bool changed;
    do
    {
        changed = false;
        for (const auto &rule : grammar)
        {
            char variable = rule.first;
            for (const string &production : rule.second)
            {
                if (production.empty() || all_of(production.begin(), production.end(), [&](char c)
                                                 { return nullable.count(c); }))
                {
                    if (nullable.insert(variable).second)
                    {
                        changed = true;
                    }
                }
            }
        }
    } while (changed);

    map<char, set<string>> newGrammar;
    for (const auto &rule : grammar)
    {
        char variable = rule.first;
        for (const string &production : rule.second)
        {
            if (!production.empty())
            {
                newGrammar[variable].insert(production);
                int n = production.size();
                for (int i = 1; i < (1 << n); ++i)
                {
                    string newProduction;
                    for (int j = 0; j < n; ++j)
                    {
                        if (i & (1 << j))
                        {
                            newProduction += production[j];
                        }
                    }
                    if (!newProduction.empty())
                    {
                        newGrammar[variable].insert(newProduction);
                    }
                }
            }
        }
    }
    grammar = newGrammar;
}

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
    cout << "Enter the production rules (e.g., A -> aB | B | ε):" << endl;

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

    removeNullProductions(grammar);

    cout << "\nGrammar after removing null productions:" << endl;
    printGrammar(grammar);

    removeUnitProductions(grammar);

    cout << "\nGrammar after removing unit productions:" << endl;
    printGrammar(grammar);

    return 0;
}
