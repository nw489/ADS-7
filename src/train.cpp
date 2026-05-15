// Copyright 2022 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
  Car* newCar = new Car;
  newCar->light = light;
  newCar->next = nullptr;
  newCar->prev = nullptr;
  
  if (first == nullptr) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (first == nullptr) return 0;
  
  bool startLight = first->light;
  int distance = 1;
  
  while (true) {
    for (int i = 0; i < distance; i++) {
      first = first->next;
      countOp++;
    }
    
    first->light = !first->light;
    
    for (int i = 0; i < distance; i++) {
      first = first->prev;
      countOp++;
    }
    
    if (first->light != startLight) {
      return distance;
    }
    
    distance++;
  }
}

int Train::getOpCount() {
  return countOp;
}
