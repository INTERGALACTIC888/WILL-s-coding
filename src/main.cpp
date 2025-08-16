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
void intakeBall() {
    //Spin intake, drive to a ball 24" ahead, stop when detected
    setIntake(127);
    lemlib::Pose target(0, 24);
    chassis.moveToPoint(target.x, target.y, 1500, {.minSpeed=48});
    while (chassis.isInMotion() && !isBallInIntake()) pros::delay(10);
    chassis.cancelMotion(); // in case we detected early
    setIntake(0);
}
ASSET(pathjerryio_txt);
void autonomous() {
    chassis.setPose(0, 0, 0);

    //If you want to follow the embedded path from static/example.txt:
    //Lookahead 15", 2s timeout
    chassis.follow(pathjerryio_txt, 15, 1000);

    //Or just do a simple motion:
    //Chassis.moveToPoint(10, 10, 4000);
    //Chassis.moveToPose(10, 10, 90, 4000);
}

void opcontrol() {
    while (true) {
    const double fwd = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;
    const double turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;
    chassis.arcade(fwd, turn);
    pros::delay(10);
    }
}