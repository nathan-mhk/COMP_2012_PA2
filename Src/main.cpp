#include "buddy.h"

using namespace std;

template <typename T>
void test_capable(Buddy& buddy, Activity<T> activity) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
	cout << buddy.getName() << " is capable for the following activity? " << (buddy.capable(activity) ? "Yes" : "No") << endl;
    activity.debug_print();
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}

template <typename T>
void print_vector(vector<T> values) {
	for (typename vector<T>::iterator itr = values.begin(); itr != values.end(); ++itr) {
		(*itr).debug_print();
	}
}

template <typename T>
void test_insert(Buddy& buddy, Activity<T> activity) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
    buddy << activity;
    cout << "after trying to insert " << activity.item.getName() << " [" << activity.start_time << "," << activity.end_time << "] to " << buddy.getName() << endl;
    buddy.debug_print();
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}

void test_remove_workout(Buddy& buddy, int start, int end) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
    string result = buddy.remove_workout(start, end) ? "Successful" : "Failed";
    cout << "result of removing workout activities from " << start << " to " << end << " of " << buddy.getName() << ": " << result << endl;
    buddy.debug_print();
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}

void test_remove_workout(Buddy& buddy, string name) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
    buddy.remove_workout(name);
    cout << "After trying to remove workout activities with name: " << name << " of " << buddy.getName() << endl;
    buddy.debug_print();
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}

void test_remove_dining(Buddy& buddy, int start, int end) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
    string result = buddy.remove_dining(start, end) ? "Successful" : "Failed";
    cout << "result of removing dining activities from " << start << " to " << end << " of " << buddy.getName() << ": " << result << endl;
    buddy.debug_print();
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}

void test_remove_dining(Buddy& buddy, string name) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
    buddy.remove_dining(name);
    cout << "After trying to remove dining activities with name: " << name << " of " << buddy.getName() << endl;
    buddy.debug_print();
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}

void test_summarize_workout(Buddy& buddy, int start, int end) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
	cout << "list workout activities of " << buddy.getName() << " from " << start << " to " << end << endl;
	print_vector(buddy.summarize_workout(start, end));
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}

void test_summarize_workout(Buddy& buddy, string name) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
	cout << "workout activities of " << buddy.getName() << " with name: " << name << endl;
	int total_time = 0;
	Workout sum = buddy.summarize_workout(name, total_time);
	sum.debug_print();
	cout << "total time: " << total_time << endl;
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}

void test_summarize_dining(Buddy& buddy, int start, int end) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
	cout << "list dining activities of " << buddy.getName() << " from " << start << " to " << end << endl;
	print_vector(buddy.summarize_dining(start, end));
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}

void test_summarize_dining(Buddy& buddy, string name) {
	cout << endl << ">>>>>>>>>>>>>>> start of test >>>>>>>>>>>>>>>" << endl;
	cout << "dining activities of " << buddy.getName() << " with name: " << name << endl;
	int total_time = 0;
	Dining sum = buddy.summarize_dining(name, total_time);
	sum.debug_print();
	cout << "total time: " << total_time << endl;
    cout << endl << "<<<<<<<<<<<<<<< end of test <<<<<<<<<<<<<<<" << endl;
}


int main() {
	Buddy tom = Buddy("Tom");
	tom.debug_print();

	Workout jogging("jogging", -10, -10, -10);
	Activity<Workout> jogging_activity1 = Activity<Workout>(7, 8, jogging);
	Activity<Workout> jogging_activity2 = Activity<Workout>(9, 12, jogging);
    Activity<Workout> jogging_activity3 = Activity<Workout>(14, 16, jogging);

	Workout lifting("lifting", -500, -30, -50);
	Activity<Workout> lifting_activity1 = Activity<Workout>(6, 8, lifting);
	Activity<Workout> lifting_activity2 = Activity<Workout>(18, 22, lifting);
    Activity<Workout> lifting_activity3 = Activity<Workout>(16, 18, lifting);


    Dining dish("dish", 100, 300, 300);
    Activity<Dining> dish_activity1 = Activity<Dining>(7, 10, dish);
    Activity<Dining> dish_activity2 = Activity<Dining>(9, 12, dish);
    Activity<Dining> dish_activity3 = Activity<Dining>(13, 15, dish);
    Activity<Dining> dish_activity4 = Activity<Dining>(10, 13, dish);

    test_capable(tom, jogging_activity1);
    test_capable(tom, jogging_activity2);

    test_insert(tom, jogging_activity3);

    test_capable(tom, jogging_activity1);
    test_capable(tom, jogging_activity2);
    test_capable(tom, jogging_activity3);
    test_capable(tom, lifting_activity1);
    test_capable(tom, lifting_activity2);
    test_capable(tom, lifting_activity3);

    test_insert(tom, jogging_activity2);
    test_insert(tom, jogging_activity1);
    test_insert(tom, lifting_activity3);
    test_insert(tom, lifting_activity2);

    test_summarize_workout(tom, 10, 18);
    test_summarize_workout(tom, "jogging");
    test_summarize_workout(tom, "lifting");

    test_insert(tom, dish_activity1);
    test_insert(tom, dish_activity2);
    test_insert(tom, dish_activity3);
    test_insert(tom, lifting_activity2);

    test_remove_workout(tom, 11, 6);
    test_remove_workout(tom, 7, 14);

    test_summarize_dining(tom, 10, 15);

    test_insert(tom, dish_activity4);

    test_summarize_dining(tom, "dish");
    test_summarize_workout(tom, "jogging");

	test_remove_dining(tom, 7, 14);
	test_remove_dining(tom, "dish");
	test_remove_workout(tom, "jogging");

    cout << "[The end of program]" << endl;
    return 0;
}
