#ifndef BUDDY_H
#define BUDDY_H

#include <iostream>
#include <string>
#include <cassert>
#include "dining.h"
#include "workout.h"
#include "schedule.h"

using namespace std;

template<typename T>
struct Activity {
	int start_time;
	int end_time;
	T item;
	Activity(int start, int end, T action) {
	    assert(start < end && "start time should be smaller than end time!");
		start_time = start;
		end_time = end;
		item = action;
	}
	void debug_print() const {
		cout << "duration: [" << start_time << ", " << end_time << "]\n";
		item.debug_print();
	}
};

class Buddy {
public:
    // fat, muscle, energy, money are non-negative numbers
    Buddy(string name_, int fat_ = 1000, int muscle_ = 100, int energy_ = 100, int money_ = 1000);
    ~Buddy();

    string getName() const;
    int getFat() const;
    int getMuscle() const;
    int getEnergy() const;
    int getMoney() const;

	void debug_print(int indent = 0) const;

    // ensures the duration of workout and dining are larger than 0
    bool capable(Activity<Workout> workout_activity);
    bool capable(Activity<Dining> dining_activity);

    Buddy& operator<<(Activity<Workout> workout_activity);
    Buddy& operator<<(Activity<Dining> dining_activity);

    bool remove_workout(int start, int end);
    bool remove_dining(int start, int end);
    void remove_workout(string name);
    void remove_dining(string name);

	Workout summarize_workout(string name, int& total_time);
	Dining summarize_dining(string name, int& total_time);

	vector<Workout> summarize_workout(int start, int end);
    vector<Dining> summarize_dining(int start, int end);

private:
    string name;
    int fat;
    int muscle;
    int energy;
    int money;

    Schedule<Workout> workout_schedule;
    Schedule<Dining> dining_schedule;
};


#endif //BUDDY_H
