#include "hash_and_database.hpp"

classIntersection iClass;
classCombination c;
unordered_global u;
queue<vector<string>> itensT;

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
                u.classesD[key].push_back(linha);
                token = strtok(NULL, ",");
                break;
            }
            key = to_string(coluna) + ", " + string(token);
            u.itensD[key].push_back(linha);
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

void intersection()
{
    queue<vector<string>> aux = c.combinates;
    vector<string> v;
    while (!aux.empty())
    {
        v = aux.front();
        aux.pop();
        for (auto &element : v)
            makeIntersection(element);
        v.clear();
    }
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
    if (foundInCache == u.cache_intersection.end())
    {
        while (token != NULL)
        {
            string key = (string)token;
            unordered_map<string, vector<int>>::const_iterator foundHash = u.itensD.find(key);
            token = strtok(NULL, "-");
            if (!(foundHash == u.itensD.end()))
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
            /* TESTO O QUE SOBROU DAS COMBINAÇÔES CASO EXISTIR RESTO DE 2 OU MAIS COMBINAÇÕES*/
            // char *auxToken = token;
            // auxToken = strtok(NULL, "-");
            // if (auxToken != NULL)
            // {
            //     aux = tokenizeString(aux);
            //     unordered_map<string, vector<int>>::const_iterator foundInCache2 = cacheSearch(aux);
            //     if (!(foundInCache2 == u.cache_intersection.end()))
            //     {
            //         v = intersection(v, foundInCache2->second);
            //         break;
            //     }
            //     else if (foundInCache2->second == c.nulo)
            //     {
            //         block = true;
            //         break;
            //     }
            // }
        }

        if (!(v.empty()) && block == false)
        {
            u.cache_intersection[KeyInString] = v;
            intersectionWithClassHash(KeyInString, v);
        }
        else
        {
            u.cache_intersection[KeyInString] = c.nulo;
        }
    }

    /*
    SE EU JA TIVER A COMBINAÇÃO INTEIRA
    EM CACHE, NÃO ENTRO NO WHILE
    */
    else if (!(foundInCache->second.empty()) && foundInCache->second != c.nulo)
    {
        // intersectionWithClassHash(KeyInString, foundInCache->second);
        iClass.versicolor += u.intersectionWithClasse[KeyInString][0];
        iClass.virginica += u.intersectionWithClasse[KeyInString][1];
        iClass.setosa += u.intersectionWithClasse[KeyInString][2];
    }
}

unordered_map<string, vector<int>>::const_iterator cacheSearch(string key)
{
    return u.cache_intersection.find(key);
}

void intersectionWithClassHash(string key, vector<int> v)
{
    vector<int> vectorIntersection;
    int intersection_versi = 0, intersection_virg = 0, intersection_set = 0;

    for (auto mapIt = begin(u.classesD); mapIt != end(u.classesD); ++mapIt)
    {
        vectorIntersection = intersection(v, mapIt->second);
        if (mapIt->first == "Iris-versicolor")
        {
            iClass.versicolor += vectorIntersection.size();
            intersection_versi = vectorIntersection.size();
        }
        else if (mapIt->first == "Iris-virginica")
        {
            iClass.virginica += vectorIntersection.size();
            intersection_virg = vectorIntersection.size();
        }
        else if (mapIt->first == "Iris-setosa")
        {
            iClass.setosa += vectorIntersection.size();
            intersection_set = vectorIntersection.size();
        }
        vectorIntersection.clear();
    }
    u.intersectionWithClasse[key] = {intersection_versi, intersection_virg, intersection_set};
}

void *produtor(void *arg)
{
    estrutura_global *vglobal = (estrutura_global *)arg;
    queue<vector<string>> aux = itensT;
    vector<string> v;
    int perm[4] = {0};
    int index = 1;

    for (index = 1; index < 5; index++)
    {
        aux = itensT;
        for (int i = 0; i < 50; i++)
        {
            v = aux.front();
            aux.pop();
            combinate(v, perm, 0, 4, index);
            for (auto &element : c.allCombinatesLine)
            {
                sem_wait(&vglobal->buffer_full);
                pthread_mutex_lock(&vglobal->buffer_mutex);
                vglobal->buffer2[vglobal->currentidx++] = element;
                pthread_mutex_unlock(&vglobal->buffer_mutex);
                sem_post(&vglobal->buffer_empty);
                // cout << "Produz: " << element << endl;
            }
            v.clear();
            c.allCombinatesLine.clear();
            // sleep((int)(rand() % 1));
        }
        c.combinates.push(c.allCombinatesLine);
    }
    vglobal->finishedProd = true;
    pthread_exit(arg);
}

void *consumidor(void *arg)
{
    estrutura_global *vglobal = (estrutura_global *)arg;
    while (!(vglobal->finishedProd == true && vglobal->currentidx == 0))
    {
        sem_wait(&vglobal->buffer_empty);
        pthread_mutex_lock(&vglobal->buffer_mutex);
        string n = vglobal->buffer2[--vglobal->currentidx];
        makeIntersection(n);
        pthread_mutex_unlock(&vglobal->buffer_mutex);
        sem_post(&vglobal->buffer_full);
        // sleep((int)(rand() % 4));
    }

    displayResult();
    pthread_exit(arg);
}

/* Combinação em que usa a política SJF  */

void makeCombinate()
{
    queue<vector<string>> aux = itensT;
    vector<string> v;
    int perm[4] = {0};
    int index = 1;
    for (index = 1; index < 5; index++)
    {
        aux = itensT;
        for (int i = 0; i < 50; i++)
        {
            v = aux.front();
            aux.pop();
            combinate(v, perm, 0, 4, index);
            v.clear();
        }
        c.combinates.push(c.allCombinatesLine);
        c.allCombinatesLine.clear();
    }
}


/* Combinação em que usa a política FIFO  */


// void makeCombinate()
// {
//     queue<vector<string>> aux = itensT;
//     vector<string> v;
//     int perm[4] = {0};
//     int index = 1;

//     for (int i = 0; i < 50; i++)
//     {
//         v = aux.front();
//         aux.pop();
//         for (index = 1; index <= 4; index++)
//             combinate(v, perm, 0, 4, index);
//         v.clear();
//         c.combinates.push(c.allCombinatesLine);
//         c.allCombinatesLine.clear();
//     }
// }

void combinate(vector<string> vector, int perm[], int index, int n, int k)
{
    static int count = 0;
    if (count == k)
    {
        c.auxCombinates.assign("");
        for (int i = 0; i < n; i++)
            if (perm[i])
                c.auxCombinates.append(vector.at(i)).append("-");

        if (!c.auxCombinates.empty())
        {
            c.auxCombinates.erase(c.auxCombinates.end() - 1);
            c.allCombinatesLine.push_back(c.auxCombinates);
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

vector<int> intersection(vector<int> v1, vector<int> v2)
{
    vector<int> v3;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

    return v3;
}

string tokenizeString(string s)
{
    s.erase(0, 7);
    return s;
}

void displayResult()
{
    returnsWinningClass();
    printf("\n\n");
    printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("      @                                                   @\n");
    printf("      @                    RANKING                        @\n");
    printf("      @                                                   @\n");
    printf("      @              Iris-Versicolor: %d                 @\n", iClass.versicolor);
    printf("      @              Iris-Virginica: %d                  @\n", iClass.virginica);
    printf("      @              Iris-Setosa: %d                     @\n", iClass.setosa);
    printf("      @                                                   @\n");
    printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
}

void returnsWinningClass()
{
    if (iClass.versicolor > iClass.virginica && iClass.versicolor > iClass.setosa)
        cout << endl
             << "\t\tClasse Vencedora: [Iris-Versicolor] ";
    else if (iClass.virginica > iClass.setosa && iClass.virginica > iClass.versicolor)
        cout << endl
             << "\t\tClasse Vencedora: [Iris-Virginica] ";
    else
        cout << endl
             << "\t\tClasse Vencedora: [Iris-Setosa] ";
}

void printOutHashCombinate()
{
    queue<vector<string>> aux = c.combinates;
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

void printOutHashD()
{
    cout << endl
         << "--------- HASH DOS ITENS --------- " << endl
         << endl;

    for (auto mapIt = begin(u.itensD); mapIt != end(u.itensD); ++mapIt)
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

    for (auto mapIt = begin(u.classesD); mapIt != end(u.classesD); ++mapIt)
    {
        cout << "[" + mapIt->first + "]"
             << " : ";

        for (auto c : mapIt->second)
            cout << c << " ";

        cout << endl;
    }
}
