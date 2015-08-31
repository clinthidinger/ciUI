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

#include "ciUIRangeSlider.h"
#include "ciUI.h"

ciUIRangeSlider::ciUIRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh, float w, float h,
                 float x, float y, int _size) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_valuelow, &_valuehigh, w, h, x, y, _size);
}

ciUIRangeSlider::ciUIRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h,
                 float x, float y, int _size) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y, _size);
}

ciUIRangeSlider::ciUIRangeSlider(float x, float y, float w, float h, float _min, float _max, float _valuelow, float _valuehigh, string _name, int _size) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_valuelow, &_valuehigh, w, h, x, y, _size);
    //        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ciUIRangeSlider::ciUIRangeSlider(float w, float h, float _min, float _max, float _valuelow, float _valuehigh, string _name, int _size) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_valuelow, &_valuehigh, w, h, 0, 0, _size);
    //        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ciUIRangeSlider::ciUIRangeSlider(float x, float y, float w, float h, float _min, float _max, float *_valuelow, float *_valuehigh, string _name, int _size) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y, _size);
    //        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ciUIRangeSlider::ciUIRangeSlider(float w, float h, float _min, float _max, float *_valuelow, float *_valuehigh, string _name, int _size) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _valuelow, _valuehigh, w, h, 0, 0, _size);
    //        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ciUIRangeSlider::~ciUIRangeSlider()
{
    if(!useReference)
    {
        delete valuelowRef;
        delete valuehighRef;
    }
}

void ciUIRangeSlider::init(string _name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h,
          float x, float y, int _size)
{
    initRect(x,y,w,h);
    name = string(_name);
    if(w > h)
    {
        kind = CI_UI_WIDGET_RSLIDER_H;
    }
    else
    {
        kind = CI_UI_WIDGET_RSLIDER_V;
    }
    
    draw_fill = true;
    
    valuelow = *_valuelow;                                                  //the widget's value
    valuehigh = *_valuehigh;                                                //the widget's value
    
    if(useReference)
    {
        valuelowRef = _valuelow;
        valuehighRef = _valuehigh;
    }
    else
    {
        valuelowRef = new float();
        valuehighRef = new float();
        *valuelowRef = valuelow;
        *valuehighRef = valuehigh;
    }
    
    max = _max;
    min = _min;
    hitHigh = false;
    hitLow = false;
    hitCenter = false;
    
    if(valuelow > max)
    {
        valuelow = max;
    }
    if(valuelow < min)
    {
        valuelow = min;
    }
    
    if(valuehigh > max)
    {
        valuehigh = max;
    }
    if(valuehigh < min)
    {
        valuehigh = min;
    }
    
    valuelow = ciUIMap(valuelow, min, max, 0.0, 1.0, true);
    valuehigh = ciUIMap(valuehigh, min, max, 0.0, 1.0, true);
    labelPrecision = 2;
    
    valuelowString = ciUIToString(getScaledValueLow(),labelPrecision);
    valuehighString = ciUIToString(getScaledValueHigh(),labelPrecision);
    
    if(kind == CI_UI_WIDGET_RSLIDER_H)
    {
        label = new ciUILabel(0,h+padding,(name+" LABEL"), (name + ": " + valuelowString + " " + valuehighString), _size);
    }
    else
    {
        label = new ciUILabel(0,h+padding,(name+" LABEL"), name, _size);
    }
    addEmbeddedWidget(label);
    
    increment = fabs(max - min) / 10.0;
}

void ciUIRangeSlider::update()
{
    if(useReference)
    {
        valuelow = ciUIMap(*valuelowRef, min, max, 0.0, 1.0, true);
        valuehigh = ciUIMap(*valuehighRef, min, max, 0.0, 1.0, true);
    }
}

void ciUIRangeSlider::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ciUIRangeSlider::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ciUIRangeSlider::drawFill()
{
    if(draw_fill)
    {
        ciUIFill();
        ciUISetColor(color_fill);
        if(kind == CI_UI_WIDGET_RSLIDER_H)
        {
            ciUIDrawRect(rect->getX()+rect->getWidth()*valuelow, rect->getY(), rect->getWidth()*(valuehigh-valuelow), rect->getHeight());
        }
        else
        {
            ciUIDrawRect(rect->getX(), rect->getY()+(1.0-valuehigh)*rect->getHeight(), rect->getWidth(), rect->getHeight()*(valuehigh-valuelow));
        }
    }
}

void ciUIRangeSlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ciUIFill();
        ciUISetColor(color_fill_highlight);
        if(kind == CI_UI_WIDGET_RSLIDER_H)
        {
            ciUIDrawRect(rect->getX()+rect->getWidth()*valuelow, rect->getY(), rect->getWidth()*(valuehigh-valuelow), rect->getHeight());
        }
        else
        {
            ciUIDrawRect(rect->getX(), rect->getY()+(1.0-valuehigh)*rect->getHeight(), rect->getWidth(), rect->getHeight()*(valuehigh-valuelow));
        }
        if(kind == CI_UI_WIDGET_RSLIDER_V)
        {
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*valuehigh, valuehighString);
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*valuelow, valuelowString);
        }
    }
}

void ciUIRangeSlider::mouseMoved(int x, int y )
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

void ciUIRangeSlider::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = CI_UI_STATE_DOWN;
        hitValueHigh = valuehigh;
        hitValueLow = valuelow;
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

void ciUIRangeSlider::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = CI_UI_STATE_DOWN;
        hitValueHigh = valuehigh;
        hitValueLow = valuelow;
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

void ciUIRangeSlider::mouseReleased(int x, int y, int button)
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
    hitHigh = false;
    hitLow = false;
    hitCenter = false;
}

void ciUIRangeSlider::keyPressed(int key)
{
    if(state == CI_UI_STATE_OVER)
    {
        switch (key)
        {
            case OF_KEY_RIGHT:
                setValueHigh(getScaledValueHigh()+increment);
                setValueLow(getScaledValueLow()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_LEFT:
                setValueHigh(getScaledValueHigh()-increment);
                setValueLow(getScaledValueLow()-increment);
                triggerEvent(this);
                break;
                
                
            case OF_KEY_UP:
                setValueHigh(getScaledValueHigh()+increment);
                setValueLow(getScaledValueLow()-increment);
                triggerEvent(this);
                break;
                
                
            case OF_KEY_DOWN:
                setValueHigh(getScaledValueHigh()-increment);
                setValueLow(getScaledValueLow()+increment);
                triggerEvent(this);
                break;
                
            default:
                break;
        }
    }
}

void ciUIRangeSlider::keyReleased(int key)
{
    
}

void ciUIRangeSlider::windowResized(int w, int h)
{
    
}

void ciUIRangeSlider::setIncrement(float _increment)
{
    increment = _increment;
}

void ciUIRangeSlider::input(float x, float y)
{
    float v = 0;
    
    if(kind == CI_UI_WIDGET_RSLIDER_H)
    {
        v = rect->percentInside(x, y).x;
    }
    else
    {
        v = 1.0-rect->percentInside(x, y).y;
    }
    
    if(hitHigh)
    {
        valuehigh = v;
    }
    else if(hitLow)
    {
        valuelow = v;
    }
    else if(hitCenter)
    {
        valuehigh +=(v-hitPoint);
        valuelow +=(v-hitPoint);
        hitPoint = v;
    }
    else
    {
        float dvh = fabs(valuehigh - v);
        float dvl = fabs(valuelow - v);
        if(dvh < .05 || v > valuehigh)
        {
            valuehigh = v;
            hitHigh = true;
        }
        else if(dvl < .05 || v < valuelow)
        {
            valuelow = v;
            hitLow = true;
        }
        else
        {
            hitCenter = true;
            hitPoint = v;
        }
    }
    
    if(valuehigh < valuelow && hitHigh)
    {
        valuehigh = hitValueLow;
        hitHigh = false;
        hitLow = true;
    }
    else if(valuelow > valuehigh && hitLow)
    {
        valuelow = hitValueHigh;
        hitHigh = true;
        hitLow = false;
    }
    
    valuehigh = MIN(1.0, MAX(0.0, valuehigh));
    valuelow = MIN(1.0, MAX(0.0, valuelow));
    updateValueRef();
    updateLabel();
}

void ciUIRangeSlider::updateValueRef()
{
    (*valuelowRef) = getScaledValueLow();
    (*valuehighRef) = getScaledValueHigh();
}

void ciUIRangeSlider::updateLabel()
{
    valuelowString = ciUIToString(getValueLow(),labelPrecision);
    valuehighString = ciUIToString(getValueHigh(),labelPrecision);
    
    if(kind == CI_UI_WIDGET_RSLIDER_H)
    {
        label->setLabel(name + ": " + valuelowString + " " + valuehighString);
    }
}

void ciUIRangeSlider::stateChange()
{
    if(valuehigh > 0)
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

void ciUIRangeSlider::setValueLow(float _value)
{
    valuelow = ciUIMap(_value, min, max, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}

void ciUIRangeSlider::setValueHigh(float _value)
{
    valuehigh = ciUIMap(_value, min, max, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}

float ciUIRangeSlider::getValueLow()
{
    return (*valuelowRef);
}

float ciUIRangeSlider::getValueHigh()
{
    return (*valuehighRef);
}

float ciUIRangeSlider::getNormalizedValueLow()
{
    return valuelow;
}

float ciUIRangeSlider::getNormalizedValueHigh()
{
    return valuehigh;
}

float ciUIRangeSlider::getPercentValueLow()
{
    return valuelow;
}

float ciUIRangeSlider::getPercentValueHigh()
{
    return valuehigh;
}

float ciUIRangeSlider::getScaledValueLow()
{
    return ciUIMap(valuelow, 0.0, 1.0, min, max, true);
}

float ciUIRangeSlider::getScaledValueHigh()
{
    return ciUIMap(valuehigh, 0.0, 1.0, min, max, true);
}

void ciUIRangeSlider::setLabelPrecision(int _precision)
{
    labelPrecision = _precision;
    updateValueRef();
    updateLabel();
}

void ciUIRangeSlider::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    calculatePaddingRect(); 
}

void ciUIRangeSlider::setMax(float _max)
{
    setMaxAndMin(_max, min);
}

void ciUIRangeSlider::setMin(float _min)
{
    setMaxAndMin(max, _min);
}

void ciUIRangeSlider::setMaxAndMin(float _max, float _min)
{
    max = _max;
    min = _min;
    
    valuelow= ciUIMap(valuelow, 0, 1.0, min, max, true);
    valuelow = ciUIMap(valuelow, min, max, 0.0, 1.0, true);
    
    valuehigh = ciUIMap(valuehigh, 0, 1.0, min, max, true);
    valuehigh = ciUIMap(valuehigh, min, max, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}

float ciUIRangeSlider::getMin()
{
    return min;
}

float ciUIRangeSlider::getMax()
{
    return max; 
}

bool ciUIRangeSlider::isDraggable()
{
    return true;
}

#ifndef CI_UI_NO_XML

void ciUIRangeSlider::saveState(ofxXmlSettings *XML)
{
    XML->setValue("HighValue", getValueHigh(), 0);
    XML->setValue("LowValue", getValueLow(), 0);

}

void ciUIRangeSlider::loadState(ofxXmlSettings *XML)
{
    setValueHigh(XML->getValue("HighValue", getValueHigh(), 0));
    setValueLow(XML->getValue("LowValue", getValueLow(), 0));
}

#endif
