#pragma once
#include "main.h"
#include "lemlib/api.hpp"

//Controller
extern pros::Controller controller;

//Drive motors (update ports in .cpp)
extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;

//Sensors you actually use right now
extern pros::Imu imu;
extern pros::Optical optical1;

//LemLib core
extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors odom; // IMU-only for now
extern lemlib::ControllerSettings linear; // forward PID
extern lemlib::ControllerSettings angular; // turn PID
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;
extern lemlib::Chassis chassis;

//Boot helper
void configureSensors();

//(Optional now, used below)
extern pros::Motor intake1;
extern pros::Motor intake2;
extern pros::Motor intake3;