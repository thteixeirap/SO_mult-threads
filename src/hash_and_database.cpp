#include "hash_and_database.hpp"

unordered_map<string, vector<int>> itensD;
unordered_map<string, vector<int>> classesD;
queue<vector<string>> itensT;

// queue<vector<int>> auxIntersection;
int versicolor = 0;
int virginica = 0;
int setosa = 0;

queue<vector<string>> combinates;
string auxCombinates;
vector<string> allCombinatesLine;

using namespace std;

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
                classesD[key].push_back(linha);
                token = strtok(NULL, ",");
                break;
            }
            key = to_string(coluna) + ", " + string(token);
            itensD[key].push_back(linha);
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
    vector<string> aux;
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
            aux.push_back(key);
            token = strtok(NULL, ",");
            coluna++;
        }

        itensT.push(aux);
        aux.clear();
        linha++;
    }

    file.close();

    return;
}

void printOutHashT()
{
    queue<vector<string>> aux = itensT;
    vector<string> v;
    while (!aux.empty())
    {
        v = aux.front();
        aux.pop();
        for (auto &element : v)
            cout << "[" << element << "]"
                 << " ";
        cout << endl;
        v.clear();
    }
    cout << '\n';
}

void printOutHashCombinate()
{
    queue<vector<string>> aux = combinates;
    vector<string> v;
    while (!aux.empty())
    {
        v = aux.front();
        aux.pop();
        for (auto &element : v)
            cout << "[" << element << "]"
                 << " ";

        v.clear();
        cout << endl;
    }
}

void intersection()
{
    queue<vector<string>> aux = combinates;
    vector<string> v;
    while (!aux.empty())
    {
        v = aux.front();
        aux.pop();
        for (auto &element : v)
            makeIntersection(element);
        v.clear();
    }

    displayResult();
}

void makeIntersection(string s)
{
    char ar[30];
    strcpy(ar, s.c_str());
    char *token = strtok(ar, "][-");
    int cont = 0;
    vector<int> v;
    while (token != NULL)
    {

        string key = (string)token;
        unordered_map<string, vector<int>>::const_iterator find = itensD.find(key);

        token = strtok(NULL, "][-");

        if (find == itensD.end())
        {
            // std::cout << "not found";
        }
        else
        {
            if (cont == 0)
            {
                v = find->second;
                cont++;
            }
            else
            {
                v = intersection(v, find->second);
                cont++;
            }
        }
    }
    if (!v.empty())
        intersectionWithClassHash(v);
}

void intersectionWithClassHash(vector<int> v)
{

    vector<int> versicolorV;
    vector<int> virginicaV;
    vector<int> setosaV;
    int cont = 0;

    for (auto mapIt = begin(classesD); mapIt != end(classesD); ++mapIt)
    {

        switch (cont)
        {
        case 0:
            versicolorV = intersection(v, mapIt->second);
            versicolor += versicolorV.size();
            break;

        case 1:
            virginicaV = intersection(v, mapIt->second);
            virginica += virginicaV.size();
            break;

        case 2:
            setosaV = intersection(v, mapIt->second);
            setosa += setosaV.size();
            break;

        default:
            break;
        }

        cont++;
    }
}

void makeCombinate()
{
    queue<vector<string>> aux = itensT;
    vector<string> v;
    int perm[4] = {0};
    int index = 1;

    for (int i = 0; i < 50; i++)
    // while (!aux.empty())
    {
        v = aux.front();
        aux.pop();
        for (index = 1; index <= 4; index++)
            combinate(v, perm, 0, 4, index);
        v.clear();
        combinates.push(allCombinatesLine);
        allCombinatesLine.clear();
    }
}

void combinate(vector<string> vector, int perm[], int index, int n, int k)
{
    static int count = 0;
    if (count == k)
    {
        auxCombinates.assign("");

        for (int i = 0; i < n; i++)
            if (perm[i])
                auxCombinates.append(vector.at(i)).append("-");

        if (!auxCombinates.empty())
        {
            auxCombinates.erase(auxCombinates.end() - 1);
            allCombinatesLine.push_back(auxCombinates);
        }
    }
    else if ((n - index) >= (k - count))
    {
        perm[index] = 1;
        count++;
        combinate(vector, perm, index + 1, n, k);

        perm[index] = 0;
        count--;
        combinate(vector, perm, index + 1, n, k);
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

vector<int> intersection(vector<int> v1, vector<int> v2)
{
    vector<int> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

    return v3;
}

void displayResult()
{
    cout << endl
         << endl;
    if (versicolor > virginica && versicolor > setosa)
    {
        cout << " Classe Vencedora: Iris-Versicolor " << endl;
    }
    else if (virginica > setosa && virginica > versicolor)
    {
        cout << " Classe Vencedora: Iris-Virginica " << endl;
    }
    else if (setosa > virginica && setosa > versicolor)
    {
        cout << " Classe Vencedora: Iris-Setosa " << endl;
    }
    printf("\n\n");
    printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("      @                    Ranking                        @\n");
    printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
    cout << "\t\tIris-Versicolor: " << versicolor << endl;
    cout << "\t\tIris-Virginica: " << virginica << endl;
    cout << "\t\tIris-Setosa: " << setosa << endl<<endl<<endl;
}
