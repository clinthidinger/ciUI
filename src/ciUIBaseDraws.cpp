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

#include "ciUIBaseDraws.h"
#include "ciUI.h"

ciUIBaseDraws::ciUIBaseDraws(float x, float y, float w, float h, ofBaseDraws* _image, const std::string &_name) : ciUIWidgetWithLabel()
{
    init(x, y, w, h, _image, _name);
}

ciUIBaseDraws::ciUIBaseDraws(float x, float y, float w, float h, ofBaseDraws* _image, const std::string &_name, bool _showLabel) : ciUIWidgetWithLabel()
{
    init(x, y, w, h, _image, _name);
    setLabelVisible(_showLabel);
}

ciUIBaseDraws::ciUIBaseDraws(float w, float h, ofBaseDraws* _image, const std::string &_name) : ciUIWidgetWithLabel()
{
    init(0, 0, w, h, _image, _name);
}

ciUIBaseDraws::ciUIBaseDraws(float w, float h, ofBaseDraws* _image, const std::string &_name, bool _showLabel) : ciUIWidgetWithLabel()
{
    init(0, 0, w, h, _image, _name);
    setLabelVisible(_showLabel);
}

void ciUIBaseDraws::init(float x, float y, float w, float h, ofBaseDraws* _image, const std::string &_name)
{
    initRect(x, y, w, h);
    name = _name;
    kind = CI_UI_WIDGET_BASE_DRAWS;
    
    draw_back = false;
    draw_fill = true;
    
    image = _image;
    
    label = new ciUILabel(0,h+padding*2.0,(name+" LABEL"),name, CI_UI_FONT_SMALL);
    addEmbeddedWidget(label);
}

void ciUIBaseDraws::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ciUIBaseDraws::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ciUIBaseDraws::drawFill()
{
    ofSetDepthTest(false);
    if(draw_fill)
    {
        if(image != NULL)
        {
            ofFill();
            ofSetColor(255);
            image->draw(rect->getX(), rect->getY(), rect->width, rect->height);
        }
    }
}

void ciUIBaseDraws::set(ofBaseDraws *_image)
{
    image = _image;
}

bool ciUIBaseDraws::isDraggable()
{
    return false;
}
