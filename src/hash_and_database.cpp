#include "hash_and_database.hpp"

unordered_map<string, set<int>> itensD;
unordered_map<string, set<int>> classesD;

unordered_map<string, set<int>> itensT;
unordered_map<string, set<int>> classesT;

void readFileD(string fileName)
{
    ifstream file;
    string stringLineOutput;
    char *charLineOutput;
    char *token;
    string key;
    int coluna = 0;
    int linha = 0;
    file.open(fileName);

    if (!file)
    {
        printf("file can't be opened \n");
        return;
    }

    while (file)
    {
        if (coluna == 4)
            coluna = 0;
        getline(file, stringLineOutput);
        charLineOutput = const_cast<char *>(stringLineOutput.c_str());
        token = strtok(charLineOutput, ",");
        while (token != NULL)
        {

            if (coluna == 4)
            {
                key = string(token);
                classesD[key].insert(linha);
                token = strtok(NULL, ",");
                break;
            }
            else
            {
                key = to_string(coluna) + ", " + string(token);
                itensD[key].insert(linha);
                token = strtok(NULL, ",");
                coluna++;
            }
        }
        linha++;
    }

    file.close();
    return;
}

void readFileT(string fileName)
{
    ifstream file;
    string stringLineOutput;
    char *charLineOutput;
    char *token;
    string key;
    int coluna = 0;
    int linha = 0;
    file.open(fileName);

    if (!file)
    {
        printf("file can't be opened \n");
        return;
    }

    while (file)
    {
        if (coluna == 4)
            coluna = 0;
        getline(file, stringLineOutput);
        charLineOutput = const_cast<char *>(stringLineOutput.c_str());
        token = strtok(charLineOutput, ",");
        while (token != NULL)
        {

            if (coluna == 4)
            {
                key = string(token);
                classesT[key].insert(linha);
                token = strtok(NULL, ",");
                break;
            }
            else
            {
                key = to_string(coluna) + ", " + string(token);
                itensT[key].insert(linha);
                token = strtok(NULL, ",");
                coluna++;
            }
        }
        linha++;
    }

    file.close();
    return;
}

void printOutHashT()
{
    cout << endl
         << "--------- HASH DOS ITENS --------- " << endl << endl;

    for (auto mapIt = begin(itensT); mapIt != end(itensT); ++mapIt)
    {
        cout << "  \t[" + mapIt->first + "]"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }

    cout << endl
         << "--------- HASH DAS CLASSES ---------  " << endl << endl;

    for (auto mapIt = begin(classesT); mapIt != end(classesT); ++mapIt)
    {
        cout << " [" + mapIt->first + "]"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }
}

void printOutHashD()
{
    cout << endl
         << "--------- HASH DOS ITENS --------- " << endl << endl;

    for (auto mapIt = begin(itensD); mapIt != end(itensD); ++mapIt)
    {
        cout << "  \t[" + mapIt->first + "]"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }

    cout << endl
         << "--------- HASH DAS CLASSES ---------  " << endl << endl;

    for (auto mapIt = begin(classesD); mapIt != end(classesD); ++mapIt)
    {
        cout << "[" + mapIt->first + "]"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }
}