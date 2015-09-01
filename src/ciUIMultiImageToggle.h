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
#include "ciUIToggle.h"
#include "ciUIDefines.h"

class ciUIMultiImageToggle : public ciUIToggle
{
public:        
    ciUIMultiImageToggle(float x, float y, float w, float h, bool _value, const std::string &_pathURL, const std::string &_name,  int _size = CI_UI_FONT_SMALL);
    ciUIMultiImageToggle(float w, float h, bool _value, const std::string &_pathURL, const std::string &_name, int _size = CI_UI_FONT_SMALL);
    ciUIMultiImageToggle(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name,  int _size = CI_UI_FONT_SMALL);
    ciUIMultiImageToggle(float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size = CI_UI_FONT_SMALL);
    ~ciUIMultiImageToggle();
    void init(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size = CI_UI_FONT_SMALL);
    void drawBack();
    void drawOutlineHighlight();
    void drawFill();
    void drawFillHighlight();
    virtual void stateChange();
    virtual void setValue(bool _value);
    
protected:    //inherited: ciUIRectangle *rect; ciUIWidget *parent; 
    ci::Image *back;
    ci::Image *over;
    ci::Image *down;
    ci::Image *on;
}; 
