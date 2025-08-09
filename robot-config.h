#pragma once
#include "main.h"
#include "lemlib/api.hpp"
extern pros::Controller controller;
extern pros::Motor intakeF;
// motor groups
extern pros::Motor intakeM;
extern pros::Motor intakeB;
extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;
extern pros::Imu imu;
extern pros::Rotation verticalEnc;
extern pros::ADIDigitalOut loader;
extern pros::ADIDigitalOut aligner;
extern pros::Optical optical;
extern pros::Optical optical1;
extern pros::Distance distance;
//lemlib defs
extern lemlib::TrackingWheel horizontal;
extern lemlib::TrackingWheel vertical;
extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings linear;
extern lemlib::ControllerSettings angular;
extern lemlib::OdomSensors odom;
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;
extern lemlib::Chassis chassis;
