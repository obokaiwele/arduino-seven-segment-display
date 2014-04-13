/*
 * Author:	Obeahon Okaiwele
 * Date: 	September 29, 2012 
 * Purpose: A library to control a 7-segment display
 *
 * Edited:		November 06, 2012 by Obeahon Okaiwele
 * Purpose:		Added _sevenSeg[15][7] and convert()
 *				Added _isAnode and setIsAnode()	
 */
#ifndef SevenSegment_h
#define SevenSegment_h

#include "Arduino.h"

class SevenSegment
{
  public:
    SevenSegment(int pins[7]);
    void show(int num);
    int currentValue();
    void reverseCountDirection();
    int next();
	void setValue(int value);
	int getValue();
	void setLimits(int lowerLimit, int upperLimit);
	boolean countDirection();
	int convert(char num);
	void setIsAnode(boolean isAnode);

  private:
	const static char _sevenSeg[16][7];
    int _pins[7];
    int _value;
	int _lowerLimit;
	int _upperLimit;
	int _isAnode;
    boolean _countDirection;  
};

#endif
