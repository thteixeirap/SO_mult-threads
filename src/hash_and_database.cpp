#include "hash_and_database.hpp"

unordered_map<string, set<int>> itensD;
unordered_map<string, set<int>> classesD;

unordered_map<int, set<string>> itensT;
vector<string> comparisonResult;



void readFileD(string fileName)
{
    ifstream file;
    string stringLineOutput;
    char *charLineOutput;
    char *token;
    string key;
    int coluna = 1;
    int linha = 1;
    file.open(fileName);

    if (!file)
    {
        printf("file can't be opened \n");
        return;
    }

    while (file)
    {
        if (coluna == 5)
            coluna = 1;
        getline(file, stringLineOutput);
        charLineOutput = const_cast<char *>(stringLineOutput.c_str());
        token = strtok(charLineOutput, ",");
        while (token != NULL)
        {

            if (coluna == 5)
            {
                key = string(token);
                classesD[key].insert(linha);
                token = strtok(NULL, ",");
                break;
            }
                key = to_string(coluna) + ", " + string(token);
                itensD[key].insert(linha);
                token = strtok(NULL, ",");
                coluna++;
            
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
    int coluna = 1;
    int linha = 1;
    set<string> aux;
    file.open(fileName);

    if (!file)
    {
        printf("file can't be opened \n");
        return;
    }

    while (file)
    {
        if (coluna == 5)
            coluna = 1;

        getline(file, stringLineOutput);
        charLineOutput = const_cast<char *>(stringLineOutput.c_str());
        token = strtok(charLineOutput, ",");

        while (token != NULL)
        {
            if (coluna == 5)
            {
                break;
            }

            key = to_string(coluna) + ", " + string(token);
            aux.insert(key);
            token = strtok(NULL, ",");
            coluna++;
        }

        itensT[linha].insert(aux.begin(), aux.end());
        aux.clear();
        linha++;
    }

    file.close();

    return;
}

void printOutHashT()
{
    cout << endl
         << "--------- HASH DOS ITENS --------- " << endl
         << endl;

    for (auto mapIt = begin(itensT); mapIt != end(itensT); ++mapIt)
    {
        for (auto c : mapIt->second)
            cout << '[' + c + ']' << " ";
        cout << endl;
    }
}

void comparingHash(){

    set<string> v;
   
    for (auto mapIt = begin(itensT); mapIt != end(itensT); ++mapIt)
    {
        for (auto c : mapIt->second)
        {
            if (itensD.find(c) != itensD.end())
            {
               comparisonResult.push_back(c);
            }
        }
    }

    ofstream file;
    file.open("comparisonResult.txt");
     for(auto &element : comparisonResult)
    {
        v.insert(element);
        for(auto &value : v)
             file << "(" << value << ")" << " ";
        file << endl;
    }


}

void printOutHashD()
{
    cout << endl
         << "--------- HASH DOS ITENS --------- " << endl
         << endl;

    for (auto mapIt = begin(itensD); mapIt != end(itensD); ++mapIt)
    {
        cout << "  \t[" + mapIt->first + "]"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }

    cout << endl
         << "--------- HASH DAS CLASSES ---------  " << endl
         << endl;

    for (auto mapIt = begin(classesD); mapIt != end(classesD); ++mapIt)
    {
        cout << "[" + mapIt->first + "]"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }
}
