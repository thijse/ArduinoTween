/*
  ease.h - library with easing functions
  Copyright (c) 2019 Thijs Elenbaas.  All right reserved.

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

#include <math.h>

#ifndef PI
#define PI      3.14159265
#define TWO_PI  6.28318530
#endif

class easing
{
	/*-----------------------------
	  EASING FUNCTIONS
-----------------------------*/
// Easings are described at https://easings.net/en
//
//t – time elapsed from startValue of animation
//b – startValue value
//c – value change
//d – duration of animation

public:

#pragma warning( push )
#pragma warning( disable : 4146)
#pragma warning( disable : 4244)


	template <typename Ti, typename To> static To linearEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * t / d + b;
	}

	template <typename Ti, typename To> static To linearEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * t / d + b;
	}

	template <typename Ti, typename To> static To linearEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * t / d + b;
	}

	template <typename Ti, typename To> static To backEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		float s = 1.70158f;
		float postFix = t /= d;
		return c * (postFix)*t*((s + 1)*t - s) + b;
	}

	template <typename Ti, typename To> static To backEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		float s = 1.70158f;
		return c * ((t = t / d - 1)*t*((s + 1)*t + s) + 1) + b;
	}

	template <typename Ti, typename To> static To backEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		float s = 1.70158f;
		if ((t /= d / 2) < 1) return c / 2 * (t*t*(((s *= (1.525f)) + 1)*t - s)) + b;
		float postFix = t -= 2;
		return c / 2 * ((postFix)*t*(((s *= (1.525f)) + 1)*t + s) + 2) + b;
	}

	template <typename Ti, typename To> static To bounceEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if ((t /= d) < (1 / 2.75f)) {
			return c * (7.5625f*t*t) + b;
		}
		else if (t < (2 / 2.75f)) {
			float postFix = t -= (1.5f / 2.75f);
			return c * (7.5625f*(postFix)*t + .75f) + b;
		}
		else if (t < (2.5 / 2.75)) {
			float postFix = t -= (2.25f / 2.75f);
			return c * (7.5625f*(postFix)*t + .9375f) + b;
		}
		else {
			float postFix = t -= (2.625f / 2.75f);
			return c * (7.5625f*(postFix)*t + .984375f) + b;
		}
	}

	template <typename Ti, typename To> static To bounceEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c - bounceEaseOut<Ti, To>(d - t, 0, c, d) + b;
	}

	template <typename Ti, typename To> static To bounceEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if (t < d / 2) return bounceEaseIn<Ti, To>(t * 2, 0, c, d) * .5f + b;
		else return bounceEaseOut<Ti, To>(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
	}

	template <typename Ti, typename To> static To circEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return -c * (sqrt(1 - (t /= d)*t) - 1) + b;
	}

	template <typename Ti, typename To> static To circEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * sqrt(1 - (t = t / d - 1)*t) + b;
	}

	template <typename Ti, typename To> static To circEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t * t) - 1) + b;
		return c / 2 * (sqrt(1 - t * (t -= 2)) + 1) + b;
	}

	template <typename Ti, typename To> static To cubicEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * (t /= d)*t*t + b;
	}

	template <typename Ti, typename To> static To cubicEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * ((t = t / d - 1)*t*t + 1) + b;
	}

	template <typename Ti, typename To> static To cubicEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if ((t /= d / 2) < 1) return c / 2 * t*t*t + b;
		return c / 2 * ((t -= 2)*t*t + 2) + b;
	}

	template <typename Ti, typename To> static To elasticEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if (t == 0) return b;  if ((t /= d) == 1) return b + c;
		float p = d * .3f;
		float a = c;
		float s = p / 4;
		float postFix = a * pow(2, 10 * (t -= 1)); // this is a fix, again, with post-increment operators
		return -(postFix * sin((t*d - s)*(TWO_PI) / p)) + b;
	}

	template <typename Ti, typename To> static To elasticEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if (t == 0) return b;  if ((t /= d) == 1) return b + c;
		float p = d * .3f;
		float a = c;
		float s = p / 4;
		return (a*pow(2, -10 * t) * sin((t*d - s)*(TWO_PI) / p) + c + b);
	}

	template <typename Ti, typename To> static To elasticEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if (t == 0) return b;  if ((t /= d / 2) == 2) return b + c;
		float p = d * (.3f*1.5f);
		float a = c;
		float s = p / 4;

		if (t < 1) {
			float postFix = a * pow(2, 10 * (t -= 1)); // postIncrement is evil
			return -.5f*(postFix* sin((t*d - s)*(TWO_PI) / p)) + b;
		}
		float postFix = a * pow(2, -10 * (t -= 1)); // postIncrement is evil
		return postFix * sin((t*d - s)*(TWO_PI) / p)*.5f + c + b;
	}

	template <typename Ti, typename To> static To elasticEaseInFast(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if (t == 0) return b;  if ((t /= d) == 1) return b + c;
		float p = d * .3f;
		float a = c;
		float s = p / 4;
		float postFix = a * pow(2, 10 * (t -= 1)); // this is a fix, again, with post-increment operators
		return -(postFix * sin16F((t*d - s)*(TWO_PI) / p)) + b;
	}

	template <typename Ti, typename To> static To elasticEaseOutFast(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if (t == 0) return b;  if ((t /= d) == 1) return b + c;
		float p = d * .3f;
		float a = c;
		float s = p / 4;
		return (a*pow(2, -10 * t) * sin16F((t*d - s)*(TWO_PI) / p) + c + b);
	}

	template <typename Ti, typename To> static To elasticEaseInOutFast(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if (t == 0) return b;  if ((t /= d / 2) == 2) return b + c;
		float p = d * (.3f*1.5f);
		float a = c;
		float s = p / 4;

		if (t < 1) {
			float postFix = a * pow(2, 10 * (t -= 1)); // postIncrement is evil
			return -.5f*(postFix* sin16F((t*d - s)*(TWO_PI) / p)) + b;
		}
		float postFix = a * pow(2, -10 * (t -= 1)); // postIncrement is evil
		return postFix * sin16F((t*d - s)*(TWO_PI) / p)*.5f + c + b;
	}

	template <typename Ti, typename To> static To expoEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
	}

	template <typename Ti, typename To> static To expoEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
	}

	template <typename Ti, typename To> static To expoEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if (t == 0) return b;
		if (t == d) return b + c;
		if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
		return c / 2 * (-pow(2, -10 * --t) + 2) + b;
	}

	template <typename Ti, typename To> static To quadEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * (t /= d)*t + b;
	}

	template <typename Ti, typename To> static To quadEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return -c * (t /= d)*(t - 2) + b;
	}

	template <typename Ti, typename To> static To quadEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if ((t /= d / 2) < 1) return ((c / 2)*(t*t)) + b;
		return -c / 2 * (((t - 2)*(--t)) - 1) + b;
	}

	template <typename Ti, typename To> static To quartEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * (t /= d)*t*t*t + b;
	}

	template <typename Ti, typename To> static To quartEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return -c * ((t = t / d - 1)*t*t*t - 1) + b;
	}

	template <typename Ti, typename To> static To quartEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if ((t /= d / 2) < 1) return c / 2 * t*t*t*t + b;
		return -c / 2 * ((t -= 2)*t*t*t - 2) + b;
	}

	template <typename Ti, typename To> static To quintEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * (t /= d)*t*t*t*t + b;
	}
	template <typename Ti, typename To> static To quintEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * ((t = t / d - 1)*t*t*t*t + 1) + b;
	}

	template <typename Ti, typename To> static To quintEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		if ((t /= d / 2) < 1) return c / 2 * t*t*t*t*t + b;
		return c / 2 * ((t -= 2)*t*t*t*t + 2) + b;
	}

	template <typename Ti, typename To> static To sineEaseIn(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return -c * cos(t / d * (PI / 2)) + c + b;
	}

	template <typename Ti, typename To> static To sineEaseOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return c * sin(t / d * (PI / 2)) + b;
	}

	template <typename Ti, typename To> static To sineEaseInOut(Ti tin, To b, To c, Ti d) {
		float t = float(tin);
		return -c / 2 * (cos(PI*t / d) - 1) + b;
	}

};