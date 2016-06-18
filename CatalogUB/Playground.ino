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

// *********************
// *                   *
// *  Light and Sound  *
// *                   *
// *********************

NeoPixelColor colors[] =
{
//  Red Green Blue
  { 128,   0,   0},   // A red
  { 110,  18,   0},   // B red-orange
  {  96,  32,   0},   // C orange
  {  91,  30,   7},   // D peach
  {  78,  25,  25},   // E pink
  {  85,  43,   0},   // F yellow-orange
  {  64,  64,   0},   // G yellow
  {  51,  77,   0},   // H yellow-green
  {   0, 128,   0},   // I green
  {   0,  64,  64},   // J aqua-green
  {  21,  21,  86},   // K sky blue
  {   0,   0, 128},   // L blue
  {  32,   0,  96},   // M violet (purple)
  {  64,   0,  64},   // N magenta
  {  43,  43,  43}    // O white
};

//                 0     1     2     3     4     5     6     7
//                 C     D     E     F     G     A     B     C
int tones[8] = { 1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093 };

// ****************
// *              *
// *  Beep Party  *
// *              *
// ****************

void beepParty()
{

}

// *****************
// *               *
// *  Dance Party  *
// *               *
// *****************

void danceParty()
{
  leftWheel.setSpeed(75);
  rightWheel.setSpeed(75);
  delay(250);
  
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

