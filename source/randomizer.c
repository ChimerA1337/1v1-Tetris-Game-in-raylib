#include <stdlib.h>
#include "../include/randomizer.h"
#include <stdio.h>
#include "../include/definitions.h"

int *createBag() {
    int *bag = malloc(sizeof(*bag) * BAG_SIZE);
    for(int i = 0; i < BAG_SIZE; i++) bag[i] = i+1;
    return bag;
}

Bags *createBags() {
    Bags *bags = malloc(sizeof(Bags));
    bags->bag1 = createBag();
    bags->bag2 = createBag();
    shuffle(bags->bag1);
    shuffle(bags->bag2);

    return bags;
}

void freeBags(Bags *bags) {
    freeBag(bags->bag1);
    freeBag(bags->bag2);
    free(bags);
}

void freeBag(int *bag) {
    free(bag);
}

void refreshBags(Bags *bags) {
    int *tempBag = bags->bag1;
    bags->bag1 = bags->bag2;
    bags->bag2 = tempBag;

    for (int i = 0; i < BAG_SIZE; i++) bags->bag2[i] = i+1;
    shuffle(bags->bag2);
}

int getNextMino(int *bag) {
    for(int i = 0; i < BAG_SIZE; i++) {
        if(bag[i] != 0) {
            int nextMino = bag[i];
            bag[i] = 0;
            return nextMino;
        }
    }
    return 0;
}

// Apparently you need to do it this way with the swaps, some Fischer Yates technology thing
void shuffle(int *bag) {
    for (int i = BAG_SIZE-1; i > 0; i--) swap(&bag[i], &bag[rand() % (i+1)]);
}

void swap(int *pos1, int *pos2) {
    int temp = *pos1;
    *pos1 = *pos2;
    *pos2 = temp;
}

void printBags(Bags *bags) {
    printf("\nbag1: \n");
    for(int i = 0; i < BAG_SIZE; i++) printf("%d, ", bags->bag1[i]);
    printf("\nbag2: \n");
    for(int i = 0; i < BAG_SIZE; i++) printf("%d, ", bags->bag2[i]);
}

int peekBag(Bags *bags, int offset) {
    int found = 0;
    for (int i = 0; i < BAG_SIZE; i++) {
        if (bags->bag1[i] != 0) {
            if (found == offset) return bags->bag1[i]-1;
            found++;
        }
    }
    for (int i = 0; i < BAG_SIZE; i++) {
        if (bags->bag2[i] != 0) {
            if (found == offset) return bags->bag2[i]-1;
            found++;
        }
    }
    return 0;
}