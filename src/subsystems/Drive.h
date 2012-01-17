#ifndef SUBSYSTEMS_DRIVE_H_
#define SUBSYSTEMS_DRIVE_H_

#include "WPILib.h"

#include "config/Constants.h"

class Drive {
 public:
  Drive(Victor* left, Victor* right);
  void SetLeftDrivePower(double power);
  void SetRightDrivePower(double power);
 private:
  Victor* leftDriveMotors_;
  Victor* rightDriveMotors_;

  Constants* constants;
};


#endif  // SUBSYSTEMS_DRIVE_H_