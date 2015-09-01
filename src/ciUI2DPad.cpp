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

#include "ciUI2DPad.h"
#include "ciUI.h"

ciUI2DPad::ciUI2DPad(const std::string &_name, const ciUIVec3f &_rangeX, const ciUIVec3f &_rangeY, const ciUIVec3f &_value, float w, float h, float x, float y) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _rangeX, _rangeY, &_value, w, h, x, y);
}

ciUI2DPad::ciUI2DPad(const std::string &_name, const ciUIVec3f &_rangeX, const ciUIVec3f &_rangeY, ciUIVec3f *_value, float w, float h, float x, float y) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _rangeX, _rangeY, _value, w, h, x, y);
}

ciUI2DPad::~ciUI2DPad()
{
    if(!useReference)
    {
        delete valueRef;
    }
}

void ciUI2DPad::init(const std::string _name, const ciUIVec3f &_rangeX, const ciUIVec3f &_rangeY, ciUIVec3f *_value, float w, float h, float x, float y)
{
    initRect(x, y, w, h);
    name = string(_name);
    kind = CI_UI_WIDGET_2DPAD;
    draw_fill = true;
    draw_outline = true;
    value = *_value;                                               //the widget's value
    if(useReference)
    {
        valueRef = _value;
    }
    else
    {
        valueRef = new ciUIVec3f();
        *valueRef = value;
    }
    
    rangeX = _rangeX;
    rangeY = _rangeY;
    labelPrecision = 2;
    
    value.x = ciUIMap(value.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
    value.y = ciUIMap(value.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
    
    if(value.x > 1)
    {
        value.x = 1;
    }
    else if(value.x < 0)
    {
        value.x = 0;
    }
    
    if(value.y > 1)
    {
        value.y = 1;
    }
    else if(value.y < 0)
    {
        value.y = 0;
    }
    
    label = new ciUILabel(0,h+padding*2.0,(name+" LABEL"), (name + ": " + ciUIToString(getScaledValue().x,labelPrecision) + ", " + ciUIToString(getScaledValue().y,labelPrecision)), CI_UI_FONT_SMALL);
    addEmbeddedWidget(label);
    
    float horizontalRange = abs(rangeX.x - rangeX.y);
    float verticalRange = abs(rangeY.x - rangeY.y);
    increment = MIN(horizontalRange, verticalRange) / 10.0;
}

void ciUI2DPad::update()
{
    if(useReference)
    {
        value.x = ciUIMap(valueRef->x, rangeX.x, rangeX.y, 0.0, 1.0, true);
        value.y = ciUIMap(valueRef->y, rangeY.x, rangeY.y, 0.0, 1.0, true);
    }
}

void ciUI2DPad::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ciUI2DPad::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ciUI2DPad::drawFill()
{
    if(draw_fill)
    {
        ciUIFill();
        ciUISetColor(color_fill);
        ciUISetRectMode(CI_UI_RECTMODE_CENTER);
        ciUIDrawRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), CI_UI_GLOBAL_WIDGET_SPACING, CI_UI_GLOBAL_WIDGET_SPACING);
        ciUISetRectMode(CI_UI_RECTMODE_CORNER);
        
        ciUIDrawLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight());
        ciUIDrawLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight());
    }
}

void ciUI2DPad::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ciUIFill();
        ciUISetColor(color_fill_highlight);
        ciUISetRectMode(CI_UI_RECTMODE_CENTER);
        ciUIDrawRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), CI_UI_GLOBAL_WIDGET_SPACING, CI_UI_GLOBAL_WIDGET_SPACING);
        ciUISetRectMode(CI_UI_RECTMODE_CORNER);
        
        ciUIDrawLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight());
        ciUIDrawLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight());
        
        label->drawString(rect->getX()+value.x*rect->getWidth()+CI_UI_GLOBAL_WIDGET_SPACING, rect->getY()+value.y*rect->getHeight(), "(" +ciUIToString(getScaledValue().x,labelPrecision) + ", " + ciUIToString(getScaledValue().y,labelPrecision)+")");
    }
}

float ciUI2DPad::getIncrement()
{
    return increment;
}

void ciUI2DPad::setIncrement(float _increment)
{
    increment = _increment;
}

void ciUI2DPad::mouseMoved(int x, int y )
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

void ciUI2DPad::mouseDragged(int x, int y, int button)
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

void ciUI2DPad::mousePressed(int x, int y, int button)
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

void ciUI2DPad::mouseReleased(int x, int y, int button)
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

void ciUI2DPad::keyPressed(int key)
{
    if(state == CI_UI_STATE_OVER)
    {
        switch (key)
        {
            case OF_KEY_RIGHT:
            {
                ciUIVec3f p = getScaledValue();
                p.x+=increment;
                value.x = ciUIMap(p.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
                updateValueRef();
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            case OF_KEY_UP:
            {
                ciUIVec3f p = getScaledValue();
                p.y +=increment;
                value.y = ciUIMap(p.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
                updateValueRef();
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            case OF_KEY_LEFT:
            {
                ciUIVec3f p = getScaledValue();
                p.x-=increment;
                value.x = ciUIMap(p.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
                updateValueRef();
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            case OF_KEY_DOWN:
            {
                ciUIVec3f p = getScaledValue();
                p.y -=increment;
                value.y = ciUIMap(p.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
                updateValueRef();
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            default:
                break;
        }
    }
}

void ciUI2DPad::input(float x, float y)
{
    value.x = MIN(1.0, MAX(0.0, rect->percentInside(x, y).x));
    value.y = MIN(1.0, MAX(0.0, rect->percentInside(x, y).y));

    updateValueRef();
    updateLabel();
}

void ciUI2DPad::updateValueRef()
{
    (*valueRef) = getScaledValue();
}

void ciUI2DPad::updateLabel()
{
    label->setLabel(name + ": " + ciUIToString(getScaledValue().x,labelPrecision) + ", " + ciUIToString(getScaledValue().y,labelPrecision));
}

void ciUI2DPad::stateChange()
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

void ciUI2DPad::setValue(ciUIVec3f _value)
{
    if(_value.x > rangeX.y)
    {
        _value.x = rangeX.y;
    }
    else if(_value.x < rangeX.x)
    {
        _value.x = rangeX.x;
    }
    
    if(_value.y > rangeY.y)
    {
        _value.y = rangeY.y;
    }
    else if(_value.y < rangeY.x)
    {
        _value.y = rangeY.x;
    }
    
    value.x = ciUIMap(_value.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
    value.y = ciUIMap(_value.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}

ciUIVec3f ciUI2DPad::getValue()
{
    return value;
}

ciUIVec3f ciUI2DPad::getPercentValue()
{
    return value;
}

ciUIVec3f ciUI2DPad::getScaledValue()
{
    ciUIVec3f p = value;
    p.x = ciUIMap(p.x, 0, 1, rangeX.x, rangeX.y, true);
    p.y = ciUIMap(p.y, 0, 1, rangeY.x, rangeY.y, true);
    return p;
}

bool ciUI2DPad::isDraggable()
{
    return true;
}

void ciUI2DPad::setLabelPrecision(int _precision)
{
    labelPrecision = _precision;
    updateValueRef();
    updateLabel();
}

//#ifndef CI_UI_NO_XML
//
//void ciUI2DPad::saveState(ofxXmlSettings *XML)
//{
//    XML->setValue("XValue", getScaledValue().x, 0);
//    XML->setValue("YValue", getScaledValue().y, 0);
//}
//
//void ciUI2DPad::loadState(ofxXmlSettings *XML)
//{
//    setValue(ciUIVec3f(XML->getValue("XValue", getScaledValue().x, 0), XML->getValue("YValue", getScaledValue().y, 0)));
//}
//
//#endif
