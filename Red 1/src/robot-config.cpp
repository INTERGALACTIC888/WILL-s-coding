#include "robot-config.hpp"
#include "lemlib/chassis/trackingWheel.hpp" //Wheel size constants

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//Motors (TODO: update to your real ports; negative = reversed)
pros::MotorGroup leftDrive({-20, 1, -2}, pros::MotorGearset::green);
pros::MotorGroup rightDrive({8, -17, 16}, pros::MotorGearset::green);

//Optional (used by intakeBall() helper in main.cpp)
pros::Motor intake1(1, pros::v5::MotorGears::blue);
pros::Motor intake2(2,pros::v5::MotorGears::blue);
pros::Motor intake3(10, pros::v5::MotorGears::blue);
pros::adi::Pneumatics top('A', false);
pros::adi::Pneumatics basket('H', false);
pros::adi::Pneumatics load ('F', false);

//Sensors
pros::Imu imu(11); // TODO: change to your real IMU port
pros::Optical optical1(9); // TODO: change to your real optical port

//LemLib core
constexpr double TRACK_WIDTH_IN = 28; // measure center-to-center
constexpr auto WHEEL_PRESET = lemlib::Omniwheel::NEW_325; // use NEW_4 if 4" wheels
constexpr int DRIVE_RPM = 200; // green cartridge
constexpr float H_DRIFT = 8.0f; // 

lemlib::Drivetrain drivetrain(
&leftDrive,
&rightDrive,
TRACK_WIDTH_IN,
WHEEL_PRESET,
DRIVE_RPM,
H_DRIFT
);

//Your LemLib needs 4 tracking-wheel pointers + IMU.
//IMU-only odometry for now: pass four nullptrs + &imu.
pros::Rotation horizontalEncoder(20); //change these ports
pros::Rotation verticalEncoder(-19); // negetive means that the encoder is backwards
lemlib::TrackingWheel horizontal(&horizontalEncoder, lemlib::Omniwheel::NEW_275, -6.5);
lemlib::TrackingWheel vertical(&verticalEncoder, lemlib::Omniwheel::NEW_275, -6.5);

lemlib::OdomSensors sensors(&vertical, 
    nullptr, 
    &horizontal, 
    nullptr, 
    &imu
);

//PID starting points (safe defaults—tune on the bot)
lemlib::ControllerSettings linear(
12, 0, 30, //kP,kI,kD
3, //windupRange
1, 0, //smallError,smallErrorTimeout
3, 1, //largeError,largeErrorTimeout
0 //slew
);
lemlib::ControllerSettings angular(
3, 0, 35,
3,
1, 0,
3, 1,
0
);

//Driver curves
lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.0);
lemlib::ExpoDriveCurve steerCurve(3, 10, 1.0);

//Single global chassis instance
lemlib::Chassis chassis(
drivetrain,
linear,
angular,
odom,
&throttleCurve,
&steerCurve
);

//Boot helper
void configureSensors() {
imu.reset();
while (imu.is_calibrating()) pros::delay(20);
optical1.set_led_pwm(100); //Helpful for color/proximity reliability
}
