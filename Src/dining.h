#ifndef DINING_H
#define DINING_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Dining {
public:
    // fat, energy, price are all non-negative
	Dining();
    Dining(string name_, int fat_ = 0, int energy_ = 0, int price_ = 0);

    string getName() const;
    int getFat() const;
    int getEnergy() const;
    int getPrice() const;

	void debug_print(int indent = 0) const;

    Dining operator+(const Dining &dining);
	Dining& operator+=(const Dining &dining);
    Dining& operator=(const Dining &dining);

private:
    // meal's name
    string name;
    // Represents how much fat a person will absorb when eating this food, you may assume it is non-negative
    int fat;
    // Represents how much muscle a person will absorb when eating this food, you may assume it is non-negative
    int energy;
    // Represents how much a person needs to pay in order to eat this food, you may assume it is non-negative
    int price;
};

#endif //DINING_H
