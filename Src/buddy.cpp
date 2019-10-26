#include "buddy.h"

Buddy::Buddy(string name_, int fat_, int muscle_, int energy_, int money_) :
    name(name_),
    fat(max(0, fat_)),
    muscle(max(0, muscle_)),
    energy(max(0, energy_)),
    money(max(0, money_)) {
	
	workout_schedule = Schedule<Workout>();
	dining_schedule = Schedule<Dining>();
}

Buddy::~Buddy() {
}

string Buddy::getName() const {
    return name;
}

int Buddy::getFat() const {
    return fat;
}

int Buddy::getMuscle() const {
    return muscle;
}

int Buddy::getEnergy() const {
    return energy;
}

int Buddy::getMoney() const {
    return money;
}

void Buddy::debug_print(int indent) const {
    string indent1 = string(indent, '\t');
    string indent2 = string(indent+1, '\t');

    cout << indent1 << "Buddy:" << endl
         << indent2 << "name:" << name << endl
         << indent2 << "energy:" << energy << endl
         << indent2 << "fat:" << fat << endl
         << indent2 << "money:" << money << endl
         << indent2 << "muscle:" << muscle << endl;
	cout << indent1 << "<-Workout Schedule->:" << (workout_schedule.size() == 0 ? "Empty!\n" : "\n");
    workout_schedule.debug_print(indent + 1);
	cout << indent1 << "<-Dining Schedule->:" << (dining_schedule.size() == 0 ? "Empty!\n" : "\n");
	dining_schedule.debug_print(indent + 1);
}

bool Buddy::capable(Activity<Workout> workout_activity) {
    /*
	 * You ONLY need to consider the following to determine whether capable or not
	 * 1. check whether buddy's attributes are enough 
	 *     (enough means: energy + change of energy >= 0 and fat + change of fat >= 0 and muscle + change of muscle >= 0
	 *     , you may assume the changes of energy, fat and muscle of the work_activity are negative)
	 * 2. check whether buddy's schedule can fit the activity, you need to call isFree function in schedule.h
     * return true if both 1 and 2 are satisfied, otherwise return false
	 *
	 * Add your code here!
	 * */
    // int newEnergy = energy + workout_activity.item.getEnergyChange();
    // int newFat = fat + workout_activity.item.getFatChange();
    // int newMuscle = muscle + workout_activity.item.getMuscleChange();
    if (
        (energy + workout_activity.item.getEnergyChange() >= 0) &&
        (fat + workout_activity.item.getFatChange() >= 0) &&
        (muscle + workout_activity.item.getMuscleChange() >= 0) &&
        workout_schedule.isFree(workout_activity.start_time, workout_activity.end_time)) {
        return true;
    }
    return false;
}

bool Buddy::capable(Activity<Dining> dining_activity) {
    /*
	 * You ONLY need to consider the following to determine whether capable or not
	 * 1. check whether buddy's money is enough 
	 *     (enough means: money - price >= 0)
	 * 2. check whether buddy's schedule can fit the activity, you need to call isFree function in schedule.h
     * return true if both 1 and 2 are satisfied, otherwise return false
	 *
     * Add your code here!
     * */
    if (
        (money - dining_activity.item.getPrice >= 0) &&
        dining_schedule.isFree(dining_activity.start_time, dining_activity.end_time)) {
        return true;
    }
	return false;
}

Buddy& Buddy::operator<<(Activity<Workout> workout_activity) {
    /*
     * Check if workout_activity is capable or not
     * Add work_activity to work_schedule by using the insert function
     * update Buddy's variables: energy, fat, muscle
     * 
     * Similar for the following function 
     * 
     * Add your code here!
     */
    if (capable(workout_activity)) {
        workout_schedule.insert(workout_activity.start_time, workout_activity.end_time, workout_activity.item);
        energy += workout_activity.item.getEnergyChange();
        fat += workout_activity.item.getFatChange();
        muscle += workout_activity.item.getMuscleChange();
    }
    return (*this);
}

Buddy& Buddy::operator<<(Activity<Dining> dining_activity) {
    /*
     * Add your code here!
     */
	int newMoney = money - dining_activity.item.getPrice();
	if (capable(dining_activity) && newMoney >= 0) {
		dining_schedule.insert(dining_activity.start_time, dining_activity.end_time, dining_activity.item);
		energy += dining_activity.item.getEnergy();
		fat += dining_activity.item.getFat();
		money = newMoney;
	}
	return (*this);
}

bool Buddy::remove_workout(int start, int end) {
	Workout total_to_remove;
	vector<Workout> items = workout_schedule(start, end);
	for (vector<Workout>::iterator itr = items.begin(); itr != items.end(); ++itr) {
		total_to_remove += *itr;
	}
	if (energy >= total_to_remove.getEnergyChange()
			&& fat >= total_to_remove.getFatChange()
			&& muscle >= total_to_remove.getMuscleChange()) {
		if (workout_schedule.remove(start, end)) {
	        energy -= total_to_remove.getEnergyChange();
	        fat -= total_to_remove.getFatChange();
	        muscle -= total_to_remove.getMuscleChange();
			return true;
		}
	}
	return false;
}

bool Buddy::remove_dining(int start, int end) {
	Dining total_to_remove;
	vector<Dining> items = dining_schedule(start, end);
	for (vector<Dining>::iterator itr = items.begin(); itr != items.end(); ++itr) {
		total_to_remove += *itr;
	}
	if (fat >= total_to_remove.getFat()
			&& energy >= total_to_remove.getEnergy()) {
		if (dining_schedule.remove(start ,end)) {
	        fat -= total_to_remove.getFat();
	        energy -= total_to_remove.getEnergy();
	        money += total_to_remove.getPrice();
			return true;
		}
	}
	return false;
}

void Buddy::remove_workout(string name) {
	int total_time;
	Workout total_to_remove = workout_schedule.summarize(name, total_time);

	if (energy >= total_to_remove.getEnergyChange()
			&& fat >= total_to_remove.getFatChange()
			&& muscle >= total_to_remove.getMuscleChange()) {
		workout_schedule.remove(name);
	    energy -= total_to_remove.getEnergyChange();
	    fat -= total_to_remove.getFatChange();
	    muscle -= total_to_remove.getMuscleChange();
	}
}

void Buddy::remove_dining(string name) {
	int total_time;
	Dining total_to_remove = dining_schedule.summarize(name, total_time);

	if (fat >= total_to_remove.getFat()
			&& energy >= total_to_remove.getEnergy()) {
		dining_schedule.remove(name);
		fat -= total_to_remove.getFat();
		energy -= total_to_remove.getEnergy();
		money += total_to_remove.getPrice();
	}
}

Workout Buddy::summarize_workout(string name, int& total_time) {
	return workout_schedule.summarize(name, total_time);
}

Dining Buddy::summarize_dining(string name, int& total_time) {
	return dining_schedule.summarize(name, total_time);
}

vector<Workout> Buddy::summarize_workout(int start, int end) {
    return workout_schedule(start, end);
}

vector<Dining> Buddy::summarize_dining(int start, int end) {
    return dining_schedule(start, end);
}
