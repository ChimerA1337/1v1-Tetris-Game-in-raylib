#ifndef RANDOMIZER_H
#define RANDOMIZER_H

typedef struct Bags {
    int *bag1;
    int *bag2;
} Bags;

int getNextMino(int *bag);


int *createBag();
Bags *createBags();
void freeBag(int *bag);
void freeBags(Bags *bags);
void shuffle(int *bag);
void swap(int *pos1, int *pos2);
void refreshBags(Bags *bags);

void printBags(Bags *bags);

int peekBag(Bags *bags, int offset);

#endif