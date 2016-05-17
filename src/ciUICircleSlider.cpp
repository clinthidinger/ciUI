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

#include "ciUICircleSlider.h"
#include "ciUI.h"

ciUICircleSlider::ciUICircleSlider(float x, float y, float w, float _min, float _max, float _value, const std::string &_name, int _size) : ciUISlider()
{
    useReference = false;
    init(x, y, w, w, _min, _max, &_value, _name, _size);
}

ciUICircleSlider::ciUICircleSlider(float w, float _min, float _max, float _value, const std::string &_name, int _size) : ciUISlider()
{
    useReference = false;
    init(0, 0, w, w, _min, _max, &_value, _name, _size);
}

ciUICircleSlider::ciUICircleSlider(float x, float y, float w, float _min, float _max, float *_value, const std::string &_name, int _size) : ciUISlider()
{
    useReference = true;
    init(x, y, w, w, _min, _max, _value, _name, _size);
}

ciUICircleSlider::ciUICircleSlider(float w, float _min, float _max, float *_value, const std::string &_name, int _size) : ciUISlider()
{
    useReference = true;
    init(0, 0, w, w, _min, _max, _value, _name, _size);
}

void ciUICircleSlider::init(float x, float y, float w, float h, float _min, float _max, float *_value, const std::string &_name, int _size)
{
    initRect(x,y,w,h);
    name = _name;
    kind = CI_UI_WIDGET_CIRCLESLIDER;
    
    draw_fill = true;
    draw_outline = true;
    
    value = *_value;                                               //the widget's value
    if(useReference)
    {
        valueRef = _value;
    }
    else
    {
        valueRef = new float();
        *valueRef = value;
    }
    
    max = _max;
    min = _min;
    labelPrecision = 2;
    increment = .0005;
    inputDirection = CI_UI_DIRECTION_SOUTHNORTH;
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    value = ciUIMap<float>(value, min, max, 0.0f, 1.0f, true);
    
    label = new ciUILabel(0,w+padding,(name+" LABEL"), name, _size);
    addEmbeddedWidget(label);
}


void ciUICircleSlider::drawBack()
{
    if(draw_back)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_back);
        ciUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), rect->getHalfWidth(), true);
    }
}

void ciUICircleSlider::drawOutline()
{
    if(draw_outline)
    {
        //ofNoFill();
        ci::gl::ScopedColor scopedColor(color_outline);
        ciUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), rect->getHalfWidth(), false);
    }
}

void ciUICircleSlider::drawFill()
{
    if(draw_fill)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill);
        ciUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), value*rect->getHalfWidth(), true);
    }
}

void ciUICircleSlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        //ciUIFill();
        {
            ci::gl::ScopedColor scopedColor(color_fill_highlight);
            ciUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), value*rect->getHalfWidth(), true);
        }
        {
            ci::gl::ScopedColor scopedColor(label->getColorFillHighlight());
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ciUIToString(getScaledValue(),labelPrecision));
        }
    }
}

void ciUICircleSlider::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        //ofNoFill();
        ci::gl::ScopedColor scopedColor(color_outline_highlight);
        ciUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), rect->getHalfWidth(), false);
        if(!draw_fill_highlight)
        {
            ci::gl::ScopedColor scopedColor(label->getColorFill());
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ciUIToString(getScaledValue(),labelPrecision));
        }
    }
}

void ciUICircleSlider::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        if(triggerType & CI_UI_TRIGGER_CHANGE)
        {
            switch(inputDirection)
            {
                case CI_UI_DIRECTION_NORTHSOUTH:
                    value -= increment*(hitPoint.y-y);
                    valueClamp();
                    break;
                case CI_UI_DIRECTION_SOUTHNORTH:
                    value += increment*(hitPoint.y-y);
                    valueClamp();
                    break;
                case CI_UI_DIRECTION_EASTWEST:
                    value += increment*(hitPoint.x-x);
                    valueClamp();
                    break;
                case CI_UI_DIRECTION_WESTEAST:
                    value -= increment*(hitPoint.x-x);
                    valueClamp();
                    break;
            }
            
            hitPoint = ciUIVec2f(x,y);
            updateValueRef();
            triggerEvent(this);
        }
        state = CI_UI_STATE_DOWN;
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUICircleSlider::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        hitPoint = ciUIVec2f(x,y);
        state = CI_UI_STATE_DOWN;
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

void ciUICircleSlider::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef CI_UI_TARGET_TOUCH
        state = CI_UI_STATE_NORMAL;
#else
        state = CI_UI_STATE_OVER;
#endif
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
    hit = false;
}

void ciUICircleSlider::valueClamp()
{
    value = std::min(1.0f, std::max(0.0f, static_cast<float>(value)));
}

void ciUICircleSlider::setInputDirection(ciUIWidgetInputDirection _inputDirection)
{
    inputDirection = _inputDirection;
}

void ciUICircleSlider::updateLabel()
{
    
}

void ciUICircleSlider::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    ciUIRectangle *labelrect = label->getRect();
    while(labelrect->getWidth() > rect->getWidth())
    {
        std::string labelstring = label->getLabel();
        std::string::iterator it;
        it=labelstring.end();
        it--;
        labelstring.erase (it);
        label->setLabel(labelstring);
    }
    
    float w = labelrect->getWidth();
    float pw = rect->getWidth();
    labelrect->setX((int)(pw*.5 - w*.5-padding*.5)); 
    calculatePaddingRect();
}

bool ciUICircleSlider::isHit(float x, float y)
{
    if(visible && glm::distance(ci::vec2(x, y), ci::vec2(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight())) < rect->getHalfWidth())
    {
        return true;
    }
    else
    {
        return false;
    }
}
