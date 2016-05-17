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

#include "ciUIButton.h"
#include "ciUI.h"

ciUIButton::ciUIButton() : ciUIWidgetWithLabel()
{
    
}

ciUIButton::ciUIButton(const std::string &_name, bool _value, float w, float h, float x, float y, int _size) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(_name, &_value, w, h, x, y, _size);
}

ciUIButton::ciUIButton(const std::string &_name, bool *_value, float w, float h, float x, float y, int _size) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _value, w, h, x, y, _size);
}

ciUIButton::~ciUIButton()
{
    if(!useReference)
    {
        delete value;
    }
}

void ciUIButton::init(const std::string &_name, bool *_value, float w, float h, float x, float y, int _size)
{
    initRect(x,y,w,h);
    name = _name;
    kind = CI_UI_WIDGET_BUTTON;
    label = new ciUILabel((name+" LABEL"),name,_size);
    addEmbeddedWidget(label);
    
    labelPosition = CI_UI_WIDGET_POSITION_RIGHT;
    
    if(useReference)
    {
        value = _value;
    }
    else
    {
        value = new bool();
        *value = *_value;
    }
    
    setValue(*_value);
}

void ciUIButton::drawFill()
{
    if(*value)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill);
        rect->draw(true);
    }
}

void ciUIButton::mouseMoved(int x, int y)
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

void ciUIButton::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
        {
            state = CI_UI_STATE_DOWN;
        }
        else
        {
            hit = false;
            state = CI_UI_STATE_NORMAL;
            toggleValue();
            if(triggerType & CI_UI_TRIGGER_END)
            {
                triggerEvent(this);
            }
        }
        stateChange();
    }
}

void ciUIButton::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
    {
        hit = true;
        state = CI_UI_STATE_DOWN;
        toggleValue();
        if(triggerType & CI_UI_TRIGGER_BEGIN)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUIButton::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef CI_UI_TARGET_TOUCH
        state = CI_UI_STATE_NORMAL;
#else
        hit = false;
        if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
        {
            state = CI_UI_STATE_OVER;
        }
        else
        {
            state = CI_UI_STATE_NORMAL;
        }
#endif
        toggleValue();
        if(triggerType & CI_UI_TRIGGER_END)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUIButton::stateChange()
{
    switch (state) {
        case CI_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case CI_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case CI_UI_STATE_DOWN:
        {
            draw_fill_highlight = true;
            draw_outline_highlight = false;
            label->focus();
        }
            break;
        case CI_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
            
        default:
            break;
    }
}

void ciUIButton::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    setLabelPosition(labelPosition);
}

bool ciUIButton::getValue() const
{
    return *value;
}
void ciUIButton::setValue(bool _value)
{
    *value = _value;
    draw_fill = *value;
}

void ciUIButton::setValuePtr(bool *_value)
{
    if(!useReference)
    {
        delete value;
        useReference = true;
    }
    value = _value;
    setValue(*value);
}

void ciUIButton::toggleValue()
{
    setValue(!(*value));
}

bool ciUIButton::isHit(float x, float y)
{
    if(visible)
    {
        return (rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)));
    }
    else
    {
        return false;
    }
}

void ciUIButton::setLabelPosition(ciUIWidgetPosition pos)
{
    labelPosition = pos;
    switch (labelPosition)
    {
        case CI_UI_WIDGET_POSITION_LEFT:
        {
            ciUIRectangle *labelrect = label->getRect();
            float h = labelrect->getHeight();
            float ph = rect->getHeight();
            labelrect->setX(-label->getRect()->getWidth() - padding*2);
            labelrect->setY(ph/2.0 - h/2.0);
        }
            break;
            
        case CI_UI_WIDGET_POSITION_RIGHT:
        {
            ciUIRectangle *labelrect = label->getRect();
            float h = labelrect->getHeight();
            float ph = rect->getHeight();
            labelrect->setX(rect->getWidth()+padding);
            labelrect->setY(ph/2.0 - h/2.0);
        }
            break;
            
        case CI_UI_WIDGET_POSITION_DOWN:
        {
            label->getRect()->setX(0);
            label->getRect()->setY(rect->getHeight() + padding);
        }
            break;
            
        case CI_UI_WIDGET_POSITION_UP:
        {
            label->getRect()->setX(0);
            label->getRect()->setY(-label->getRect()->getHeight() - padding);
        }
            break;
            
        default:
            break;
    }
   calculatePaddingRect();
}

void ciUIButton::keyPressed(int key)
{
    if(getIsBindedToKey(key) && !bKeyHit)
    {
        bKeyHit = true;
        toggleValue();
        if(triggerType & CI_UI_TRIGGER_BEGIN)
        {
            triggerEvent(this);
        }
    }
}

void ciUIButton::keyReleased(int key)
{
    if(getIsBindedToKey(key) && bKeyHit)
    {
        bKeyHit = false; 
        toggleValue();
        if(triggerType & CI_UI_TRIGGER_END)
        {
            triggerEvent(this);
        }
    }
}
