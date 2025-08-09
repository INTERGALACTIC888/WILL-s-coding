#include "robot-config.h"
#include "lemlib/chassis/trackingWheel.hpp"

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// -------------------- Motors --------------------
pros::MotorGroup leftDrive({-20, 1, -2}, pros::MotorGearset::green); // TODO: update ports
pros::MotorGroup rightDrive({8, -17, 16}, pros::MotorGearset::green); // TODO: update ports

// -------------------- Sensors --------------------
pros::Imu imu(11); // TODO: update to your real port

// -------------------- LemLib core --------------------
constexpr double TRACK_WIDTH_IN = 12.625; // measure center-to-center of left & right wheels
constexpr int DRIVE_RPM = 200; // green cartridge decared above

lemlib::Drivetrain drivetrain(
    &leftDrive, 
    &rightDrive,
    TRACK_WIDTH_IN,
    lemlib::Omniwheel::NEW_325, // 4" omni preset; if 3.25", use NEW_325
    DRIVE_RPM,
    0.5 // drift (tune later)
);

// IMU-only odometry to start (you can add tracking wheels later)
// If you do not have tracking wheels, use the IMU-only constructor:
lemlib::OdomSensors odom(
    nullptr, nullptr, nullptr, nullptr &imu
);

// PID placeholders (safe starters; we’ll tune on the real bot)
// Example: lemlib::ControllerSettings(kP, kI, kD, windupRange, smallErrorRange, smallErrorTimeout, largeErrorRange, largeErrorTimeout, slew)
lemlib::ControllerSettings linear(12, 0, 30, 3, 1, 0, 3, 1, 0);
lemlib::ControllerSettings angular(3, 0, 35, 3, 1, 0, 3, 1, 0);

// Driver input curves (gentle expo, adjust to taste)
lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.0, true);
lemlib::ExpoDriveCurve steerCurve(3, 10, 1.0, true);

// THE one-and-only chassis
lemlib::Chassis chassis(
drivetrain, linear, angular, odom,
&throttleCurve, &steerCurve
);

// Optional: one place to configure sensors at boot
void configureSensors() {
imu.reset();
while (imu.is_calibrating()) pros::delay(20);
}