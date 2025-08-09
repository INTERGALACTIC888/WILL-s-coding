#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
#include "robot-config.cpp"
//Motor group defenitions (real ports)

// pros::MotorGroup left_drivetrain({-20, 1, -2},pros::MotorGearset::green);    // Left side motors
// pros::MotorGroup right_drivetrain({8, -17, 16},pros::MotorGearset::green);  // right side motors
// lemlib::Drivetrain drivetrain(&left_drivetrain, &right_drivetrain, 12.625, lemlib::Omniwheel::NEW_4, 300, 0.5);
// pros::Imu imu(11);
// pros::Rotation left_drivetrain_rotation(6);
// lemlib::TrackingWheel left_tracking_wheel(&left_drivetrain_rotation, lemlib::Omniwheel::NEW_4, -6.4);
// lemlib::OdomSensors Odom (&left_tracking_wheel, nullptr, nullptr, nullptr, &imu);
// lemlib::ControllerSettings lateral_controller(10, 0, 5, 3, 1, 100, 3, 500, 20);
// lemlib::ControllerSettings angular_controller(2, 0.3, 25, 3, 1, 140, 3, 500, 0);
// lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, Odom);
// pros::Controller controller(pros::E_CONTROLLER_MASTER);
// // pros::Controller controller2(pros::E_CONTROLLER_PARTNER);
// pros::Motor intake2(14);
// pros::adi::DigitalOut clamp('A');


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

void autonomous(){
	pros::Motor front_left_motor = pros::Motor(20);
	pros::Motor middle_left_motor = pros::Motor(1);
	pros::Motor back_left_motor = pros::Motor(2);
	pros::Motor front_right_motor = pros::Motor(8);
	pros::Motor middle_right_motor = pros::Motor(17);
	pros::Motor back_right_motor = pros::Motor(16);
	}
