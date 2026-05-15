// Copyright 2022 NNTU-CS
#include "train.h"
#include <iostream>
#include <fstream>
#include <random>

Train createTrain(int n, int type) {
  Train train;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);
  
  for (int i = 0; i < n; i++) {
    if (type == 0) train.addCar(false);
    else if (type == 1) train.addCar(true);
    else train.addCar(dis(gen));
  }
  return train;
}

int main() {
  std::ofstream file("data.csv");
  file << "n,all_off,all_on,random\n";
  
  for (int n = 2; n <= 100; n++) {
    long long off_sum = 0, on_sum = 0, rand_sum = 0;
    
    for (int trial = 0; trial < 10; trial++) {
      Train t_off = createTrain(n, 0);
      Train t_on = createTrain(n, 1);
      Train t_rand = createTrain(n, 2);
      
      t_off.getLength();
      t_on.getLength();
      t_rand.getLength();
      
      off_sum += t_off.getOpCount();
      on_sum += t_on.getOpCount();
      rand_sum += t_rand.getOpCount();
    }
    
    file << n << "," << off_sum/10.0 << "," << on_sum/10.0 << "," << rand_sum/10.0 << "\n";
  }
  
  file.close();
  return 0;
}
