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

#include "ciUIImage.h"
#include "ciUI.h"

ciUIImage::ciUIImage(float x, float y, float w, float h, ci::SurfaceRef _image, const std::string &_name) : ciUIWidgetWithLabel()
{
    init(x, y, w, h, _image, _name);
}

ciUIImage::ciUIImage(float x, float y, float w, float h, ci::SurfaceRef _image, const std::string &_name, bool _showLabel) : ciUIWidgetWithLabel()
{
    init(x, y, w, h, _image, _name);
    setLabelVisible(_showLabel);
}

ciUIImage::ciUIImage(float w, float h, ci::SurfaceRef _image, const std::string &_name) : ciUIWidgetWithLabel()
{
    init(0, 0, w, h, _image, _name);
}

ciUIImage::ciUIImage(float w, float h, ci::SurfaceRef _image, const std::string &_name, bool _showLabel) : ciUIWidgetWithLabel()
{
    init(0, 0, w, h, _image, _name);
    setLabelVisible(_showLabel);
}

void ciUIImage::init(float x, float y, float w, float h, ci::SurfaceRef _image, const std::string &_name)
{
    initRect(x,y,w,h);
    name = _name;
    kind = CI_UI_WIDGET_IMAGE;
    
    draw_back = false;
    draw_fill = true;
    
    image = _image;
    
    label = new ciUILabel(0,h+padding*2.0,(name+" LABEL"),name, CI_UI_FONT_SMALL);
    addEmbeddedWidget(label);
    cropImageToFitRect = false;
}

void ciUIImage::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ciUIImage::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ciUIImage::drawFill()
{
    if(draw_fill)
    {
        if(image != nullptr)
        {
            ciUIFill();
            ciUISetColor(255);
            if(cropImageToFitRect)
            {
                image->drawSubsection(rect->getX(), rect->getY(), rect->width, rect->height, 0, 0, rect->width, rect->height);
            }
            else
            {
                image->draw(rect->getX(), rect->getY(), rect->width, rect->height);
            }
        }
    }
}

void ciUIImage::setCropImageToFitRect(bool _cropImageToFitRect)
{
    cropImageToFitRect = _cropImageToFitRect;
}

void ciUIImage::setImage(ci:SurfaceRef _image)
{
    image = _image;
}

bool ciUIImage::isDraggable()
{
    return false;
}
