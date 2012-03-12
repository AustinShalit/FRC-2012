#ifndef AUTO_SHOOT_CMD_H_
#define AUTO_SHOOT_CMD_H_

#include "auto/AutoCommand.h"

class Drive;
class Pid;
class Shooter;
class Intake;

class ShootCommand : public AutoCommand {
 public:
  /**
   * Constructor. Takes a drive object and the angle to turn.
   */
  ShootCommand(Shooter* shooter, Intake* intake, bool runIntake, double timeout);

  /**
   * Initializes 
   */
  void Initialize();

  /**
   * Uses PID to turn to the wanted angle. Returns true when complete.
   */
  bool Run();
  
  ~ShootCommand();

 private:
  Shooter* shooter_;
  Intake* intake_;
  bool runIntake_;
  
};

#endif
