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
#include "ciUIWrapper.h"
#include "ciUISlider.h"
#include "ciUIWidget.h"
#include "ciUIButton.h"
#include "ciUIRadio.h"
#include "ciUIToggle.h"

class ciUICanvas;

class ciUIEventArgs 
{   
public:
	ciUIEventArgs();
    ciUIEventArgs(ciUIWidget *_widget);
    ciUIButton *getButton();
    ciUIRadio  *getRadio();
    ciUIToggle *getToggle();
    ciUISlider *getSlider();

    bool isName(const std::string &_name) const;
    bool getBool();
    float getFloat();
    double getDouble();
    int getInt();
    
    ciUICanvas *getCanvasParent();
    ciUIWidget *getParent();

    const std::string &getName() const;
    std::string getParentName() const;
    std::string getCanvasParentName() const;
    
    int getKind();
    
    ciUIWidget *widget;
}; 
