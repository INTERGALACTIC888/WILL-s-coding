#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
#include "robot-config.cpp"



void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

void disabled() {}

void competition_initialize() {}
bool isBallInIntake(){
	//e.g. optical sensor detects ball
	return optical1.get_proximity() > 100;
}
void intakeBall() {
    chassis.setPose(0, 0, 0);
    lemlib::Pose intakeBallTarget(0, 24);

    // spin intake
    intakeBall();
    // move towards ball
    chassis.moveToPoint(intakeBallTarget.x, intakeBallTarget.y, 1500, {.minSpeed=48});

    // Wait until a ball has been intaked.
    // Or until the motion has stopped after which, the state of
    // the intake is very unlikely to change and we'd be wasting time
    while (chassis.isInMotion() && !isBallInIntake()) {
        pros::delay(10); // don't consume all the cpu's resources
    }

    // Cancel and move on to the next motion since the purpose of the first is complete.
    // If the motion had exited before a ball was detected, then this will do nothing.
    chassis.cancelMotion();
}
void autonomous(){
	pros::Motor front_left_motor = pros::Motor(20);
	pros::Motor middle_left_motor = pros::Motor(1);
	pros::Motor back_left_motor = pros::Motor(2);
	pros::Motor front_right_motor = pros::Motor(8);
	pros::Motor middle_right_motor = pros::Motor(17);
	pros::Motor back_right_motor = pros::Motor(16);

	// set chassis pose
    chassis.setPose(0, 0, 0);
    // lookahead distance: 15 inches
    // timeout: 2000 ms
    chassis.follow(example_txt, 15, 2000);
    // follow the next path, but with the robot going backwards
    chassis.follow(example2_txt, 15, 2000, false);
	chassis.moveToPoint(10, 10, 4000); 
	// move the chassis to (10, 10)
    // with a timeout of 4000 ms

	chassis.moveToPose(10, 10, 90, 4000); 
	// move the chassis to (10, 10, 90)
    // with a timeout of 4000 ms
	
	}
	// path file name is "example.txt".
	// "." is replaced with "_" to overcome c++ limitations
	ASSET(example_txt);
	ASSET(example2_txt)

