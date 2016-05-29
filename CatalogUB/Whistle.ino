// ********************************************
// *                                          *
// *  Musical Whistle Using Proximity Sensor  *
// *                                          *
// ********************************************

// A computer pretends to do many things at once by switching rapidly
// among various tasks. This is called "multitasking". Here we create
// a task that makes the piezo buzzer whistle at a pitch controlled
// by the proximity sensor. Tasks shares the computer by taking turns
// doing what they need to do. In the Gizmo Garden system, we create
// a task by saying what we want to happen when it's that task's turn
// to use the computer. We also give the task a name, here "WhistleTask".
MakeGizmoGardenTaskWithStop(WhistleTask)
{
  // Compute a pitch from the proximity sensor, and start whistling
  int pitch = 4 * readProximitySensor() + 500;
  GizmoGardenTone(pitch);

  // Show the pitch on the dashboard
  lcd.setCursor(6, 1);
  ggPrint(lcd, pitch, 4);

  // Ask for another turn to use the computer in 100 milliseconds.
  callMe(100);
}

// When WhistleTask stops for any reason, turn off the piezo buzzer.
CustomStop(WhistleTask)
{
  GizmoGardenTone(0);
}

// Make a dashboard menu item that can start and stop WhistleTask.
MakeGizmoGardenStartStopMenu("Whistle", WhistleTask);

