#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "main.h"

//Declare motor groups (extern means they're defined elsewhere)
extern pros::MotorGroup left_drivetrain;
extern pros::MotorGroup right_drivetrain;

//Declare the drivetrain object
extern lemlib::Drivetrain drivetrain;
//Use Ctrl click on name for function info
//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor LeftF(3,pros::v5::MotorGears::blue);
pros::Motor LeftM(4,pros::v5::MotorGears::blue);
pros::Motor LeftB(5,pros::v5::MotorGears::blue);

pros::MotorGroup leftMotors({-20,18,-19}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({10,-8,9}, pros::MotorGearset::blue);

//5.5w
pros::Motor Inake1(8,pros::v5::MotorGears::green);
//imu
pros::IMU imu(5);

//cylinder
pros::adi::DigitalOut cylinder('A');

//Drivetrain
lemlib::Drivetrain drivetrain (
    &left_drivetrain, //Left motor group
    &right_drivetrain, //Right motor group
    10, //10 inch track width
    lemlib::Omniwheel::NEW_325, //Using new 3.25" omnis
    360, //Drivetrain rpm is 360
    2 //Horizontal drift is 2 (for now)
);

//Encoder
pros::adi::Encoder adi_encoder('A', 'B');

//Rotation sensor
pros::Rotation rotation_sensor(1);

//Testing if the IMU's are in the correct position
    //Replace 'A', 'B', with the ports the sensor is connected to
    pros::adi::Encoder vertical_encoder('A', 'B');
    //Replace 1 with the port the rotation sensor is connected to
    pros::Rotation horizontal_sensor(1);

    //This runs at the start of the program
    void initialize() {
        pros::lcd::initialize(); //Initialize brain screen
        while (true) { //Infinite loop
            //Print measurements from the adi encoder
            pros::lcd::print(0, "ADI Encoder: %i", adi_encoder.get_value());
            //Print measurements from the rotation sensor
            pros::lcd::print(1, "Rotation Sensor: %i", rotation_sensor.get_position());
            pros::delay(10); //Delay to save resources. DO NOT REMOVE
        }
    }

//Updating the variables
    //Reversed ADI Encoder
    pros::adi::Encoder adi_encoder('A', 'B', true);
    //Reversed rotation sensor
    pros::Rotation rotation_sensor(-1);

    //Initialise tracking wheels
    //Horizontal tracking wheel encoder
    pros::Rotation horizontal_encoder(20);
    //Vertical tracking wheel encoder
    pros::adi::Encoder vertical_encoder('C', 'D', true);
    //Horizontal tracking wheel
    lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);
    //Vertical tracking wheel
    lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5);

//PID
    //Lateral PID controller
    lemlib::ControllerSettings lateral_controller(
    10, //Proportional gain (kP)
    0, //Integral gain (kI)
    3, //Derivative gain (kD)
    3, //Anti windup
    1, //Small error range, in inches
    100, //Small error range timeout, in milliseconds
    3, //Large error range, in inches
    500, //Large error range timeout, in milliseconds
    20 //Maximum acceleration (slew)
);

//Angular PID controller
lemlib::ControllerSettings angular_controller(
    2, //Proportional gain (kP)
    0, //Integral gain (kI)
    10, //Derivative gain (kD)
    3, //Anti windup
    1, //Small error range, in degrees
    100, //Small error range timeout, in milliseconds
    3, //Large error range, in degrees
    500, //Large error range timeout, in milliseconds
    0 //Maximum acceleration (slew)
);

//Final config
//Left motor group
pros::MotorGroup left_motor_group({-1, 2, -3}, pros::MotorGears::blue);
//Right motor group
pros::MotorGroup right_motor_group({4, -5, 6}, pros::MotorGears::green);

//Drivetrain settings
lemlib::Drivetrain drivetrain(
    &left_motor_group, //Left motor group
    &right_motor_group, //Right motor group
    10, //10 inch track width
    lemlib::Omniwheel::NEW_4, //Using new 4" omnis
    360, //Drivetrain rpm is 360
    2 //Horizontal drift is 2 (for now)
);

//Imu
pros::Imu imu(10);
//Horizontal tracking wheel encoder
pros::Rotation horizontal_encoder(20);
//Vertical tracking wheel encoder
pros::adi::Encoder vertical_encoder('C', 'D', true);
//Horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);
//Vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5);

//Odometry settings
lemlib::OdomSensors sensors(
    &vertical_tracking_wheel, //Vertical tracking wheel 1, set to null
    nullptr, //Vertical tracking wheel 2, set to nullptr as we are using IMEs
    &horizontal_tracking_wheel, //Horizontal tracking wheel 1
    nullptr, //Horizontal tracking wheel 2, set to nullptr as we don't have a second one
    &imu //Inertial sensor
);

//Lateral PID controller
lemlib::ControllerSettings lateral_controller(
    10, //Proportional gain (kP)
    0, //Integral gain (kI)
    3, //Derivative gain (kD)
    3, //Anti windup
    1, //Small error range, in inches
    100, //Small error range timeout, in milliseconds
    3, //Large error range, in inches
    500, //Large error range timeout, in milliseconds
    20 //Maximum acceleration (slew)
);

//Angular PID controller
lemlib::ControllerSettings angular_controller(
    2, //Proportional gain (kP)
    0, //Integral gain (kI)
    10, //Derivative gain (kD)
    3, //Anti windup
    1, //Small error range, in degrees
    100, //Small error range timeout, in milliseconds
    3, //Large error range, in degrees
    500, //Large error range timeout, in milliseconds
    0 //Maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

// initialize function. Runs on program startup
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
}