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

#include "ciUIToggle.h"
#include "ciUI.h"

ciUIToggle::ciUIToggle() : ciUIButton()
{
    
}

ciUIToggle::ciUIToggle(const std::string &_name, bool _value, float w, float h, float x, float y, int _size)
: ciUIButton( _name, _value, w, h, x, y, _size )
{
    kind = CI_UI_WIDGET_TOGGLE;
}

ciUIToggle::ciUIToggle(const std::string &_name, bool *_value, float w, float h, float x, float y, int _size)
: ciUIButton( _name, _value, w, h, x, y, _size )
{
    kind = CI_UI_WIDGET_TOGGLE;
}

void ciUIToggle::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ciUIToggle::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ciUIToggle::mouseMoved(int x, int y )
{
    if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
    {
        state = CI_UI_STATE_OVER;
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUIToggle::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = CI_UI_STATE_DOWN;
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUIToggle::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
    {
        hit = true;
        state = CI_UI_STATE_DOWN;
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUIToggle::mouseReleased(int x, int y, int button)
{
    if((rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y))) && hit)
    {
        setValue(!(*value));
#ifdef CI_UI_TARGET_TOUCH
        state = CI_UI_STATE_NORMAL;
#else
        state = CI_UI_STATE_OVER;
#endif
        triggerEvent(this);
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

void ciUIToggle::setParent(ciUIWidget *_parent)
{
    ciUIButton::setParent(_parent);
}

void ciUIToggle::setValue(bool _value)
{
    *value = _value;
    draw_fill = *value;
}

void ciUIToggle::keyPressed(int key)
{
    if(getIsBindedToKey(key) && !bKeyHit)
    {
        bKeyHit = true;
        toggleValue();
        triggerEvent(this);
    }
}

void ciUIToggle::keyReleased(int key)
{
    if(getIsBindedToKey(key) && bKeyHit)
    {
        bKeyHit = false; 
    }
}

//#ifndef CI_UI_NO_XML
//
//void ciUIToggle::saveState(ofxXmlSettings *XML)
//{
//    XML->setValue("Value", (getValue() ? 1 : 0), 0);
//}
//
//void ciUIToggle::loadState(ofxXmlSettings *XML)
//{
//    int value = XML->getValue("Value", (getValue() ? 1 : 0), 0);
//    setValue((value ? 1 : 0));
//}
//
//#endif
