#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
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
                if (production == "" || all_of(production.begin(), production.end(), [&](char c)
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
            if (production != "")
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

    map<char, set<string>> grammar;
    cout << "Enter the production rules (e.g., A -> aB | ε):" << endl;
    for (int i = 0; i < numRules; ++i)
    {
        char variable;
        string arrow, productionLine;
        cin >> variable >> arrow;
        getline(cin, productionLine);

        size_t pos = 0;
        while ((pos = productionLine.find('|')) != string::npos)
        {
            string production = productionLine.substr(0, pos);
            productionLine.erase(0, pos + 1);
            grammar[variable].insert(production == "ε" ? "" : production);
        }
        grammar[variable].insert(productionLine == "ε" ? "" : productionLine);
    }

    cout << "\nOriginal Grammar:" << endl;
    printGrammar(grammar);

    removeNullProductions(grammar);

    cout << "\nGrammar after removing null productions:" << endl;
    printGrammar(grammar);

    return 0;
}
