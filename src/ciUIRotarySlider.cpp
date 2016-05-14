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
    
    value = ciUIMap(value, min, max, 0.0, 1.0, true);
    valueString = ciUIToString(getValue(),2);
    label = new ciUILabel(0,w+padding,(name+" LABEL"), (name + ": " + valueString), _size);
    addEmbeddedWidget(label);
    increment = fabs(max - min) / 10.0;
}

void ciUIRotarySlider::update()
{
    if(useReference)
    {
        value = ciUIMap(*valueRef, min, max, 0.0, 1.0, true);
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
        ciUIFill();
        ciUISetColor(color_back);
        drawArcStrip(1.0);
    }
}

void ciUIRotarySlider::drawFill()
{
    if(draw_fill)
    {
        ciUIFill();
        ciUISetColor(color_fill);
        drawArcStrip(value);
    }
}

void ciUIRotarySlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ciUIFill();
        ciUISetColor(color_fill_highlight);
        drawArcStrip(value);
    }
}

void ciUIRotarySlider::drawOutline()
{
    if(draw_outline)
    {
        ofNoFill();
        ciUISetColor(color_outline);
        ofSetLineWidth(2.0);
        drawArcStrip(1.0);
        ofSetLineWidth(1.0);
    }
}
void ciUIRotarySlider::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        ofNoFill();
        ciUISetColor(color_outline_highlight);
        ofSetLineWidth(2.0);
        drawArcStrip(1.0);
        ofSetLineWidth(1.0);
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
            case OF_KEY_RIGHT:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_UP:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_LEFT:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_DOWN:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            default:
                break;
        }
    }
}

void ciUIRotarySlider::drawArcStrip(float percent)
{
    float theta = ciUIMap(percent, 0, 1, 0, 360.0, true);
    
    ofPushMatrix();
    ofTranslate(rect->getX(),rect->getY());
    
    ofBeginShape();
    
    {
        float x = sin(-ofDegToRad(0));
        float y = cos(-ofDegToRad(0));
        ofVertex(center.x+outerRadius*x,center.y+outerRadius*y);
    }
    
    for(int i = 0; i <= theta; i+=10)
    {
        float x = sin(-ofDegToRad(i));
        float y = cos(-ofDegToRad(i));
        
        ofVertex(center.x+outerRadius*x,center.y+outerRadius*y);
    }
    
    {
        float x = sin(-ofDegToRad(theta));
        float y = cos(-ofDegToRad(theta));
        ofVertex(center.x+outerRadius*x,center.y+outerRadius*y);
        ofVertex(center.x+innerRadius*x,center.y+innerRadius*y);
    }
    
    for(int i = theta; i >= 0; i-=10)
    {
        float x = sin(-ofDegToRad(i));
        float y = cos(-ofDegToRad(i));
        
        ofVertex(center.x+innerRadius*x,center.y+innerRadius*y);
    }
    
    {
        float x = sin(-ofDegToRad(0));
        float y = cos(-ofDegToRad(0));
        ofVertex(center.x+innerRadius*x,center.y+innerRadius*y);
    }
    
    ofEndShape();
    ofPopMatrix();
}

void ciUIRotarySlider::setIncrement(float _increment)
{
    increment = _increment;
}

void ciUIRotarySlider::input(float x, float y)
{
    hitPoint = ciUIVec2f(x,y);
    ofVec2f mappedHitPoint = hitPoint;
    mappedHitPoint -= ofVec2f(rect->getX()+center.x, rect->getY()+center.y);
    
    ofVec2f cVector = center-homePoint;
    value = ciUIMap(cVector.angle(mappedHitPoint), -180, 180, 0, 1.0, true);
    
    value = MIN(1.0, MAX(0.0, value));
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
    value = ciUIMap(_value, min, max, 0.0, 1.0, true);
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
    return ciUIMap(value, 0.0, 1.0, min, max, true);
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

ofVec2f ciUIRotarySlider::getMaxAndMind()
{
    return ofVec2f(max, min);
}

void ciUIRotarySlider::setMaxAndMin(float _max, float _min)
{
    max = _max;
    min = _min;
    
    value = ciUIMap(value, 0, 1.0, min, max, true);
    value = ciUIMap(value, min, max, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}


bool ciUIRotarySlider::isHit(float x, float y)
{
    float d = ofDist(x, y, rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight());
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
