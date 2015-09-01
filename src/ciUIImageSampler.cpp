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

#include "ciUIImageSampler.h"
#include "ciUI.h"

ciUIImageSampler::ciUIImageSampler(float x, float y, float w, float h, ci::Image *_image, const std::string &_name) : ciUIImage(x, y, w, h, _image, _name)
{
    initSampler();
}

ciUIImageSampler::ciUIImageSampler(float w, float h, ci::Image *_image, const std::string &_name) : ciUIImage(w, h, _image, _name)
{
    initSampler();
}

void ciUIImageSampler::initSampler()
{
    setLabelVisible(false);
    value.x = .5;
    value.y = .5;
    input(value.x*rect->getWidth(),value.y*rect->getHeight());
    kind = CI_UI_WIDGET_IMAGESAMPLER;
    squareSize = CI_UI_GLOBAL_WIDGET_SPACING;
}

void ciUIImageSampler::setSquareSize(float _squareSize)
{
    squareSize = _squareSize;
}

void ciUIImageSampler::drawFill()
{
    if(draw_fill)
    {
        if(image != NULL)
        {
            ciUIFill();
            ciUISetColor(255);
            image->draw(rect->getX(), rect->getY(), rect->width, rect->height);
        }
        ciUISetColor(color_fill);
        ciUIDrawLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight());
        ciUIDrawLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight());
        
        ciUIFill();
        ciUISetColor(sampledColor);
        ciUISetRectMode(CI_UI_RECTMODE_CENTER);
        ciUIDrawRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), squareSize, squareSize);
        ciUISetRectMode(CI_UI_RECTMODE_CORNER);
        
    }
}

void ciUIImageSampler::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ciUISetColor(color_fill_highlight);
        ciUIDrawLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight());
        ciUIDrawLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight());
        
        ciUIFill();
        ciUISetColor(sampledColor);
        ciUISetRectMode(CI_UI_RECTMODE_CENTER);
        ciUIDrawRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), squareSize, squareSize);
        ciUISetRectMode(CI_UI_RECTMODE_CORNER);
    }
}

void ciUIImageSampler::mouseDragged(int x, int y, int button)
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

void ciUIImageSampler::mousePressed(int x, int y, int button)
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

void ciUIImageSampler::mouseReleased(int x, int y, int button)
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

void ciUIImageSampler::stateChange()
{
    switch (state) {
        case CI_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
        }
            break;
        case CI_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
        }
            break;
        case CI_UI_STATE_DOWN:
        {
            draw_fill_highlight = true;
            draw_outline_highlight = true;
        }
            break;
        case CI_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
        }
            break;
            
        default:
            break;
    }
}

void ciUIImageSampler::input(int x, int y)
{
    ciUIVec2f _v = rect->percentInside(x, y);
    setValue(_v);
}

ofColor& ciUIImageSampler::getColor()
{
    return sampledColor;
}

void ciUIImageSampler::setColor(const ci::Color &_sampledColor)
{
    sampledColor = _sampledColor;
}

ofPoint ciUIImageSampler::getValue()
{
    return value;
}

void ciUIImageSampler::setValue(const ci::vec2 &_value)
{
    value.x = MIN(1.0, MAX(0.0, _value.x));
    value.y = MIN(1.0, MAX(0.0, _value.y));
    sampledColor = image->getColor(value.x*(image->getWidth()-1), value.y*(image->getHeight()-1));
}

bool ciUIImageSampler::isDraggable()
{
    return true;
}

//#ifndef CI_UI_NO_XML
//
//void ciUIImageSampler::saveState(ofxXmlSettings *XML)
//{
//    XML->setValue("XValue", getValue().x, 0);
//    XML->setValue("YValue", getValue().y, 0);
//    XML->setValue("RColor", getColor().r, 0);
//    XML->setValue("GColor", getColor().g, 0);
//    XML->setValue("BColor", getColor().b, 0);
//    XML->setValue("AColor", getColor().a, 0);
//}
//
//void ciUIImageSampler::loadState(ofxXmlSettings *XML)
//{
//    setValue(ciUIVec2f(XML->getValue("XValue", getValue().x, 0), XML->getValue("YValue", getValue().y, 0)));
//    setColor(ciUIColor(XML->getValue("RColor", getColor().r, 0),
//                        XML->getValue("GColor", getColor().g, 0),
//                        XML->getValue("BColor", getColor().b, 0),
//                        XML->getValue("AColor", getColor().a, 0)));
//}
//
//#endif
