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

#pragma once

#include "ciUIWidgetWithLabel.h"

class ciUIBaseDraws : public ciUIWidgetWithLabel
{
public:
    ciUIBaseDraws(float x, float y, float w, float h, const ci::SurfaceRef &_image, const std::string &_name);
    ciUIBaseDraws(float x, float y, float w, float h, const ci::SurfaceRef &_image, const std::string &_name, bool _showLabel);
    ciUIBaseDraws(float w, float h, const ci::SurfaceRef &_image, const std::string &_name);
    ciUIBaseDraws(float w, float h, const ci::SurfaceRef &_image, const std::string &_name, bool _showLabel);
    virtual ~ciUIBaseDraws();
    void init(float x, float y, float w, float h, const ci::SurfaceRef &_image, const std::string &_name);
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawFill();
    void set(const ci::SurfaceRef &_image);
    virtual bool isDraggable();
    
protected:
	ci::SurfaceRef image;
    ci::gl::Texture2dRef tex;
};
