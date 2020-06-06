/*
  Tween.h - library to perform tween animations
  Copyright (c) 2019, 2020 Thijs Elenbaas.  All right reserved.

  Permission is hereby granted, free of charge, to any person 
  obtaining a copy of this software and associated documentation 
  files (the "Software"), to deal in the Software without restriction,
  including without limitation the rights to use, copy, modify, merge, 
  publish, distribute, sublicense, and/or sell copies of the Software, 
  and to permit persons to whom the Software is furnished to do so, 
  subject to the following conditions:

  The above copyright notice and this permission notice shall be 
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
   ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
   TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
   PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
   SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR 
   ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
   OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "ease.h"


// todo: add relative position

#define Ease(EASEMETHOD)  EASEMETHOD ## EaseIn, EASEMETHOD ## EaseOut, EASEMETHOD ## EaseInOut

enum easingType {
	Ease(Linear),
	Ease(Back),
	Ease(Bounce),
	Ease(Circ),
	Ease(Cubic),
	Ease(Elastic),
	Ease(Expo),
	Ease(Quad),
	Ease(Quart),
	Ease(Quint),
	Ease(Sine)
};

template <class Tin, class Tout> class Tween
{

public:
	typedef void(*onUpdateCallback)(Tin, Tout);

private:
	enum state {
		started,
		firstPos,
		intermediatePos,
		lastPos,
		stopped,
	};

	Tout val, startValue, endValue, prevValue;                            		// actual, origin and destination values
	Tin duration, stepSize, pos, startPos, prevPos;
	bool useTime;
	bool filterSteps;
	Tout  minIncrement;
	bool filterIncrement;
	//bool started;
	state runState;
	easingType easeMode;
	onUpdateCallback onUpdateCallbackFunction;
	void init() {
		startValue   = 0;
		endValue     = 1;
		duration     = 1;
		startPos     = 0;
		stepSize     = 0;
		filterSteps  = false;
		useTime      = false;
		runState    = stopped;
	}

public:

	/*-----------------------------
	           TWEEN
    -----------------------------*/

private:
	void calcValue() {
		switch (easeMode) {
			default:
		case LinearEaseIn:         { val = easing::linearEaseIn    <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case LinearEaseOut:    { val = easing::linearEaseOut   <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case LinearEaseInOut:  { val = easing::linearEaseInOut <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case BackEaseIn:       { val = easing::backEaseIn      <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case BackEaseOut:      { val = easing::backEaseOut     <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case BackEaseInOut:    { val = easing::backEaseInOut   <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case BounceEaseIn:     { val = easing::bounceEaseIn    <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case BounceEaseOut:    { val = easing::bounceEaseOut   <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case BounceEaseInOut:  { val = easing::bounceEaseInOut <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case CircEaseIn:       { val = easing::circEaseIn      <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case CircEaseOut:      { val = easing::circEaseOut     <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case CircEaseInOut:    { val = easing::circEaseInOut   <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case CubicEaseIn:      { val = easing::cubicEaseIn     <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case CubicEaseOut:     { val = easing::cubicEaseOut    <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case CubicEaseInOut:   { val = easing::cubicEaseInOut  <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case ElasticEaseIn:    { val = easing::elasticEaseIn   <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case ElasticEaseOut:   { val = easing::elasticEaseOut  <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case ElasticEaseInOut: { val = easing::elasticEaseInOut<Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case ExpoEaseIn:       { val = easing::expoEaseIn      <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case ExpoEaseOut:      { val = easing::expoEaseOut     <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case ExpoEaseInOut:    { val = easing::expoEaseInOut   <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case QuadEaseIn:       { val = easing::quadEaseIn      <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case QuadEaseOut:      { val = easing::quadEaseOut     <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case QuadEaseInOut:    { val = easing::quadEaseInOut   <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case QuartEaseIn:      { val = easing::quartEaseIn     <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case QuartEaseOut:     { val = easing::quartEaseOut    <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case QuartEaseInOut:   { val = easing::quartEaseInOut  <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case QuintEaseIn:      { val = easing::quintEaseIn     <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case QuintEaseOut:     { val = easing::quintEaseOut    <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case QuintEaseInOut:   { val = easing::quintEaseInOut  <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case SineEaseIn:       { val = easing::sineEaseIn      <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case SineEaseOut:      { val = easing::sineEaseOut     <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
			case SineEaseInOut:    { val = easing::sineEaseInOut   <Tin,Tout>(pos-startPos,startValue,endValue-startValue,duration); break; }
		}
	}


	void invokeCallback()
	{
		if (onUpdateCallbackFunction != nullptr) onUpdateCallbackFunction(pos,val);
	}
public:

	Tween() {
		init();
	}

	Tout value() {
		return val;
	}

	Tween& from(Tout value) {
		startValue = value;
		return *this;
	}

	Tween& to(Tout value) {
		endValue = value;
		return *this;
	}

	Tween& during(Tin value) {
		duration = value;
		return *this;
	}

	Tween& duringMsec(Tin value) {
		useTime = true;
		duration = value;
		return *this;
	}

	Tween& duringSec   (Tin value) { return duringMsec(                     1000 * value); }
	Tween& duringMin   (Tin value) { return duringMsec(                60 * 1000 * value); }	
	Tween& duringHour  (Tin value) { return duringMsec(           60 * 60 * 1000 * value); }
	Tween& duringDay   (Tin value) { return duringMsec(      24 * 60 * 60 * 1000 * value); }
	Tween& duringWeek  (Tin value) { return duringMsec(  7 * 24 * 60 * 60 * 1000 * value); }


	Tween& step(Tin value) {
		stepSize = value;
		filterSteps = true;
		return *this;
	}

	Tween& stepMsec(Tin value) {
		useTime     = true;
		stepSize    = value;
		filterSteps = true;
		return *this;
	}

	Tween& stepSec   (Tin value) { return stepMsec(                     1000 * value); }
	Tween& stepMin   (Tin value) { return stepMsec(                60 * 1000 * value); }	
	Tween& stepHour  (Tin value) { return stepMsec(           60 * 60 * 1000 * value); }
	Tween& stepDay   (Tin value) { return stepMsec(      24 * 60 * 60 * 1000 * value); }
	Tween& stepWeek  (Tin value) { return stepMsec(  7 * 24 * 60 * 60 * 1000 * value); }

	Tween& increment(Tout value) {
		minIncrement   = value;
		filterIncrement = true;
		return *this;
	}

	Tween& easing(easingType value) {
		easeMode = value;
		return *this;
	}

	Tween& onUpdate(onUpdateCallback value) {
		onUpdateCallbackFunction = value;
		return *this;
	}

	Tween& start() {
		runState = state::started;
		//started = true;
		if (useTime) { 
			startPos = Tin(millis());
		} else {
			startPos = 0;
		}
		pos = 0;
		return *this;
	}

	Tween& startAt(Tin value) {
		runState = state::started;
		startPos = value;
		pos      = 0;
		return *this;
	}

	Tween& stop() {
		runState = state::stopped;
		return *this;
	}

	bool isAnimating()
	{
		return runState != state::stopped;
	}

	bool update() {
		return seek(pos);
	}

	bool update(Tin value) {
		return seek(pos+value);
	}

	bool seek(Tin value) {
		// todo: allow for time overload

		if (runState == state::stopped)   { return false;          }
		if (useTime)                      { value = Tin(millis()); }
		if (value < startPos)             { return false;          }				
		if (value > startPos + duration)  { runState = state::stopped;  return false; }

		pos     = value;
		
		if (value == startPos)                                                                      { val = startValue; prevPos = pos; prevValue = val; invokeCallback(); return true;  }
		if (value == startPos + duration)                                                           { val = endValue  ; prevPos = pos; prevValue = val; invokeCallback(); return true;  }

		calcValue();
		if (filterSteps     && ((pos -prevPos   )*(pos - prevPos  ) < stepSize * stepSize))         { return false; }
		prevPos = pos;
		if (filterIncrement && ((val - prevValue)*(val - prevValue) < minIncrement * minIncrement)) { return false; }
		prevValue = val;
		invokeCallback();
		return true;
	}

	Tin position() const
	{
		return pos;
	}

#pragma warning(pop)

};

#define TweenTime(Tout) Tween <unsigned long, Tout>

/*-----------------------------
     EXPLICIT DECLARATION
  -----------------------------*/

template class Tween<unsigned char,char>;
template class Tween<unsigned char, unsigned char>;
template class Tween<unsigned int, int>;
template class Tween<unsigned int, unsigned int>;
template class Tween<unsigned long, long>;
template class Tween<unsigned long, unsigned long>;
template class Tween<unsigned long, float>;
template class Tween<float, unsigned long>;
template class Tween<unsigned long, double>;
template class Tween<float, float>;
template class Tween<double, double>;
