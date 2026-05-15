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

  // Выключаем свет в первом вагоне (маркер)
  first->light = false;
  int steps = 1;

  while (true) {
    // Идём вперёд, включая свет
    for (int i = 0; i < steps; i++) {
      first = first->next;
      countOp++;
      if (!first->light) {
        first->light = true;
      }
    }

    // Возвращаемся назад
    for (int i = 0; i < steps; i++) {
      first = first->prev;
      countOp++;
    }

    // Проверяем маркер
    if (!first->light) {
      steps++;
      first->light = false;
    } else {
      return steps;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
