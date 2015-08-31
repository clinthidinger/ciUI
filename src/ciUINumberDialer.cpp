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

#include "ciUINumberDialer.h"
#include "ciUI.h"
#include <math.h>

ciUINumberDialer::ciUINumberDialer(float x, float y, float _min, float _max, float _value, int _precision, string _name, int _size) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(x,y,0,0, _min, _max, &_value, _precision, _name, _size);
}

ciUINumberDialer::ciUINumberDialer(float _min, float _max, float _value, int _precision, string _name, int _size) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(0,0,0,0, _min, _max, &_value, _precision, _name, _size);
}

ciUINumberDialer::ciUINumberDialer(float x, float y, float _min, float _max, float *_value, int _precision, string _name, int _size) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(x,y,0,0, _min, _max, _value, _precision, _name, _size);
}

ciUINumberDialer::ciUINumberDialer(float _min, float _max, float *_value, int _precision, string _name, int _size) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(0,0,0,0, _min, _max, _value, _precision, _name, _size);
}

ciUINumberDialer::~ciUINumberDialer()
{
    if(!useReference)
    {
        delete value;
    }
}

void ciUINumberDialer::init(float x, float y, float w, float h, float _min, float _max, float *_value, int _precision, string _name, int _size)
{
    initRect(x, y, w, h);
    name = string(_name);
    kind = CI_UI_WIDGET_NUMBERDIALER;
    
    if(useReference)
    {
        value = _value;
    }
    else
    {
        value = new float();
        *value = (*_value);
    }
    
    max = _max;
    min = _min;
    if(*value > max)
    {
        *value = max;
    }
    else if(*value < min)
    {
        *value = min;
    }
    precision = _precision;
    currentPrecisionZone = 1;
    
    string minString = ciUIToString(min, precision);
    string maxString = ciUIToString(max, precision);
    if(minString.length() > maxString.length())
    {
        textstring = minString;
    }
    else
    {
        textstring = "+"+maxString;
    }
    
    string temp = "";
    if(precision > 0)
    {
        temp+="..";
        hasPeriod = 1;
    }
    else
    {
        temp += "+";
        hasPeriod = 0;
    }
    
    numOfPrecisionZones = textstring.length()-1;             //1 for the "-/+" sign & 1 for the "."
    
    displaystring = textstring;
    
    for(int i = 0; i < numOfPrecisionZones; i++)
    {
        temp+="0";
    }
    
    draw_fill = true;
    
    label = new ciUILabel(0,0,(name+" LABEL"), temp, _size);
    addEmbeddedWidget(label);
}

void ciUINumberDialer::update()
{
    if(useReference)
    {
        setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
    }
}


void ciUINumberDialer::drawFill()
{
    if(draw_fill)
    {
        ciUIFill();
        ciUISetColor(color_fill);
        float x = rect->getX()+padding;
        float y = label->getRect()->getY()+label->getRect()->getHeight();
        float w = label->getStringWidth("_");
        
        for(unsigned int i = 0; i < displaystring.size(); i++)
        {
            float tw = label->getStringWidth(displaystring.substr(i,1));
            float delta = w/2.0 - tw/2.0;
            label->drawString(x+i*w+delta, y, displaystring.substr(i,1));
        }
    }
}

void ciUINumberDialer::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ciUIFill();
        ciUISetColor(color_fill_highlight);
        float x = rect->getX()+padding;
        float y = label->getRect()->getY()+label->getRect()->getHeight();
        float w = label->getStringWidth("_");
        ciUIDrawRect(x+currentPrecisionZone*w,y+padding*.5,w, padding*.5);
        
        for(unsigned int i = 0; i < displaystring.size(); i++)
        {
            float tw = label->getStringWidth(displaystring.substr(i,1));
            float delta = w/2.0 - tw/2.0;
            label->drawString(x+i*w+delta, y, displaystring.substr(i,1));
        }
    }
}

void ciUINumberDialer::calculatePrecisionZone()
{
    currentPrecisionZone = ceil(ciUIMap(hitPoint.x,rect->getX(),rect->getX()+rect->getWidth(),-1, displaystring.size()-1, true));
    if(currentPrecisionZone == 0)
    {
        zoneMultiplier = powf(10.0, numOfPrecisionZones-precision-hasPeriod);
    }
    else if(currentPrecisionZone <= numOfPrecisionZones-precision)
    {
        zoneMultiplier = powf(10.0, numOfPrecisionZones-precision-hasPeriod-currentPrecisionZone);
    }
    else
    {
        zoneMultiplier = powf(10.0, numOfPrecisionZones-currentPrecisionZone-precision);
    }
}

float ciUINumberDialer::getMax()
{
    return max;
}
float ciUINumberDialer::getMin()
{
    return min;
}

float ciUINumberDialer::getValue()
{
    return *value;
}

void ciUINumberDialer::setValue(float _value)
{
    if(_value > max)
    {
        _value = max;
    }
    else if(_value < min)
    {
        _value = min;
    }
    *value = _value;
    setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
}

void ciUINumberDialer::mouseMoved(int x, int y )
{
    if(rect->inside(x, y))
    {
        state = CI_UI_STATE_OVER;
        hitPoint = ofPoint(x,y);
        calculatePrecisionZone();
        
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUINumberDialer::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        *value += zoneMultiplier*(hitPoint.y-y);
        if(*value > max)
        {
            *value = max;
        }
        else if(*value < min)
        {
            *value = min;
        }
        hitPoint = ofPoint(x,y);
        setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
        triggerEvent(this);
        state = CI_UI_STATE_DOWN;
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUINumberDialer::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        hitPoint = ofPoint(x,y);
        calculatePrecisionZone();
        state = CI_UI_STATE_DOWN;
        triggerEvent(this);
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUINumberDialer::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
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

void ciUINumberDialer::keyPressed(int key)
{
    if(state == CI_UI_STATE_OVER)
    {
        switch (key)
        {
            case OF_KEY_RIGHT:
                *value += zoneMultiplier;
                if(*value > max)
                {
                    *value = max;
                }
                else if(*value < min)
                {
                    *value = min;
                }
                
                setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
                triggerEvent(this);
                break;
                
            case OF_KEY_UP:
                *value += zoneMultiplier;
                if(*value > max)
                {
                    *value = max;
                }
                else if(*value < min)
                {
                    *value = min;
                }
                
                setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
                triggerEvent(this);
                break;
                
            case OF_KEY_LEFT:
                *value -= zoneMultiplier;
                if(*value > max)
                {
                    *value = max;
                }
                else if(*value < min)
                {
                    *value = min;
                }
                
                setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
                triggerEvent(this);
                break;
                
            case OF_KEY_DOWN:
                *value -= zoneMultiplier;
                if(*value > max)
                {
                    *value = max;
                }
                else if(*value < min)
                {
                    *value = min;
                }
                
                setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
                triggerEvent(this);
                break;
                
            default:
                break;
        }
    }
}

void ciUINumberDialer::keyReleased(int key)
{
    
}

void ciUINumberDialer::windowResized(int w, int h)
{
    
}

void ciUINumberDialer::stateChange()
{
    switch (state) {
        case CI_UI_STATE_NORMAL:
        {
            draw_fill = true;
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case CI_UI_STATE_OVER:
        {
            draw_fill = false;
            draw_fill_highlight = true;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case CI_UI_STATE_DOWN:
        {
            draw_fill = false;
            draw_fill_highlight = true;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case CI_UI_STATE_SUSTAINED:
        {
            draw_fill = true;
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
            
        default:
            break;
    }
}

string ciUINumberDialer::getTextString()
{
    return textstring;
}

void ciUINumberDialer::setTextString(string s)
{
    if(*value > 0)
    {
        s = "+" + s;
    }
    else
    {
        s = "-" + s;
    }
    textstring = s;
    displaystring = s;
}

void ciUINumberDialer::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    rect->height = label->getPaddingRect()->height+padding*2.0;
    rect->width = label->getPaddingRect()->width+padding*3.0;
    ciUIRectangle *labelrect = label->getRect();
    labelrect->setX(padding*2.0);
    float h = labelrect->getHeight();
    float ph = rect->getHeight();    
    labelrect->setY(ph/2.0 - h/2.0);
    labelrect->setX(rect->getWidth()+padding);
    label->setLabel(name); 
    setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
    calculatePaddingRect();    
}

bool ciUINumberDialer::isDraggable()
{
    return true;
}

string ciUINumberDialer::numToString(float value, int precision, int width, char fill )
{
    ostringstream out;
    out << fixed << setfill(fill) << setw(width) << setprecision(precision) << value;
    return out.str();
}

#ifndef CI_UI_NO_XML

void ciUINumberDialer::saveState(ofxXmlSettings *XML)
{
    XML->setValue("Value", getValue(), 0);
}

void ciUINumberDialer::loadState(ofxXmlSettings *XML)
{
    setValue(XML->getValue("Value", getValue(), 0));
}

#endif
