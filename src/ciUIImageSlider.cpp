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

#include "ciUIImageSlider.h"
#include "ciUI.h"

ciUIImageSlider::ciUIImageSlider(float x, float y, float w, float h, float _min, float _max, float _value, const std::string &_pathURL, const std::string &_name) : ciUISlider()
{
    useReference = false;
    init(x, y, w, h, _min, _max, &_value, _pathURL, _name);
}

ciUIImageSlider::ciUIImageSlider(float w, float h, float _min, float _max, float _value, const std::string &_pathURL, const std::string &_name) : ciUISlider()
{
    useReference = false;
    init(0, 0, w, h, _min, _max, &_value, _pathURL, _name);
}

ciUIImageSlider::ciUIImageSlider(float x, float y, float w, float h, float _min, float _max, float *_value, const std::string &_pathURL, const std::string &_name) : ciUISlider()
{
    useReference = true;
    init(x, y, w, h, _min, _max, _value, _pathURL, _name);
}

ciUIImageSlider::ciUIImageSlider(float w, float h, float _min, float _max, float *_value, const std::string &_pathURL, const std::string &_name) : ciUISlider()
{
    useReference = true;
    init(0, 0, w, h, _min, _max, _value, _pathURL, _name);
}

void ciUIImageSlider::init(float x, float y, float w, float h, float _min, float _max, float *_value, const std::string &_pathURL, const std::string &_name)
{
    initRect(x, y, w, h);
    name = _name;
    if(w > h)
    {
        kind = CI_UI_WIDGET_IMAGESLIDER_H;
    }
    else
    {
        kind = CI_UI_WIDGET_IMAGESLIDER_V;
    }
    
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
    labelPrecision = 2;
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    value = ciUIMap<float>(value, min, max, 0.0f, 1.0f, true);
    
    if(kind == CI_UI_WIDGET_IMAGESLIDER_H)
    {
        label = new ciUILabel(0,h+padding,(name+" LABEL"), (name + ": " + ciUIToString(max,labelPrecision)), CI_UI_FONT_SMALL);
    }
    else
    {
        label = new ciUILabel(0,h+padding,(name+" LABEL"), name, CI_UI_FONT_SMALL);
    }
    
    addEmbeddedWidget(label);
    increment = fabs(max - min) / 10.0;
    
    std::string coreURL = _pathURL;
    std::string extension = "";
    std::string period (".");
    size_t found;
    
    found=_pathURL.find(period);
    if (found != std::string::npos)
    {
        coreURL = _pathURL.substr(0,found);
        extension = _pathURL.substr(found);
    }
    
    track = ci::gl::Texture2d::create(ci::loadImage(coreURL+"track"+extension));         //back
    
    trackleft = ci::gl::Texture2d::create(ci::loadImage(coreURL+"trackleft"+extension));         //back
    tlaspect = (float)trackleft->getWidth()/(float)trackleft->getHeight();
    
    trackright = ci::gl::Texture2d::create(ci::loadImage(coreURL+"trackright"+extension));         //back
    traspect = (float)trackright->getWidth()/(float)trackright->getHeight();
    
    progress = ci::gl::Texture2d::create(ci::loadImage(coreURL+"progress"+extension));      //fill
    
    progressright = ci::gl::Texture2d::create(ci::loadImage(coreURL+"progressright"+extension));      //fill
    
    progressleft = ci::gl::Texture2d::create(ci::loadImage(coreURL+"progressleft"+extension));      //fill
    
    handle = ci::gl::Texture2d::create(ci::loadImage(coreURL+"handle"+extension));        //handle
    
    handleDown = ci::gl::Texture2d::create(ci::loadImage(coreURL+"handledown"+extension));    //handleOver State
    
    handleHalfWidth = handle->getWidth()*.5;
    handleHalfHeight = handle->getHeight()*.5;
    
    if(kind == CI_UI_WIDGET_IMAGESLIDER_H)
    {
        ratio = rect->getHeight() / (float) track->getHeight();
        imageRect = new ciUIRectangle(handleHalfWidth*ratio,0,rect->getWidth()-handle->getWidth()*ratio, rect->getHeight());
        
    }
    else
    {
        ratio = rect->getWidth() /  (float) track->getWidth();
        imageRect = new ciUIRectangle(0,handleHalfHeight*ratio,rect->getWidth(), rect->getHeight()-handle->getHeight()*ratio);
    }
    imageRect->setParent(rect);
}

ciUIImageSlider::~ciUIImageSlider()
{
    //delete track;
    //delete trackleft;
    //delete trackright;
    //delete progress;
    //delete progressright;
    //delete progressleft;
    //delete handle;
    //delete handleDown;
    delete imageRect;
}


void ciUIImageSlider::drawBack()
{
    if(draw_back)
    {
        if(kind == CI_UI_WIDGET_IMAGESLIDER_H)
        {
            ci::gl::ScopedColor scopedColor(ci::Color::white());
            
            // CHECK rect params!!!
            ciUIDrawCorneredTex(trackleft, rect->getX(), rect->getY(), tlaspect*rect->getHeight(), rect->getHeight());
            ciUIDrawCorneredTex(trackright, rect->getX()+rect->getWidth()-traspect*rect->getHeight(), rect->getY(), traspect*rect->getHeight(), rect->getHeight());
            ciUIDrawCorneredTex(track, rect->getX()+rect->getHeight()*tlaspect-1, rect->getY(), rect->getWidth()-rect->getHeight()*tlaspect - rect->getHeight()*traspect + 1, rect->getHeight());
        }
    }
}

void ciUIImageSlider::drawOutline()
{
    if(draw_outline)
    {
        //ofNoFill();
        ci::gl::ScopedColor scopedColor(color_outline);
        rect->draw(true);
    }
}

void ciUIImageSlider::drawOutlineHighlight()
{
    
}

void ciUIImageSlider::drawFill()
{
    if(draw_fill)
    {
        ci::gl::ScopedColor scoledColor(ci::Color::white());
        if(kind == CI_UI_WIDGET_IMAGESLIDER_H)
        {
            if(value > 0.00)
            {
                ciUIDrawCorneredTex(progressleft, rect->getX(), rect->getY(), tlaspect*rect->getHeight(), rect->getHeight());
            }
            ciUIDrawCorneredTex(progress, rect->getX()+rect->getHeight()*tlaspect - 1,rect->getY(),(rect->getWidth() - 2.0*rect->getHeight()*tlaspect)*value + 1, rect->getHeight());
            
            if(value > .99)
            {
                ciUIDrawCorneredTex(progressright, rect->getX()+rect->getWidth() - tlaspect*rect->getHeight(), rect->getY(), tlaspect *rect->getHeight(), rect->getHeight());
            }
            ci::gl::ScopedColor scoledColor2(ci::Color::white());
            ciUIDrawCenteredTex(handle, imageRect->getX()+value*imageRect->getWidth(), rect->getY()+rect->getHalfHeight(), ratio*handle->getWidth(), ratio*handle->getHeight());
        }
    }
}

void ciUIImageSlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ci::gl::ScopedColor scoledColor(ci::Color::white());
        if(kind == CI_UI_WIDGET_IMAGESLIDER_H)
        {
            if(value > 0.00)
            {
                ciUIDrawCorneredTex(progressleft, rect->getX(), rect->getY(), tlaspect*rect->getHeight(), rect->getHeight());
            }
            ciUIDrawCorneredTex(progress, rect->getX()+rect->getHeight()*tlaspect-1,rect->getY(),(rect->getWidth() - 2.0*rect->getHeight()*tlaspect)*value + 1, rect->getHeight());
            
            if(value > .99)
            {
                ciUIDrawCorneredTex(progressright, rect->getX()+rect->getWidth() - tlaspect*rect->getHeight(), rect->getY(), tlaspect*rect->getHeight(), rect->getHeight());
            }
            ci::gl::ScopedColor scoledColor2(ci::Color::white());
            ciUIDrawCenteredTex(handleDown, imageRect->getX()+value*imageRect->getWidth(), rect->getY()+rect->getHalfHeight(), ratio*handle->getWidth(), ratio*handle->getHeight());
        }
        else
        {
            
            
        }
        if(kind == CI_UI_WIDGET_IMAGESLIDER_V)
        {
            label->drawString(imageRect->getX()+imageRect->getWidth()+padding, label->getRect()->getHeight()/2.0+imageRect->getY()+imageRect->getHeight()-imageRect->getHeight()*value, ciUIToString(getScaledValue(),labelPrecision));
        }
    }
}

void ciUIImageSlider::stateChange()
{
    switch (state) {
        case CI_UI_STATE_NORMAL:
        {
            draw_back = true;
            draw_fill = true;
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case CI_UI_STATE_OVER:
        {
            draw_back = true;
            draw_fill = true;
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case CI_UI_STATE_DOWN:
        {
            draw_back = true;
            draw_fill = false;
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

void ciUIImageSlider::input(float x, float y)
{
    if(kind == CI_UI_WIDGET_IMAGESLIDER_H)
    {
        value = std::min(1.0f, std::max(0.0f, imageRect->percentInside(x, y).x));
    }
    else
    {
        value = std::min(1.0f, std::max(0.0f, 1.0f - imageRect->percentInside(x, y).y));
    }

    updateValueRef();
    updateLabel();
}

void ciUIImageSlider::updateLabel()
{
    if(kind == CI_UI_WIDGET_IMAGESLIDER_H)
    {
        label->setLabel(name + ": " + ciUIToString(getScaledValue(),labelPrecision));
    }
}
