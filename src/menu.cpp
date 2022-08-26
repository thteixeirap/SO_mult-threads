#include "menu.hpp"
#include "hash_and_database.hpp"

void menu()
{
    int op = 0;

    do
    {
        cout << endl;
        cout << "[1] - Read and store [D.csv]" << endl;
        cout << "[2] - Read and store [T.csv]" << endl;
        cout << "[3] - Exit" << endl;

        cout << "Choose an option:  ";
        cin >> op;

        switch (op)
        {
        case 1:
            readFileD("src/dataset/D.csv");
            printOutHashD();
            break;

        case 2:
            readFileT("src/dataset/T.csv");
            printOutHashT();
            break;

        case 3:
            cout << endl << "Finished Program" << endl << endl;
            break;

        default:
            break;
        }

    } while (op != 3);
}