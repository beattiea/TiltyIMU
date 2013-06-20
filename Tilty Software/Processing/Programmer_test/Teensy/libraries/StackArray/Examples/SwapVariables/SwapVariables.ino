/*
 *  Swapping numbers by using a generic, dynamic stack data structure.
 *
 *  Copyright (C) 2010  Efstathios Chatzikyriakidis (contact@efxa.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// include stack library header.
#include <StackArray.h>

// declare two numbers.
double a = 1.1;
double b = 2.2;

// create a stack of numbers.
StackArray <double> stack;

// startup point entry (runs once).
void
setup () {
  // start serial communication.
  Serial.begin (9600);

  // set the printer of the stack.
  stack.setPrinter (Serial);
}

// loop the main sketch.
void
loop () {
  // print the values of the numbers.
  Serial.print ("a: "); Serial.println (a);
  Serial.print ("b: "); Serial.println (b);

  // push the numbers to the stack.
  stack.push (a);
  stack.push (b);

  // pop the numbers from the stack.
  a = stack.pop ();
  b = stack.pop ();

  // delay 1 second.
  delay (1000);
}
