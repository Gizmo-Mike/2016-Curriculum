// *****************************
// *                           *
// *  8x8 NeoPixel Light Show  *
// *                           *
// *****************************

// orientation          flipX  flipY  exchange
// 0 (as is)              0      0     false
// 1 (rotate 90)          7      0     true
// 2 (rotate 180)         7      7     false
// 3 (rotate 270)         0      7     true
// 4 (flip horizontal)    7      0     false
// 5 (flip vertical)      0      7     false
// 6 (flip diagonal 1)    0      0     true
// 7 (flip diagonal 2)    7      7     true

const byte flipXTable[8] PROGMEM = { 0, 7, 7, 0, 7, 0, 0, 7};
const byte flipYTable[8] PROGMEM = { 0, 0, 7, 7, 0, 7, 0, 7};
const bool exgXYTable[8] PROGMEM = { false, true, false, true, false, false, true, true};

enum { MaxEnergy = 2500 };

void lightShow(GizmoGardenText pattern, NeoPixelColor* palette, byte brightness,
               byte orientation, char xPosition, char yPosition)
{
  lights.clear();
  lights.setBrightness(255);
  
  uint16_t energy = 0;
  byte x = 0, y = 0;

  byte flipX      = pgm_read_byte(&flipXTable[orientation]);
  byte flipY      = pgm_read_byte(&flipYTable[orientation]);
  bool exchangeXY = pgm_read_byte(&exgXYTable[orientation]);
  
  while (*pattern)
  {
    byte c = *pattern++;
    if (c == ' ')
      continue;
    bool endOfRow = c == ';';
    if (isLowerCase(c))
      c -= 'a';
    else
      c -= 'A';
    
    if (c < 24)
    {
      byte u = x ^ flipX;
      byte v = y ^ flipY;
      if (exchangeXY)
      {
        u ^= v;
        v ^= u;
        u ^= v;
      }
      u += xPosition;
      v += yPosition;
      NeoPixelColor color = palette[c];
      energy += color.energy();
      if ((u | v) < 8)
        // Adjust u & v for physical orientation of display in platform
        lights.setPixelColor(((u << 3) + (v ^ 7)), color);
    }

    if (++x == 8 || endOfRow)
    {
      x = 0;
      if (++y == 8)
        break;
    }
  }

  byte bright = brightness * 255u / 100u;
  if (energy > MaxEnergy)
    bright = min(bright, (byte)(255ul * MaxEnergy / energy));
  lights.setBrightness(bright);
  lights.show();
}

void lightsOff()
{
  lights.clear();
  lights.show();
}

// Make the color mixer menu
GizmoGardenColorMixer mixer(lights);

