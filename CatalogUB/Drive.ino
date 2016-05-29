/***************************************************************************
Copyright (c) 2016 Bill Silver, Member of Gizmo Garden LLC. This source code
is distributed under terms of the GNU General Public License, Version 3,
which grants certain rights to copy, modify, and redistribute. The license
can be found at <http://www.gnu.org/licenses/>. There is no express or
implied warranty, including merchantability or fitness for a particular
purpose.
***************************************************************************/

// *********************************************
// *                                           *
// *  Drive on the Road and Follow the Leader  *
// *                                           *
// *********************************************

// Show the current speed and road sensor readings while driving
MakeGizmoGardenTask(Dashboard)
{
  lcd.setCursor(12, 0);
  ggPrint(lcd, driver.getFullSpeed(), 4);
  for (int s = 0; s < 2; ++s)
  {
    lcd.setCursor(8 * s + 2, 1);
    ggPrint(lcd, driver.getSmoothedOnRoad(s) * 100 / 128, 4);
  }

  callMe(250);
}

// This is the main driving task. It follows the vehicle in front by controlling speed,
// and starts the driver task (which does steering) and the Dashboard task.
MakeGizmoGardenTaskWithStartStop(SpeedControl)
{
  // If we are still on the road, keep going
  if (driver.isRunning())
  {
    gasPedal();
    callMe(50);
  }
}

// Here are things we have to do to when starting DriveTask
CustomStart(SpeedControl)
{
  proximityMonitor.reset();
  driver.start();
  Dashboard.start();
  showMode = 1;
}

CustomStop(SpeedControl)
{
  driver.stop();
  Dashboard.stop();
  showMode = 0;
}

// ******************
// *                *
// *  Driver Menus  *
// *                *
// ******************

MakeGizmoGardenMenuItem(DriveStiffness)
{
  switch(event)
  {
    case Enter:
      printName();
      break;
      
    case ChangeAndShow:
      driver.setStiffness(driver.getStiffness() + 0.1 * direction);
      ggPrint(lcd, driver.getStiffness(), 4, 2);
      break;
  }
}

MakeGizmoGardenMenuItem(Calibrate)
{
  switch(event)
  {
    case Enter:
      printName();
      break;

    case Select:
      driver.calibrate();
      
    case ChangeAndShow:
      for (int s = 0; s < 2; ++s)
      {
        lcd.setCursor(8 * s, 1);
        ggPrint(lcd, driver.getDark(s), 3);
        lcd.write('-');
        ggPrint(lcd, driver.getRange(s), 3);
      }
      break;
  }
}

MakeGizmoGardenStartStopMenu("Drive", SpeedControl);

// ******************************
// *                            *
// *  Motor Zeroing Menu Items  *
// *                            *
// ******************************

class ZeroMotorMenu : public GizmoGardenMenuItem
{
  GizmoGardenText name;
  GizmoGardenRotatingMotor& motor;
  
protected:
  virtual void action(uint8_t event, int8_t direction, GizmoGardenLCDPrint&);

public:
  ZeroMotorMenu(GizmoGardenText name, GizmoGardenRotatingMotor& motor)
    : name(name), motor(motor)
  {}
};

void ZeroMotorMenu::action(uint8_t event, int8_t direction, GizmoGardenLCDPrint& lcd)
{
  switch(event)
  {
    case Enter:
      lcd.print(name);
      break;

    case ChangeAndShow:
      motor.setZero(motor.getZero() + direction);
      ggPrint(lcd, motor.getZero(), 4);
      break;
  }
}

MakeGizmoGardenText(leftZeroName , "Zero left motor" );
MakeGizmoGardenText(rightZeroName, "Zero right motor");
ZeroMotorMenu leftZero (leftZeroName , leftWheel );
ZeroMotorMenu rightZero(rightZeroName, rightWheel);

