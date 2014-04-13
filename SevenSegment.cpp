/*
 * Author:		Obeahon Okaiwele
 * Purpose: 	A library to control a 7-segment display
 * Created: 	September 29, 2012
 *
 * Edited:		November 06, 2012 by Obeahon Okaiwele
 * Purpose:		Added _sevenSeg[15][7] and convert()
 *				Added _isAnode and setIsAnode()	
 */

#include "Arduino.h"
#include "SevenSegment.h"

int _value;					// current value displayed
int _lowerLimit;
int _upperLimit;
boolean _countDirection;		// true = count UP
int _pins[7];					
int _isAnode;

const char SevenSegment::_sevenSeg[16][7] = 
	{	{ '1', '1', '1', '1', '1', '1', '0' },
		{ '0', '1', '1', '0', '0', '0', '0' },
		{ '1', '1', '0', '1', '1', '0', '1' },
		{ '1', '1', '1', '1', '0', '0', '1' },
		{ '0', '1', '1', '0', '0', '1', '1' },
		{ '1', '0', '1', '1', '0', '1', '1' },
		{ '1', '0', '1', '1', '1', '1', '1' },
		{ '1', '1', '1', '0', '0', '0', '0' },
		{ '1', '1', '1', '1', '1', '1', '1' }, 
		{ '1', '1', '1', '1', '0', '1', '1' },
		{ '1', '1', '1', '0', '1', '1', '1' },
		{ '0', '0', '1', '1', '1', '1', '1' },
		{ '1', '0', '0', '1', '1', '1', '0' },
		{ '0', '1', '1', '1', '1', '0', '1' },
		{ '1', '0', '0', '0', '1', '1', '1' },
		{ '0', '0', '0', '0', '0', '0', '0' }
	};

SevenSegment::SevenSegment(int pins[7]) {
	//SevenSegment(pins, countDirection, -1);
	for (int i = 0; i < 7; i++) {
		_pins[i] = pins[i];
		pinMode(_pins[i], OUTPUT);
	}
	
	_value = -1;			// current value displayed
	_lowerLimit = 0;
	_upperLimit = 15;
	_countDirection = true;	// true = count UP
	_isAnode = false;
}

void SevenSegment::show(int num) {
	for (int i = 0; i < 7; i++) {
		int val = convert(_sevenSeg[num][i] );
		if (val == 1) { digitalWrite( _pins[i], LOW ); }
		else { digitalWrite( _pins[i], HIGH ); }
	}
}

int SevenSegment::currentValue() {
	return _value; 
}

boolean SevenSegment::countDirection() {
	return _countDirection;
}

void SevenSegment::reverseCountDirection() {
	if (_countDirection == false) {
		_countDirection = true;
	} else {
		_countDirection = false;
	}
}

int SevenSegment::next() {
	if ( _countDirection) {  
		_value++;
		Serial.println(_value);
		if (_value > _upperLimit) { _value = _lowerLimit; }
	}
	else {
		_value--;
		if (_value < _lowerLimit) { _value = _upperLimit; }
	}
	return _value;
}

void SevenSegment::setValue(int value) {
	_value = value;
}

int SevenSegment::getValue() {
	return _value;
}

void SevenSegment::setLimits(int lowerLimit, int upperLimit) {
	_lowerLimit = lowerLimit;
	_upperLimit = upperLimit;
}

int SevenSegment::convert(char value) {
	if (_isAnode) {
		if (value == '1') { return 0; }
		else { return 1; }
	} else {
		if (value == '1') { return 1; }
		else { return 0; }
	}
}

void SevenSegment::setIsAnode(boolean isAnode) {
	_isAnode = isAnode;
}
