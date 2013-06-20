/* $Id: SoftPWM.cpp 82 2010-04-21 19:00:46Z bhagman@roguerobotics.com $

  A Software PWM Library
  
  Written by Brett Hagman
  http://www.roguerobotics.com/
  bhagman@roguerobotics.com

  Minor modification by Paul Stoffregen to support different timers

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "SoftPWM.h"
#include "SoftPWM_timer.h"
#include <wiring.h>
#include <pins_arduino.h>

#if F_CPU
#define SOFTPWM_FREQ 60UL
#define SOFTPWM_OCR (F_CPU/(8UL*256UL*SOFTPWM_FREQ))
#else
// 130 == 60 Hz (on 16 MHz part)
#define SOFTPWM_OCR 130
#endif

volatile uint8_t _isr_softcount = 0xff;

typedef struct
{
  // hardware I/O port and pin for this channel
  int8_t pin;
  volatile uint8_t *outport;
  uint8_t pinmask;
  uint8_t pwmvalue;
  uint8_t checkval;
  uint8_t fadeuprate;
  uint8_t fadedownrate;
} softPWMChannel;

softPWMChannel _softpwm_channels[SOFTPWM_MAXCHANNELS];


// Here is the meat and gravy
ISR(SOFTPWM_TIMER_INTERRUPT)
{
  uint8_t i;
  int16_t newvalue;
  int16_t direction;

  if(++_isr_softcount == 0)
  {
    // set all channels high - let's start again
    // and accept new checkvals
    for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
    {
      if (_softpwm_channels[i].fadeuprate > 0 || _softpwm_channels[i].fadedownrate > 0)
      {
        // we want to fade to the new value
        direction = _softpwm_channels[i].pwmvalue - _softpwm_channels[i].checkval;

        // we will default to jumping to the new value
        newvalue = _softpwm_channels[i].pwmvalue;

        if (direction > 0 && _softpwm_channels[i].fadeuprate > 0)
        {
          newvalue = _softpwm_channels[i].checkval + _softpwm_channels[i].fadeuprate;
          if (newvalue > _softpwm_channels[i].pwmvalue)
            newvalue = _softpwm_channels[i].pwmvalue;
        }
        else if (direction < 0 && _softpwm_channels[i].fadedownrate > 0)
        {
          newvalue = _softpwm_channels[i].checkval - _softpwm_channels[i].fadedownrate;
          if (newvalue < _softpwm_channels[i].pwmvalue)
            newvalue = _softpwm_channels[i].pwmvalue;
        }

        _softpwm_channels[i].checkval = newvalue;
      }
      else  // just set the channel to the new value
        _softpwm_channels[i].checkval = _softpwm_channels[i].pwmvalue;

      // now set the pin high (if not 0)
      if (_softpwm_channels[i].checkval > 0)  // don't set if checkval == 0
        *_softpwm_channels[i].outport |= _softpwm_channels[i].pinmask;

    }
  }

  for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
  {
    if (_softpwm_channels[i].pin > 0)  // if it's a valid pin
      if (_softpwm_channels[i].checkval == _isr_softcount)  // if we have hit the width
        *_softpwm_channels[i].outport &= ~(_softpwm_channels[i].pinmask);  // turn off the channel
  }  
}



void SoftPWMBegin(void)
{
  // We can tweak the number of PWM period by changing the prescalar
  // and the OCR - we'll default to ck/8 (CS21 set) and OCR=128.
  // This gives 1024 cycles between interrupts.  And the ISR consumes ~200 cycles, so
  // we are looking at about 20 - 30% of CPU time spent in the ISR.
  // At these settings on a 16 MHz part, we will get a PWM period of
  // approximately 60Hz (~16ms).

  uint8_t i;

  SOFTPWM_TIMER_INIT(SOFTPWM_OCR);

  for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
  {
    _softpwm_channels[i].pin = -1;
    _softpwm_channels[i].fadeuprate = 0;
    _softpwm_channels[i].fadedownrate = 0;
  }
}


void SoftPWMSetPercent(int8_t pin, uint8_t percent, uint8_t hardset)
{
  SoftPWMSet(pin, ((uint16_t)percent * 255) / 100, hardset);
}


void SoftPWMSet(int8_t pin, uint8_t value, uint8_t hardset)
{
  int8_t firstfree = -1;  // first free index
  uint8_t i;

  if (hardset)
  {
    SOFTPWM_TIMER_SET(0);
    _isr_softcount = 0xff;
  }

  // If the pin isn't already set, add it
  for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
  {
    if ((pin < 0 && _softpwm_channels[i].pin > 0) ||  // ALL pins
       (pin > 0 && _softpwm_channels[i].pin == pin))  // individual pin
    {
      // set the pin (and exit, if individual pin)
      _softpwm_channels[i].pwmvalue = value;

      if (pin > 0) // we've set the individual pin
        return;
    }

    // get the first free pin if available
    if (firstfree < 0 && _softpwm_channels[i].pin < 0)
      firstfree = i;
  }

  if (pin > 0 && firstfree >= 0)
  {
    // we have a free pin we can use
    _softpwm_channels[firstfree].pin = pin;
    _softpwm_channels[firstfree].outport = portOutputRegister(digitalPinToPort(pin));
    _softpwm_channels[firstfree].pinmask = digitalPinToBitMask(pin);
    _softpwm_channels[firstfree].pwmvalue = value;
    _softpwm_channels[firstfree].checkval = 0;
    
    // now prepare the pin for output
    digitalWrite(pin, 0);  // turn it off to start (no glitch)
    pinMode(pin, OUTPUT);
  }
}

void SoftPWMEnd(int8_t pin)
{
  uint8_t i;

  for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
  {
    if ((pin < 0 && _softpwm_channels[i].pin > 0) ||  // ALL pins
       (pin > 0 && _softpwm_channels[i].pin == pin))  // individual pin
    {
      // now disable the pin (put it into INPUT mode)
      digitalWrite(_softpwm_channels[i].pin, 1);
      pinMode(_softpwm_channels[i].pin, INPUT);

      // remove the pin
      _softpwm_channels[i].pin = -1;
    }
  }
}


void SoftPWMSetFadeTime(int8_t pin, uint16_t fadeUpTime, uint16_t fadeDownTime)
{
  int16_t fadeAmount;
  uint8_t i;

  for (i = 0; i < SOFTPWM_MAXCHANNELS; i++)
  {
    if ((pin < 0 && _softpwm_channels[i].pin > 0) ||  // ALL pins
       (pin > 0 && _softpwm_channels[i].pin == pin))  // individual pin
    {

      fadeAmount = 0;
      if (fadeUpTime > 0)
        fadeAmount = 255UL * (SOFTPWM_OCR * 256UL / (F_CPU / 8000UL)) / fadeUpTime;

      _softpwm_channels[i].fadeuprate = fadeAmount;

      fadeAmount = 0;
      if (fadeDownTime > 0)
        fadeAmount = 255UL * (SOFTPWM_OCR * 256UL / (F_CPU / 8000UL)) / fadeDownTime;

      _softpwm_channels[i].fadedownrate = fadeAmount;

      if (pin > 0)  // we've set individual pin
        break;
    }
  }
}
