#include "menu.hpp"
#include "hash_and_database.hpp"

using namespace std;

int main()
{

   readFileD("src/dataset/D.csv");
   readFileT("src/dataset/T.csv");
  
   steady_clock::time_point t1 = steady_clock::now();
   pthread_t cons[NUMCONS];
   pthread_t prod[NUMPROD];
   estrutura_global vglobal;

   vglobal.currentidx = 0;
   for (int i = 0; i < BUFFERSIZE; i++)
      vglobal.buffer[i] = -1;

   pthread_mutex_init(&vglobal.buffer_mutex, NULL);
   sem_init(&vglobal.buffer_full, 0, BUFFERSIZE);
   sem_init(&vglobal.buffer_empty, 0, 0);

   for (int i = 0; i < NUMPROD; i++)
      pthread_create(&(prod[i]), NULL, produtor, &vglobal);

   for (int i = 0; i < NUMCONS; i++)
      pthread_create(&(cons[i]), NULL, consumidor, &vglobal);

   for (int i = 0; i < NUMCONS; i++)
      pthread_join(cons[i], NULL);

   for (int i = 0; i < NUMPROD; i++)
      pthread_join(prod[i], NULL);

   steady_clock::time_point t2 = steady_clock::now();
   duration<double> tempo = duration_cast<duration<double>>(t2 - t1);
   cout << "Tempo de Total: " << tempo.count() << " Segundos " << endl;

   // menu();
   
    exit(0);
}
