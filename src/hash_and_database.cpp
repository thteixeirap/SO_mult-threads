#include "hash_and_database.hpp"

unordered_map<string, vector<int>> itensD;
unordered_map<string, vector<int>> classesD;
unordered_map<string, vector<int>> cache_intersection;

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
    cout << endl
         << "--------- HASH DOS ITENS --------- " << endl
         << endl;
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

void makeIntersection(string KeyInString)
{
    char keyInChar[30];
    strcpy(keyInChar, KeyInString.c_str());
    char *token = strtok(keyInChar, "-");
    bool firstLoop = true;
    vector<int> v;
    bool block = false;

    string aux = KeyInString;

    unordered_map<string, vector<int>>::const_iterator foundInCache = cacheSearch(KeyInString);
    if (foundInCache == cache_intersection.end())
    {
        while (token != NULL)
        {
            string key = (string)token;
            unordered_map<string, vector<int>>::const_iterator foundHash = itensD.find(key);

            token = strtok(NULL, "-");
            if (!(foundHash == itensD.end()))
            {
                if (firstLoop == true)
                {
                    v = foundHash->second;
                    firstLoop = false;
                }
                else
                    v = intersection(v, foundHash->second);
            }

            /*
             SE NA HASH DE ITENS NAO TIVER A CHAVE, CANCELO O LOOP
             PORQUE JÁ NÃO TEM POSSIBILIDADE DE INTERSEÇÃO
            */
            else
            {
                block = true;
                break;
            }

            /* TESTO O QUE SOBROU DAS COMBINAÇÔES CASO EXISTIR RESTO */
            if (token != NULL)
            {
                aux = tokenizeString(aux);
                unordered_map<string, vector<int>>::const_iterator foundInCache2 = cacheSearch(aux);
                if (!(foundInCache2 == cache_intersection.end()))
                {
                    v = intersection(v, foundInCache2->second);
                    break;
                }
            }
        }

        if (!(v.empty()) && block == false)
        {
            cache_intersection[KeyInString] = v;
            intersectionWithClassHash(v);
        }
    }

    /*
    SE EU JA TIVER A COMBINAÇÃO INTEIRA
    EM CACHE, NÃO ENTRO NO WHILE
    */
    else if (!foundInCache->second.empty())
        intersectionWithClassHash(foundInCache->second);
}

unordered_map<string, vector<int>>::const_iterator cacheSearch(string key)
{
    return cache_intersection.find(key);
}

void intersectionWithClassHash(vector<int> v)
{
    vector<int> vectorIntersection;

    for (auto mapIt = begin(classesD); mapIt != end(classesD); ++mapIt)
    {
        vectorIntersection = intersection(v, mapIt->second);

        if (mapIt->first == "Iris-versicolor")
            versicolor += vectorIntersection.size();
        else if (mapIt->first == "Iris-virginica")
            virginica += vectorIntersection.size();
        else if (mapIt->first == "Iris-setosa")
            setosa += vectorIntersection.size();

        vectorIntersection.clear();
    }
}

void makeCombinate()
{
    queue<vector<string>> aux = itensT;
    vector<string> v;
    int perm[4] = {0};
    int index = 1;

    for (int i = 0; i < 50; i++)
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
    returnsWinningClass();
    printf("\n\n");
    printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("      @                                                   @\n");
    printf("      @                    RANKING                        @\n");
    printf("      @                                                   @\n");
    printf("      @              Iris-Versicolor: %d                 @\n", versicolor);
    printf("      @              Iris-Virginica: %d                  @\n", virginica);
    printf("      @              Iris-Setosa: %d                     @\n", setosa);
    printf("      @                                                   @\n");
    printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
}

void returnsWinningClass()
{

    if (versicolor > virginica && versicolor > setosa)
        cout << endl
             << "\t\tClasse Vencedora: [Iris-Versicolor] ";
    else if (virginica > setosa && virginica > versicolor)
        cout << endl
             << "\t\tClasse Vencedora: [Iris-Virginica] ";
    else
        cout << endl
             << "\t\tClasse Vencedora: [Iris-Setosa] ";
}

string tokenizeString(string s)
{

    s.erase(0, 7);
    return s;
}
