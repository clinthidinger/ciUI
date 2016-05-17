/**********************************************************************************
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#pragma once

#include <string>
#include <sstream>
#include "cinder/gl/gl.h"

template <class T>
std::string ciUIToString(const T& value){
    std::ostringstream out;
	out << value;
	return out.str();
}

template <class T>
std::string ciUIToString(const T& value, int precision){
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
	return out.str();
}

template<typename t>
inline t ciUIMap(t value, t inputMin, t inputMax, t outputMin, t outputMax, bool clamp)
{    
	if (fabs(inputMin - inputMax) < FLT_EPSILON)
    {
		return outputMin;
	}
    else
    {
		float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);        
		if( clamp )
        {
			if(outputMax < outputMin){
				if( outVal < outputMax )outVal = outputMax;
				else if( outVal > outputMin )outVal = outputMin;
			}else{
				if( outVal > outputMax )outVal = outputMax;
				else if( outVal < outputMin )outVal = outputMin;
			}
		}
		return outVal;
	}    
}

inline ci::Rectf ciUICenteredRect(float centerX, float centerY, float width, float height)
{
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;
    return ci::Rectf(centerX - halfWidth, centerY - halfHeight, centerX + halfWidth, centerY + halfHeight);
}

inline void ciUIDrawCenteredRect(float centerX, float centerY, float width, float height, bool doFill)
{
    ci::Rectf rect(ciUICenteredRect(centerX, centerY, width, height));
    
    if(doFill)
    {
        ci::gl::drawSolidRect(rect);
    }
    else
    {
        ci::gl::drawStrokedRect(rect);
    }
}

inline void ciUIDrawCorneredRect(float centerX, float centerY, float width, float height, bool doFill)
{
    ci::Rectf rect(centerX, centerY, centerX + width, centerY + height);
    
    if(doFill)
    {
        ci::gl::drawSolidRect(rect);
    }
    else
    {
        ci::gl::drawStrokedRect(rect);
    }
}

inline void ciUIDrawCenteredTex(const ci::gl::Texture2dRef &tex, float centerX, float centerY, float width, float height)
{
    ci::gl::draw(tex, ciUICenteredRect(centerX, centerY, width, height));
}

inline void ciUIDrawCorneredTex(const ci::gl::Texture2dRef &tex, float cornerX, float cornerY, float width, float height)
{
    ci::gl::draw(tex, ci::Rectf(cornerX, cornerY, cornerX + width, cornerY + height));
}

inline void ciUIDrawLine(float x1, float y1, float x2, float y2)
{
    ci::gl::drawLine(ci::vec2(x1, y1), ci::vec2(x2, y2));
}

inline void ciUICircle(float x, float y, float radius,  bool doFill)
{
    if(doFill)
    {
        ci::gl::drawSolidCircle(ci::vec2(x, y), radius);
    }
    else
    {
        ci::gl::drawStrokedCircle(ci::vec2(x, y), radius);
    }
}
