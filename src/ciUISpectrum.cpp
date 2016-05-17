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

#include "ciUISpectrum.h"
#include "ciUI.h"

ciUISpectrum::ciUISpectrum(float x, float y, float w, float h, float *_buffer, int _bufferSize, float _min, float _max, const std::string &_name) : ciUIWaveform(x, y, w, h, _buffer, _bufferSize, _min, _max, _name)
{
    kind = CI_UI_WIDGET_SPECTRUM;
    scale = rect->getHeight();    
}

ciUISpectrum::ciUISpectrum(float w, float h, float *_buffer, int _bufferSize, float _min, float _max, const std::string &_name) : ciUIWaveform(0, 0, w, h, _buffer, _bufferSize, _min, _max, _name)
{
    kind = CI_UI_WIDGET_SPECTRUM;
    scale = rect->getHeight();
}

void ciUISpectrum::drawBack()
{
    ciUIWidget::drawBack();
}

void ciUISpectrum::drawFill()
{
    if(draw_fill)
    {
        
        ci::gl::ScopedColor scopedColor(draw_fill_highlight ? color_fill_highlight : color_fill);
        if(buffer != nullptr)
        {
            ci::gl::ScopedMatrices scopedMatrices;
            ci::gl::translate(rect->getX(), rect->getY()+scale, 0);
            shape.clear();
            shape.moveTo(0.0f, 0.0f);
            for (int i = 0; i < bufferSize; i++)
            {
                shape.lineTo(inc*(float)i, ciUIMap<float>(buffer[i], min, max, 0, -scale, true));
            }
            shape.lineTo((bufferSize-1)*inc, 0);
            shape.close();
            ci::gl::drawSolid(shape);
        }
    }
}
