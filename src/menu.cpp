#include "menu.hpp"
#include "hash_and_database.hpp"

void menu()
{
    int op = 0;

    do
    {

        printf("\n\n");
        printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        printf("      @                                                   @\n");
        printf("      @                        MENU                       @\n");
        printf("      @                                                   @\n");
        printf("      @    [1] -> Read and store [D.csv] and [T.csv]      @\n");
        printf("      @    [2] -> Make the T hash combinates              @\n");
        printf("      @    [3] -> Make intersection                       @\n");
        printf("      @    [0] -> Exit                                    @\n");
        printf("      @                                                   @\n");
        printf("      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");

        cout << endl
             << "Choose an option:  ";
        cin >> op;

        switch (op)
        {
        case 1:
            readFileD("src/dataset/D.csv");
            cout << endl
                 << " File D Read" << endl;
            readFileT("src/dataset/T.csv");
            cout << endl
                 << " File T Read" << endl;
            printOutHashD();
            printOutHashT();

            break;

        case 2:

            makeCombinate();
            cout << endl
                 << endl
                 << "\t\t\t COMBINATE HASH " << endl
                 << endl;
            printOutHashCombinate();
            break;

        case 0:
            cout << endl
                 << "Finished Program" << endl
                 << endl;
            break;

        case 3:
            intersection();
            exit(0);
            break;

        default:
            break;
        }

    } while (op != 0);
}
