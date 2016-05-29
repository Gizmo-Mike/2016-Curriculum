
extern NeoPixelColor colors[];
extern int tones[8];

MakeGizmoGardenText(testPattern,
". . A A I I . ."
". G . . . . B ."
"A . G . . B . I"
"A . . G B . . I"
"C . . J K . . E"
"C . J . . K . E"
". J . . . . K ."
". . C C E E . .");

MakeGizmoGardenText(happy,
". . L L L L . ."
". L . . . . L ."
"A . G . . M . A"
"A . . . . . . A"
"A . I . . I . A"
"A . . I I . . A"
". A . . . . A ."
". . A A A A . .");

void happyShow()
{
  // Move happy face left to right while playing musical scale
  for (int i = 0; i < 8; ++i)
  {
    lightShow(happy, colors, 100, 0, i - 7, 0);
    GizmoGardenTone(tones[i], 100);
    delay(250);
  }
  delay(750);
  
  // Move upside-down happy face top to bottom while playing
  // musical scale backwards
  for (int i = 0; i < 8; ++i)
  {
    lightShow(happy, colors, 100, 2, 0, i);
    GizmoGardenTone(tones[7 - i], 100);
    delay(250);
  }
  lightsOff();
}

MakeGizmoGardenText(tinyHeart,
". A . A .;"
"A E A E A;"
"A E E E A;"
". A E A .;"
". . A . .;");

MakeGizmoGardenText(smallHeart,
". E . . E .;"
"E K E E K E;"
"E K K K K E;"
". E K K E .;"
". . E E . .;");

MakeGizmoGardenText(bigHeart,
". A A . . A A ."
"A L L A A L L A"
"A L . L L . L A"
"A L . . . . L A"
". A L . . L A ."
". . A L L A . ."
". . . A A . . .");

void beatingHeart(int beats)
{
  for (int i = 0; i < beats; ++i)
  {
    lightShow(smallHeart, colors, 50, 0, 1, 1);
    GizmoGardenTone(500);
    delay(200);

    lightShow(bigHeart, colors, 100, 0, 0, 0);
    GizmoGardenTone(1000, 200);
    delay(500);
  }
}

