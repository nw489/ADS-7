// Copyright 2022 NNTU-CS
// Вычислительный эксперимент — алгоритм «зигзаг»
// Идея: идти вперёд на k шагов, переключить свет, вернуться назад на k шагов.
// Если свет стартового вагона изменился — k == длина поезда.
// Сложность: O(n^2), т.к. суммарно 2*(1+2+...+n) = n*(n+1) шагов.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "train.h"

// Создать поезд из n вагонов
// mode: 0 = все выключены, 1 = все включены, 2 = случайные
Train* makeTrain(int n, int mode) {
  Train *t = new Train();
  for (int i = 0; i < n; i++) {
    bool light;
    if (mode == 0)      light = false;
    else if (mode == 1) light = true;
    else                light = (rand() % 2 == 1);
    t->addCar(light);
  }
  return t;
}

int main() {
  srand(static_cast<unsigned>(time(nullptr)));

  const int minN    = 2;
  const int maxN    = 150;  
  const int step    = 2;
  const int repeats = 10;    

  std::ofstream csv("result/data.csv");
  csv << "n,ops_off,ops_on,ops_random,theoretical\n";
  std::cout << "n\tops_off\tops_on\tops_random\ttheoretical\n";

  for (int n = minN; n <= maxN; n += step) {
    
    Train *t0 = makeTrain(n, 0);
    t0->getLength();
    int ops_off = t0->getOpCount();
    delete t0;


    Train *t1 = makeTrain(n, 1);
    t1->getLength();
    int ops_on = t1->getOpCount();
    delete t1;


    long long sum = 0;
    for (int r = 0; r < repeats; r++) {
      Train *tr = makeTrain(n, 2);
      tr->getLength();
      sum += tr->getOpCount();
      delete tr;
    }
    int ops_random = static_cast<int>(sum / repeats);

    
    int theory = n * (n + 1);

    csv << n << "," << ops_off << "," << ops_on << "," << ops_random
        << "," << theory << "\n";
    std::cout << n << "\t" << ops_off << "\t" << ops_on << "\t"
              << ops_random << "\t" << theory << "\n";
  }

  csv.close();
  std::cout << "\nДанные сохранены в result/data.csv\n";
  std::cout << "Запустите plot.py для построения графика.\n";
  return 0;
}
