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

#include "ciUIEventArgs.h"
#include "ciUIWidget.h"

ciUIEventArgs::ciUIEventArgs()
{
    widget = nullptr;
}

ciUIEventArgs::ciUIEventArgs(ciUIWidget *_widget)
{
    widget = _widget;
}

ciUIButton *ciUIEventArgs::getButton()
{
    return (ciUIButton *) widget;
}

ciUIRadio *ciUIEventArgs::getRadio()
{
    return (ciUIRadio *) widget;
}

ciUIToggle *ciUIEventArgs::getToggle()
{
    return (ciUIToggle *) widget;
}

ciUISlider *ciUIEventArgs::getSlider()
{
    return (ciUISlider *) widget;
}

ciUICanvas *ciUIEventArgs::getCanvasParent()
{
    return (ciUICanvas *) widget->getCanvasParent();
}

ciUIWidget *ciUIEventArgs::getParent()
{
    return widget->getParent();
}

bool ciUIEventArgs::isName(const std::string & _name)
{
    return (getName() == _name) ? true : false; 
}

bool ciUIEventArgs::getBool()
{
    return getButton()->getValue();
}

float ciUIEventArgs::getFloat()
{
    return getSlider()->getValue();
}

double ciUIEventArgs::getDouble()
{
    return getSlider()->getValue();
}

int ciUIEventArgs::getInt()
{
    return getSlider()->getValue();
}

const std::string &ciUIEventArgs::getName()
{
    return widget->getName();
}

std::string ciUIEventArgs::getParentName()
{
    ciUIWidget *parent = widget->getParent();
    if(parent != nullptr)
    {
        return parent->getName();
    }
    else
    {
        return "";
    }
}

std::string ciUIEventArgs::getCanvasParentName()
{
    ciUIWidget *parent = widget->getCanvasParent();
    if(parent != nullptr)
    {
        return parent->getName();
    }
    else
    {
        return "";
    }
}

int ciUIEventArgs::getKind()
{
    return widget->getKind();
}
