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

#include "ciUIWaveform.h"
#include "ciUI.h"

ciUIWaveform::ciUIWaveform(float x, float y, float w, float h, float *_buffer, int _bufferSize, float _min, float _max, const std::string &_name) : ciUIWidget()
{
    init(x, y, w, h, _buffer, _bufferSize, _min, _max, _name);
}

ciUIWaveform::ciUIWaveform(float w, float h, float *_buffer, int _bufferSize, float _min, float _max, const std::string &_name) : ciUIWidget()
{
    init(0, 0, w, h, _buffer, _bufferSize, _min, _max, _name);
}

void ciUIWaveform::init(float x, float y, float w, float h, float *_buffer, int _bufferSize, float _min, float _max, const std::string &_name)
{
    initRect(x,y,w,h);
    name = _name;
    kind = CI_UI_WIDGET_WAVEFORM;
    
    draw_fill = true;
    
    if(_buffer != nullptr)
    {
        setBuffer(_buffer);
    }
    else
    {
        setBuffer(nullptr);
    }
    
    setBufferSize(_bufferSize);
    max = _max;
    min = _min;
    scale = rect->getHeight()*.5;
}

void ciUIWaveform::drawBack()
{
    if(draw_back)
    {
        ciUIFill();
        ciUISetColor(color_back);
        rect->draw();
        
        ciUIDrawLine(rect->getX(), rect->getY()+rect->getHalfHeight(), rect->getX()+rect->getWidth(), rect->getY()+rect->getHalfHeight());
    }
}

void ciUIWaveform::drawFill()
{
    if(draw_fill)
    {
        ofNoFill();
        if(draw_fill_highlight)
        {
            ci::gl::color(color_fill_highlight);
        }
        else
        {
            ci::gl::color(color_fill);
        }
        if(buffer != nullptr)
        {
            //ofPushMatrix();
            ci::gl::ScopedMatrices scopedMatrices;
            ci::gl::translate(rect->getX(), rect->getY()+scale, 0);
            ci::gl::setLineWidth(1.5);
            ofBeginShape();
            for (int i = 0; i < bufferSize; i++)
            {
                ofVertex(inc*(float)i, ciUIMap(buffer[i], min, max, scale, -scale, true));
            }
            ofEndShape();
            ci::gl::setLineWidth(1);
            //ofPopMatrix();
        }
    }
}

void ciUIWaveform::setBuffer(float *_buffer)
{
    buffer = _buffer;
}

void ciUIWaveform::setBufferSize(int _bufferSize)
{
    bufferSize = _bufferSize;
    inc = rect->getWidth()/((float)bufferSize-1.0);
}

void ciUIWaveform::setMax(float _max)
{
    max = _max;
}

float ciUIWaveform::getMax()
{
    return max;
}

void ciUIWaveform::setMin(float _min)
{
    min = _min;
}

float ciUIWaveform::getMin()
{
    return min;
}

ci::vec2 ciUIWaveform::getMaxAndMind()
{
    return ci::vec2f(max, min);
}

void ciUIWaveform::setMaxAndMin(float _max, float _min)
{
    max = _max;
    min = _min;
}
