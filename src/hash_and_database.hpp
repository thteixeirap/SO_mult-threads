#ifndef HASH_AND_DATABASE_HPP
#define HASH_AND_DATABASE_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <string.h>
#include <fstream>
#include <chrono>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUMCONS 1
#define NUMPROD 1
#define BUFFERSIZE 1000

using namespace std;
using namespace chrono;
typedef struct classIntersection
{
    int versicolor = 0;
    int virginica = 0;
    int setosa = 0;
} classIntersection;

typedef struct classCombination
{
    queue<vector<string>> combinates;
    string auxCombinates;
    vector<string> allCombinatesLine;
    vector<int> nulo = {-1};
} classCombination;

typedef struct unordered_global
{
    unordered_map<string, vector<int>> itensD;
    unordered_map<string, vector<int>> classesD;
    unordered_map<string, vector<int>> cache_intersection;
    unordered_map<string, vector<int>> intersectionWithClasse;

} unordered_global;

typedef struct
{
    int buffer[BUFFERSIZE];
    string buffer2[BUFFERSIZE];
    int currentidx;
    bool finishedProd = false;
    pthread_mutex_t buffer_mutex;
    sem_t buffer_full;
    sem_t buffer_empty;
} estrutura_global;

void readFileD(string fileName);
void readFileT(string fileName);
void combinate(vector<string> vector, int perm[], int index, int n, int k);
void makeCombinate();
void makeIntersection(string keyInString);
void intersectionWithClassHash(string Key, vector<int> v);
void intersection();
unordered_map<string, vector<int>>::const_iterator cacheSearch(string key);
vector<int> intersection(vector<int> v1, vector<int> v2);
string tokenizeString(string s);
void returnsWinningClass();
void displayResult();
// ===========================================
void *consumidor(void *arg);
void *produtor(void *arg);
void printOutHashCombinate();
void printOutHashD();


#endif
