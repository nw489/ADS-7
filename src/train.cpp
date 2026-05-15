// Copyright 2022 NNTU-CS
#include "train.h"
#include <cstddef>


Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (!first) return;
  Car *cur = first->next;
  while (cur != first) {
    Car *tmp = cur->next;
    delete cur;
    cur = tmp;
  }
  delete first;
}

void Train::addCar(bool light) {
  Car *car = new Car{light, nullptr, nullptr};
  if (!first) {
    car->next = car;
    car->prev = car;
    first = car;
  } else {
    Car *last = first->prev;
    last->next = car;
    car->prev = last;
    car->next = first;
    first->prev = car;
  }
}

int Train::getLength() {
  if (!first) return 0;
  countOp = 0;

  bool startLight = first->light; 
  for (int k = 1; ; k++) {

    Car *cur = first;
    for (int i = 0; i < k; i++) {
      cur = cur->next;
      countOp++;
    }

    cur->light = !cur->light;


    for (int i = 0; i < k; i++) {
      cur = cur->prev;
      countOp++;
    }



    if (first->light != startLight) {
      first->light = startLight; 
      return k;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
