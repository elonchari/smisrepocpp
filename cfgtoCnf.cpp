#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

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
            cout << (production.empty() ? "\u03B5" : production);
        }
        cout << endl;
    }
}

void removeNullProductions(map<char, set<string>> &grammar)
{
    set<char> nullable;
    bool changed;

    do
    {
        changed = false;
        for (const auto &rule : grammar)
        {
            for (const string &production : rule.second)
            {
                if (production.empty() || all_of(production.begin(), production.end(), [&](char c)
                                                 { return nullable.count(c); }))
                {
                    if (nullable.insert(rule.first).second)
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
        for (const string &production : rule.second)
        {
            int n = production.size();
            for (int i = 0; i < (1 << n); ++i)
            {
                string newProduction;
                for (int j = 0; j < n; ++j)
                {
                    if (i & (1 << j))
                    {
                        newProduction += production[j];
                    }
                }
                if (!newProduction.empty() || !nullable.count(rule.first))
                {
                    newGrammar[rule.first].insert(newProduction);
                }
            }
        }
    }

    grammar = newGrammar;
}

void removeUnitProductions(map<char, set<string>> &grammar)
{
    for (auto &rule : grammar)
    {
        set<string> newProductions;
        set<char> visited;
        vector<char> toProcess = {rule.first};

        while (!toProcess.empty())
        {
            char current = toProcess.back();
            toProcess.pop_back();

            if (visited.count(current))
            {
                continue;
            }
            visited.insert(current);

            for (const string &production : grammar[current])
            {
                if (production.size() == 1 && isupper(production[0]))
                {
                    toProcess.push_back(production[0]);
                }
                else
                {
                    newProductions.insert(production);
                }
            }
        }

        rule.second = newProductions;
    }
}

void convertToCNF(map<char, set<string>> &grammar)
{
    map<char, set<string>> newGrammar;
    char newVariable = 'Z';

    for (auto &rule : grammar)
    {
        for (const string &production : rule.second)
        {
            if (production.size() <= 2)
            {
                newGrammar[rule.first].insert(production);
            }
            else
            {
                string currentProduction = production;
                while (currentProduction.size() > 2)
                {
                    string newRight = currentProduction.substr(currentProduction.size() - 2);
                    currentProduction.pop_back();
                    newGrammar[newVariable].insert(newRight);
                    currentProduction += newVariable;
                    --newVariable;
                }
                newGrammar[rule.first].insert(currentProduction);
            }
        }
    }

    grammar = newGrammar;
}

int main()
{
    int numRules;
    cout << "Enter the number of production rules: ";
    cin >> numRules;
    cin.ignore();

    map<char, set<string>> grammar;
    cout << "Enter the production rules (format: A -> aB | b):\n";
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
            grammar[variable].insert(production == "\u03B5" ? "" : production);
        }
        grammar[variable].insert(rhs == "\u03B5" ? "" : rhs);
    }

    cout << "\nOriginal Grammar:" << endl;
    printGrammar(grammar);

    removeNullProductions(grammar);
    cout << "\nAfter removing null productions:" << endl;
    printGrammar(grammar);

    removeUnitProductions(grammar);
    cout << "\nAfter removing unit productions:" << endl;
    printGrammar(grammar);

    convertToCNF(grammar);
    cout << "\nGrammar in CNF:" << endl;
    printGrammar(grammar);

    return 0;
}
