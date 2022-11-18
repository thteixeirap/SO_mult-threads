#include "menu.hpp"
#include "hash_and_database.hpp"

void menu()
{
    int op = 0;

    do
    {
        // printf("\n\n");
        // printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        // printf("      @                                                   @\n");
        // printf("      @                        MENU                       @\n");
        // printf("      @                                                   @\n");
        // printf("      @    [1] -> Read and store [D.csv] and [T.csv]      @\n");
        // printf("      @    [2] -> Make the T hash combinates              @\n");
        // printf("      @    [3] -> Make intersection                       @\n");
        // printf("      @    [0] -> Exit                                    @\n");
        // printf("      @                                                   @\n");
        // printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");

        int op = 1;

        switch (op)
        {
        case 1:
            steady_clock::time_point t1 = steady_clock::now();
            readFileD("src/dataset/D.csv");
            readFileT("src/dataset/T.csv");
            // printOutHashD();
            // printOutHashT();
            makeCombinate();
            printOutHashCombinate();

            steady_clock::time_point t1Intersection = steady_clock::now();
            intersection();
            steady_clock::time_point t2Intersection = steady_clock::now();
            duration<double> tempoIntersection = duration_cast<duration<double>>(t2Intersection - t1Intersection);
            cout << "Tempo Interseção: " << tempoIntersection.count() << " Segundos " << endl;

            steady_clock::time_point t2 = steady_clock::now();
            duration<double> tempo = duration_cast<duration<double>>(t2 - t1);
            cout << "Tempo de Total: " << tempo.count() << " Segundos " << endl;
            // displayResult();
            // printOutIntersection();
            exit(0);
            break;

            // case 0:
            //     cout << endl
            //          << "Finished Program" << endl
            //          << endl;
            //     break;
            // default:
            //     break;
        }
    } while (op != 0);
}
