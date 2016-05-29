// **********************
// *                    *
// *  Gizmo Playground  *
// *                    *
// **********************

// *********************
// *                   *
// *  Welcome Message  *
// *                   *
// *********************

// The Gizmo Garden dashboard is a liquid crystal display (LCD) containing 2 rows of 16
// characters each. To print a welcome message on the dashboard, you decide:
// 
//          1) What characters to print.
//          2) Where to print them.
//          3) How long the message will stay up before the menu takes over.
// 
// The 2 rows and 16 columns are numbered like this:
// 
//                                     Column
//          0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
//        -----------------------------------------------------------------
//     0  |   |   |   |   | W | e | l | c | o | m | e | ! |   |   |   |   |
//  R     |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
//  O      ----------------------------------------------------------------
//  W  1  |   |   | G | i | z | m | o |   | G | a | r | d | e | n |   |   |
//        |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
//        -----------------------------------------------------------------

void welcome()
{
  lcd.setCursor(4, 0);
  lcd.print(F("Welcome!"));
  lcd.setCursor(2, 1);
  lcd.print(F("Gizmo Garden"));
  delay(2000);
}

// ****************
// *              *
// *  Beep Party  *
// *              *
// ****************

NeoPixelColor colors[] =
{
//  Red Green Blue
  { 128,   0,   0},   // A red
  {  96,  32,   0},   // B orange
  {  64,  64,   0},   // C yellow
  {  32,  96,   0},   // D lime
  {   0, 128,   0},   // E green
  {   0,  96,  32},   // F
  {   0,  64,  64},   // G cyan
  {   0,  32,  96},   // H
  {   0,   0, 128},   // I blue
  {  32,   0,  96},   // J purple
  {  64,   0,  64},   // K magenta
  {  96,   0,  32}    // L
};

MakeGizmoGardenText(smilyFace,
". . A A I I . ."
". G . . . . B ."
"A . G . . B . I"
"A . . G B . . I"
"C . . J K . . E"
"C . J . . K . E"
". J . . . . K ."
". . C C E E . .");

int tones[] = {  1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093 };

void beepParty()
{
  for (int x = 0; x < 8; ++x)
  {
    lightShow(smilyFace, colors, 10 * x + 10, 0, x - 7, 0);
    GizmoGardenTone(tones[x]);
    delay(250);
  }
  for (int i = 1; i < 8; ++i)
  {
    lightShow(smilyFace, colors, 100, i, 0, 0);
    GizmoGardenTone(tones[6]);
    delay(100);
    GizmoGardenTone(tones[7], 100);
    delay(900);
  }
  for (int xy = 0; xy < 8; ++xy)
  {
    lightShow(smilyFace, colors, 80 - 10 * xy, 0, xy, xy);
    GizmoGardenTone(tones[7 - xy]);
    delay(250);
  }

  lights.clear();
  lights.show();
  GizmoGardenTone(0);
}

// *****************
// *               *
// *  Dance Party  *
// *               *
// *****************

void danceParty()
{
  leftWheel.setSpeed(40);
  rightWheel.setSpeed(-40);
  delay(5000);
  
  leftWheel.setSpeed(0);
  rightWheel.setSpeed(0);
}

// ***************************
// *                         *
// *  Playground Menu Items  *
// *                         *
// ***************************

MakeGizmoGardenMenuItem(BeepParty)
{
  switch(event)
  {
    case Enter:
      printName();
      break;

    case Select:
      showMode = -1;
      break;
  }
}

MakeGizmoGardenMenuItem(DanceParty)
{
  switch(event)
  {
    case Enter:
      printName();
      break;

    case Select:
      danceParty();
      break;
  }
}

