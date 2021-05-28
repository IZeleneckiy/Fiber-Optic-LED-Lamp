#include <FastLED.h>
#include <PinButton.h>
#include <EEPROM.h>

// define the LEDs
#define LED_PIN D3  //pin the LEDs are connected to
#define NUM_LEDS 32
#define BRIGHTNESS 255 //maximum brightness
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
struct CRGB leds[NUM_LEDS];
#define UPDATES_PER_SECOND 100

#include "solid_color_mode.h"
#include "solid_color_rainbow_mode.h"
#include "palette_mode.h"
#include "effect_mode.h"

const int wakeUpPin = D4;
PinButton FunctionButton(wakeUpPin);
int setMode = 1;
boolean isWakeUp = true;

void setup() {
	delay(1500); // power-up safety delay
	Serial.begin(115200);
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
	FastLED.setBrightness(BRIGHTNESS);
	FastLED.clear();
	Serial.print("fastled started");
  EEPROM.begin(512);
//  EEPROM.write(0, setMode);        // at first run uncomment this for lines for initializing the eeprom data
//  EEPROM.write(1, colorCounter);
//  EEPROM.write(2, paletteCounter);
//  EEPROM.write(3, gCurrentPatternNumber);
//  EEPROM.commit(); 
	setMode = EEPROM.read(0);
	colorCounter = EEPROM.read(1);
	paletteCounter = EEPROM.read(2);
	gCurrentPatternNumber = EEPROM.read(3);
}

void loop() {
	FunctionButton.update();

	if (FunctionButton.isSingleClick()) {
		if (setMode == 0) {
			colorCounter++;
			if (colorCounter > 17) {
				colorCounter = 0;
			}
		}
		else if (setMode == 1) {
			paletteCounter++;
			if (paletteCounter > 11) { // adjust if you have more or less than 34 palettes
				paletteCounter = 0;
			}
		}
		else if (setMode == 2) {
			nextPattern();  // Change to the next pattern
		}
    else if (setMode == 3) {
      colorCounterRainbow = 0;
    }
	}
	else if (FunctionButton.isDoubleClick()) {
		setMode++;
		if (setMode > 3 && isWakeUp) {
			setMode = 0;
		}
	}
	else if (FunctionButton.isLongClick()) {
    if (isWakeUp) {
      FastLED.clear();
      FastLED.show();
      EEPROM.write(0, setMode);
      EEPROM.write(1, colorCounter);
      EEPROM.write(2, paletteCounter);
      EEPROM.write(3, gCurrentPatternNumber);
      EEPROM.commit();
      isWakeUp = false;
      setMode = 4;
    } else {
      setMode = EEPROM.read(0);
      colorCounter = EEPROM.read(1);
      paletteCounter = EEPROM.read(2);
      gCurrentPatternNumber = EEPROM.read(3);
      isWakeUp = true;
    }
	}

	if (setMode == 0) {
		if (colorCounter % 2 == 0) {
		float breath = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
		FastLED.setBrightness(breath);
		}
		else {
			FastLED.setBrightness(BRIGHTNESS);
		}
		ChangeColorPeriodically();
	}
	else if (setMode == 1) {
		FastLED.setBrightness(BRIGHTNESS);
		ChangePalettePeriodically();
		static uint8_t startIndex = 0;
		startIndex = startIndex + 1;
		FillLEDsFromPaletteColors(startIndex);
	}
	else if (setMode == 2) {
		gPatterns[gCurrentPatternNumber]();
	}
  else if (setMode == 3) {
    float breath = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
    FastLED.setBrightness(breath);
    ChangeRainbowColorPeriodically();
    if (breath < 0.01 && isChange) {
      colorCounterRainbow++;
      isChange = false;
      if (colorCounterRainbow > 7) {
        colorCounterRainbow = 0;
      }
    }
    else if (breath > 250) {
      isChange = true;
    }
  }

	FastLED.show();
	FastLED.delay(2000 / UPDATES_PER_SECOND);
	EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
}