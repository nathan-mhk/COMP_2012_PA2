#ifndef WORKOUT_H
#define WORKOUT_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Workout {
public:
    // fat_change, muscle_change, energy_change can be positive, negative or 0
	Workout();
    Workout(string name_, int fat_change_ = 0, int muscle_change_ = 0, int energy_change_ = 0);

    string getName() const;
    int getFatChange() const;
    int getMuscleChange() const;
    int getEnergyChange() const;

	void debug_print(int indent = 0) const;

    Workout operator+(const Workout& workout);
	Workout& operator+=(const Workout& workout);
    Workout& operator=(const Workout& workout);

private:
    // workout's name
    string name;
    // Workout's affect on a buddy's fat
    int fat_change;
    // Workout's affect on a buddy's muscle
    int muscle_change;
    // Workout's affect on a buddy's energy
    int energy_change;
};

#endif //WORKOUT_H
