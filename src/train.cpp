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

int Train::getOpCount() {
  return countOp;
}

int Train::getLength() {
  if (first == nullptr) return 0;

  if (first->light == false) {
    Car* current = first;
    do {
      current->light = false;
      current = current->next;
      countOp++;
    } while (current != first);

    first->light = true;

    current = first;
    int result = 0;
    do {
      current = current->next;
      countOp++;
      result++;
    } while (current->light == false);
    return result;
  }

  Car* marker = first;
  int attempt = 1;

  while (true) {
    Car* walker = marker;
    for (int i = 0; i < attempt; i++) {
      walker = walker->next;
      countOp++;
    }
    walker->light = false;

    for (int i = 0; i < attempt; i++) {
      walker = walker->next;
      countOp++;
    }

    if (walker == marker && walker->light == false) {
      marker->light = true;
      return attempt;
    }
    attempt++;
  }
}
