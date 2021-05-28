#ifndef SOLID_COLOR_RAINBOW_MODE_H_
#define SOLID_COLOR_RAINBOW_MODE_H_

int colorCounterRainbow = 0;
boolean isChange = false;

void ChangeRainbowColorPeriodically()
{
if( colorCounterRainbow == 0) { fill_solid( leds, NUM_LEDS, CHSV(0, 255, 192));}
if( colorCounterRainbow == 1) { fill_solid( leds, NUM_LEDS, CHSV(32, 255, 255));}
if( colorCounterRainbow == 2) { fill_solid( leds, NUM_LEDS, CHSV(64, 255, 255));}
if( colorCounterRainbow == 3) { fill_solid( leds, NUM_LEDS, CHSV(96, 255, 255));}
if( colorCounterRainbow == 4) { fill_solid( leds, NUM_LEDS, CHSV(138, 255, 255));}
if( colorCounterRainbow == 5) { fill_solid( leds, NUM_LEDS, CHSV(160, 255, 255));}
if( colorCounterRainbow == 6) { fill_solid( leds, NUM_LEDS, CHSV(180, 255, 255));}
if( colorCounterRainbow == 7) { fill_solid( leds, NUM_LEDS, CHSV(214, 255, 255));}
}

#endif /* SOLID_COLOR_RAINBOW_MODE_H_ */
