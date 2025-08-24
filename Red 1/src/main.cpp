#include "main.h"
#include "robot-config.h"
#include "lemlib/api.hpp"
#include "lemlib/asset.hpp" //Only needed if you use ASSET() paths
//NOTES
//Measure distance between tracking wheels and tracking centre
//Tracking centre is the middle of the drivetrain
//Find the input in robot-config.cpp, search for "lemlib::trackingwheel horizontal" and "lemlib::trackingwheel vertical"
//For tracking wheel size do not include decimal, e.g. 3.25 in would become 325
//Units are Inches
//Name sensors "Horizontal encoder" and "vertical encoder" in robot-config.cpp

//Tuning pid
    //Search for "lemlib::ControllerSettings latteralController" and "lemlib::ControllerSettings angularController"
//CHange drive mode by searching in main.cpp "chassis.tank" or "chassis.split arcade"
//Optional: embed static/example.txt as an asset (you have this file)

//TODO
    //Install the 2 TrackingWheels
        //Use smallest size available
        //Make wheels spriny and pneumatically controlled
            //Do this by having low pressure air in piston holding wheel
    //Find the measurements from tracking wheel and tracking centre(middle of drivetrain)
        //Make sure that the wheels are flat or ground level
    //Find size of tracking wheels

ASSET(example_txt); // comment out if you don't want to use path following yet

//LCD button demo from PROS template
void on_center_button() {
    static bool pressed = false;
    pressed = !pressed;
    pros::lcd::set_text(2, pressed ? "I was pressed!" : "");
}

void initialize() {
    pros::lcd::initialize();
    pros::lcd::set_text(1, "Hello PROS User!");
    pros::lcd::register_btn1_cb(on_center_button);

    configureSensors();
    chassis.setPose(0, 0, 0);

    //Show pose on LCD
    pros::Task screenTask([] {
        while (true) {
            auto p = chassis.getPose();
            pros::lcd::print(0, "X: %.2f", p.x);
            pros::lcd::print(1, "Y: %.2f", p.y);
            pros::lcd::print(2, "Th: %.2f", p.theta);
            pros::delay(50);
        }
    });
}

void disabled() {}
void competition_initialize() {}

//Tiny helper the way you intended (fixed; no recursion)
static inline bool isBallInIntake() {
    return optical1.get_proximity() > 100; // tune threshold on the bot
}
static inline void setIntake(int v) {
    intakeF.move(v); intakeM.move(v); intakeB.move(v);
}
ASSET(Part1_txt);
ASSET(Part2_txt);
ASSET(Part3_txt);
ASSET(Part4_txt);
ASSET(Part5_txt);
ASSET(Part6_txt);
ASSET(Part7_txt);
ASSET(Part8_txt);
ASSET(Part9_txt);
ASSET(Part10_txt);
void autonomous() {
    chassis.setPose(0, 0, 0);

    //If you want to follow the embedded path from static/example.txt:
    //Lookahead 15", 2s timeout
    intake();
    chassis.follow(Part1_txt, 15, 10);
    intakestop();
    chassis.follow(Part2_txt, 15, 10);
    //Spin the intake
    loading();
    //The delay time in milisecconds
    pros::delay(500);
    //Stop the intake
    loadingstop();
    chassis.follow(Part3_txt, 15, 10);
    chassis.turnToHeading(float (90), int (10));
    chassis.follow(Part4_txt, 15, 10);
    //Put blocks into highgoal
    highgoal();
    //The delay time in milisecconds
    pros::delay(500);
    //Stop putting blocks into the highgoal
    highgoalstop();
    chassis.follow(Part5_txt, 15, 10);
    chassis.turnToHeading(float (0), int (10));
    chassis.follow(Part6_txt, 15, 10);
    highgoal();
    pros::delay(5000);
    highgoalstop();
    chassis.follow(Part7_txt, 15, 10);
    chassis.turnToHeading(float (270), int (10));
    chassis.follow(Part8_txt, 15, 10);
    loading();
    pros::delay(5000);
    loadingstop();

    //Or just do a simple motion:
    //Chassis.moveToPoint(10, 10, 4000);
    //Chassis.moveToPose(10, 10, 90, 4000);
    chassis.follow(Part9_txt, 15, 10);
    intake();
    chassis.follow(Part10_txt, 15, 10);
    intakestop();
    lowgoal();
    pros::delay(5000);
    lowgoalstop();
}
void intake(){


}
void intakestop(){


}
void loading(){


}
void loadingstop(){


}
void lowgoal(){


}
void lowgoalstop(){


}
void highgoal(){


}
void highgoalstop(){


}
void opcontrol() {
    while (true) {
    const double fwd = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;
    const double turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;
    chassis.arcade(fwd, turn);
    pros::delay(10);
    }
}