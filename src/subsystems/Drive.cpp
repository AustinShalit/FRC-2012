#include "subsystems/Drive.h"

#include <cmath>

Drive::Drive(Victor* leftVictorA, Victor* leftVictorB, Victor* rightVictorA, Victor* rightVictorB,
       Solenoid* shiftSolenoid, DoubleSolenoid* pizzaWheelSolenoid, Encoder* leftEncoder,
       Encoder* rightEncoder, Gyro* gyro, Accelerometer* accelerometerX, Accelerometer* accelerometerY,
       Accelerometer* accelerometerZ) {
  constants_ = Constants::GetInstance();
  leftDriveMotorA_ = leftVictorA;
  leftDriveMotorB_ = leftVictorB;
  rightDriveMotorA_ = rightVictorA;
  rightDriveMotorB_ = rightVictorB;
  shiftSolenoid_ = shiftSolenoid;
  pizzaWheelSolenoid_ = pizzaWheelSolenoid;
  SetHighGear(true); // Default to high gear
  leftDriveEncoder_ = leftEncoder;
  rightDriveEncoder_ = rightEncoder;
  ResetEncoders();
  gyro_ = gyro;
  gyro_->Reset();
  accelerometerX_ = accelerometerX;
  accelerometerY_ = accelerometerY;
  accelerometerZ_ = accelerometerZ;
}

void Drive::SetLinearPower(double left, double right) {
  double linearLeft=Linearize(left);
  double linearRight=Linearize(right);
  printf("li: %f ri: %f\nlo: %f ro: %f\n\n", left, right, linearLeft, linearRight);
  SetPower(linearLeft, linearRight);
}

double Drive::GetLeftEncoderDistance() {
  // Number of clicks read by encoder / number of clicks per rotation * gear ratio from encoder to wheel *
  // wheel circumference

  // Don't have current specs now, just return encoder rotations
  return -leftDriveEncoder_->Get() / 256.0;
}

double Drive::GetRightEncoderDistance() {
  // Number of clicks read by encoder / number of clicks per rotation * gear ratio from encoder to wheel *
  // wheel circumference

  // Don't have current specs now, just return encoder rotations
  return rightDriveEncoder_->Get() / 256.0;
}

void Drive::ResetEncoders() {
  leftDriveEncoder_->Reset();
  rightDriveEncoder_->Reset();
}

void Drive::SetHighGear(bool highGear) {
  shiftSolenoid_->Set(highGear);
}

void Drive::SetPizzaWheelDown(bool down) {
  if (down) {
    pizzaWheelSolenoid_->Set(DoubleSolenoid::kForward);
  } else {
    pizzaWheelSolenoid_->Set(DoubleSolenoid::kReverse);
  }
}

bool Drive::GetPizzaUp() {
  return (pizzaWheelSolenoid_->Get() == DoubleSolenoid::kForward);
}

double Drive::GetGyroAngle() {
  return gyro_->GetAngle();
}

void Drive::ResetGyro() {
  gyro_->Reset();
}

double Drive::GetXAcceleration() {
  return accelerometerX_->GetAcceleration();
}

double Drive::GetYAcceleration() {
  return accelerometerY_->GetAcceleration();
}

double Drive::GetZAcceleration() {
  return accelerometerZ_->GetAcceleration();
}

void Drive::SetPower(double left, double right) {
  left = PwmLimit(left);
  right = PwmLimit(right);
  leftDriveMotorA_->Set(left);
  leftDriveMotorB_->Set(left);
  rightDriveMotorA_->Set(-right);
  rightDriveMotorB_->Set(-right);
}

double Drive::Linearize(double x) {
  if (x > 0) {
    return constants_->linearCoeffA * pow(x, 4) + constants_->linearCoeffB * pow(x, 3) +
        constants_->linearCoeffC * pow(x, 2) + constants_->linearCoeffD * x + constants_->linearCoeffE;
  } else if (x < 0) {
    // Rotate the linearization function by 180 degrees to handle negative input.
    return -Linearize(-x);
  } else {
    return 0;
  }
}

