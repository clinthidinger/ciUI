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
#include "cinder/ImageIo.h"
#include "ciUISlider.h"
#include "ciUIRectangle.h"

class ciUIImageSlider : public ciUISlider         ///** I need to simplify this widget to only use one image as the handle of the slider
{
public:    
    ciUIImageSlider(float x, float y, float w, float h, float _min, float _max, float _value, const std::string &_pathURL, const std::string &_name);
    ciUIImageSlider(float w, float h, float _min, float _max, float _value, const std::string &_pathURL, const std::string &_name);
    ciUIImageSlider(float x, float y, float w, float h, float _min, float _max, float *_value, const std::string &_pathURL, const std::string &_name);
    ciUIImageSlider(float w, float h, float _min, float _max, float *_value, const std::string &_pathURL, const std::string &_name);
    ~ciUIImageSlider();
    
    virtual void init(float x, float y, float w, float h, float _min, float _max, float *_value, const std::string &_pathURL, const std::string &_name);
    
    virtual void drawBack();
    virtual void drawOutline();
    virtual void drawOutlineHighlight();
    virtual void drawFill();
    virtual void drawFillHighlight();
    
    virtual void stateChange();
    virtual void input(float x, float y);
	virtual void updateLabel();
    
protected:
    ci::SurfaceRef track;
    ci::SurfaceRef trackleft;
    float tlaspect;
    ci::SurfaceRef trackright;
    float traspect;
    float ratio; 
    
    ci::SurfaceRef progress;
    ci::SurfaceRef progressright;
    ci::SurfaceRef progressleft;
    ci::SurfaceRef handle;
    ci::SurfaceRef handleDown;
    int handleHalfWidth; 
    int handleHalfHeight; 
    ciUIRectangle *imageRect;
}; 
