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

#include "ciUIRotarySlider.h"
#include "ciUI.h"
#include "glm/gtx/vector_angle.hpp"

ciUIRotarySlider::ciUIRotarySlider(float x, float y, float w, float _min, float _max, float _value, const std::string &_name, int _size) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(x, y, w, _min, _max, &_value, _name, _size);
}

ciUIRotarySlider::ciUIRotarySlider(float w, float _min, float _max, float _value, const std::string &_name, int _size) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(0, 0, w, _min, _max, &_value, _name, _size);
}

ciUIRotarySlider::ciUIRotarySlider(float x, float y, float w, float _min, float _max, float *_value, const std::string &_name, int _size) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(x, y, w, _min, _max, _value, _name, _size);
}

ciUIRotarySlider::ciUIRotarySlider(float w, float _min, float _max, float *_value, const std::string &_name, int _size) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(0, 0, w, _min, _max, _value, _name, _size);
}

ciUIRotarySlider::~ciUIRotarySlider()
{
    if(!useReference)
    {
        delete valueRef;
    }
}

void ciUIRotarySlider::init(float x, float y, float w, float _min, float _max, float *_value, const std::string &_name, int _size)
{
    initRect(x,y,w,w);
    name = _name;
    kind = CI_UI_WIDGET_ROTARYSLIDER;
    
    draw_fill = true;
    
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
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    outerRadius = rect->getWidth()*.5;
    innerRadius = rect->getWidth()*.25;
    
    value = ciUIMap<float>(value, min, max, 0.0f, 1.0f, true);
    valueString = ciUIToString(getValue(),2);
    label = new ciUILabel(0,w+padding,(name+" LABEL"), (name + ": " + valueString), _size);
    addEmbeddedWidget(label);
    increment = fabs(max - min) / 10.0;
}

void ciUIRotarySlider::update()
{
    if(useReference)
    {
        value = ciUIMap<float>(*valueRef, min, max, 0.0f, 1.0f, true);
        updateLabel();
    }
}

void ciUIRotarySlider::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ciUIRotarySlider::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ciUIRotarySlider::drawBack()
{
    if(draw_back)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_back);
        drawArcStrip(1.0, true);
    }
}

void ciUIRotarySlider::drawFill()
{
    if(draw_fill)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill);
        drawArcStrip(value, true);
    }
}

void ciUIRotarySlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill_highlight);
        drawArcStrip(value, true);
    }
}

void ciUIRotarySlider::drawOutline()
{
    if(draw_outline)
    {
        //ofNoFill();
        ci::gl::ScopedColor scopedColor(color_outline);
        ci::gl::ScopedLineWidth scopedLineWidth(2.0);
        drawArcStrip(1.0, true);
    }
}
void ciUIRotarySlider::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        //ofNoFill();
        ci::gl::ScopedColor scopedColor(color_outline_highlight);
        ci::gl::ScopedLineWidth scopedLineWidth(2.0);
        drawArcStrip(1.0, true);
    }
}

void ciUIRotarySlider::mouseMoved(int x, int y )
{
    if(rect->inside(x, y))
    {
        state = CI_UI_STATE_OVER;
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUIRotarySlider::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = CI_UI_STATE_DOWN;
        if(triggerType & CI_UI_TRIGGER_CHANGE)
        {
            input(x, y);
            triggerEvent(this);
        }
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUIRotarySlider::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = CI_UI_STATE_DOWN;
        if(triggerType & CI_UI_TRIGGER_BEGIN)
        {
            input(x, y);
            triggerEvent(this);
        }
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUIRotarySlider::mouseReleased(int x, int y, int button)
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
            input(x, y);
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

void ciUIRotarySlider::keyPressed(int key)
{
    if(state == CI_UI_STATE_OVER)
    {
        switch (key)
        {
            case ci::app::KeyEvent::KEY_RIGHT:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case ci::app::KeyEvent::KEY_UP:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case ci::app::KeyEvent::KEY_LEFT:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            case ci::app::KeyEvent::KEY_DOWN:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            default:
                break;
        }
    }
}

void ciUIRotarySlider::drawArcStrip(float percent, bool doFill)
{
    float theta = ciUIMap<float>(percent, 0.0f, 1.0f, 0.0f, 360.0f, true);
    
    ci::gl::ScopedMatrices scopedMatrices;
    ci::gl::translate(rect->getX(),rect->getY());
 
    if(doFill)
    {
        shape.clear();
        {
            float x = sin(-glm::radians(0.0f));
            float y = cos(-glm::radians(0.0f));
            shape.lineTo(ci::vec2(center.x+outerRadius*x,center.y+outerRadius*y));
        }
        
        for(int i = 0; i <= theta; i+=10)
        {
            float x = sin(-glm::radians(static_cast<float>(i)));
            float y = cos(-glm::radians(static_cast<float>(i)));
            
            shape.lineTo(ci::vec2(center.x+outerRadius*x,center.y+outerRadius*y));
        }
        
        {
            float x = sin(-glm::radians(theta));
            float y = cos(-glm::radians(theta));
            shape.lineTo(ci::vec2(center.x+outerRadius*x,center.y+outerRadius*y));
            shape.lineTo(ci::vec2(center.x+innerRadius*x,center.y+innerRadius*y));
        }
        
        for(int i = theta; i >= 0; i-=10)
        {
            float x = sin(-glm::radians(static_cast<float>(i)));
            float y = cos(-glm::radians(static_cast<float>(i)));
            
            shape.lineTo(ci::vec2(center.x+innerRadius*x,center.y+innerRadius*y));
        }
        
        {
            float x = sin(-glm::radians(0.0f));
            float y = cos(-glm::radians(0.0f));
            shape.lineTo(ci::vec2(center.x+innerRadius*x,center.y+innerRadius*y));
        }
        shape.close();
        ci::gl::draw(shape);
    }
    else
    {
        polyLine.getPoints().clear();
        polyLine.getPoints().reserve(80);
        {
            float x = sin(-glm::radians(0.0f));
            float y = cos(-glm::radians(0.0f));
            polyLine.push_back(ci::vec2(center.x+outerRadius*x,center.y+outerRadius*y));
        }
    
        for(int i = 0; i <= theta; i+=10)
        {
            float x = sin(-glm::radians(static_cast<float>(i)));
            float y = cos(-glm::radians(static_cast<float>(i)));
            
            polyLine.push_back(ci::vec2(center.x+outerRadius*x,center.y+outerRadius*y));
        }
        
        {
            float x = sin(-glm::radians(theta));
            float y = cos(-glm::radians(theta));
            polyLine.push_back(ci::vec2(center.x+outerRadius*x,center.y+outerRadius*y));
            polyLine.push_back(ci::vec2(center.x+innerRadius*x,center.y+innerRadius*y));
        }
        
        for(int i = theta; i >= 0; i-=10)
        {
            float x = sin(-glm::radians(static_cast<float>(i)));
            float y = cos(-glm::radians(static_cast<float>(i)));
            
            polyLine.push_back(ci::vec2(center.x+innerRadius*x,center.y+innerRadius*y));
        }
        
        {
            float x = sin(-glm::radians(0.0f));
            float y = cos(-glm::radians(0.0f));
            polyLine.push_back(ci::vec2(center.x+innerRadius*x,center.y+innerRadius*y));
        }
        
        polyLine.setClosed();
        ci::gl::draw(polyLine);
    }
}

void ciUIRotarySlider::setIncrement(float _increment)
{
    increment = _increment;
}

void ciUIRotarySlider::input(float x, float y)
{
    hitPoint = ciUIVec2f(x,y);
    ci::vec2 mappedHitPoint = hitPoint;
    mappedHitPoint -= ci::vec2(rect->getX()+center.x, rect->getY()+center.y);
    
    ci::vec2 cVector = center - homePoint;
    float angle = glm::angle<float>(cVector, mappedHitPoint);
    value = ciUIMap<float>(angle, -180.0f, 180.0f, 0.0f, 1.0f, true);
    
    value = std::min(1.0f, std::max(0.0f, value));
    updateValueRef();
    updateLabel();
}

void ciUIRotarySlider::updateValueRef()
{
    (*valueRef) = getScaledValue();
}

void ciUIRotarySlider::updateLabel()
{
    valueString = ciUIToString(getValue(),2);
    label->setLabel(name + ": " + valueString);
}

void ciUIRotarySlider::stateChange()
{
    if(value > 0)
    {
        draw_fill = true;
    }
    else
    {
        draw_fill = false;
    }
    
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
            label->unfocus();
        }
            break;
        case CI_UI_STATE_DOWN:
        {
            draw_fill_highlight = true;
            draw_outline_highlight = true;
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

void ciUIRotarySlider::setValue(float _value)
{
    value = ciUIMap<float>(_value, min, max, 0.0f, 1.0f, true);
    updateValueRef();
    updateLabel();
}

float ciUIRotarySlider::getValue()
{
    return (*valueRef); 
}

float ciUIRotarySlider::getNormalizedValue()
{
    return value;
}

float ciUIRotarySlider::getScaledValue()
{
    return ciUIMap<float>(value, 0.0f, 1.0f, min, max, true);
}

void ciUIRotarySlider::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    calculatePaddingRect();
    center = ciUIVec2f(rect->getWidth()*.5, rect->getHeight()*.5);
    homePoint = ciUIVec2f(rect->getWidth()*.5, rect->getHeight());
}

bool ciUIRotarySlider::isDraggable()
{
    return true;
}

void ciUIRotarySlider::setMax(float _max)
{
    setMaxAndMin(_max, min);
}

float ciUIRotarySlider::getMax()
{
    return max;
}

void ciUIRotarySlider::setMin(float _min)
{
    setMaxAndMin(max, _min);
}

float ciUIRotarySlider::getMin()
{
    return min;
}

ci::vec2 ciUIRotarySlider::getMaxAndMind()
{
    return ci::vec2(max, min);
}

void ciUIRotarySlider::setMaxAndMin(float _max, float _min)
{
    max = _max;
    min = _min;
    
    value = ciUIMap<float>(value, 0.0f, 1.0f, min, max, true);
    value = ciUIMap<float>(value, min, max, 0.0f, 1.0f, true);
    updateValueRef();
    updateLabel();
}


bool ciUIRotarySlider::isHit(float x, float y)
{
    float d = glm::distance(ci::vec2(x, y), ci::vec2(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight()));
    if(visible &&  d < outerRadius && d > innerRadius)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#ifndef CI_UI_NO_XML

void ciUIRotarySlider::saveState(ofxXmlSettings *XML)
{
    XML->setValue("Value", getScaledValue(), 0);   
}

void ciUIRotarySlider::loadState(ofxXmlSettings *XML)
{
    setValue(XML->getValue("Value", getScaledValue(), 0));
}

#endif
