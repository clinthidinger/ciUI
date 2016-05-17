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

#include "ciUILabel.h"
#include "ciUI.h"

ciUILabel::ciUILabel() : ciUIWidget()
{
    
}

ciUILabel::ciUILabel(float x, float y, const std::string &_name, const std::string &_label, int _size) : ciUIWidget()
{
    init(x, y, 0, 0, _name, _label, _size);
    autoSize = true;
}

ciUILabel::ciUILabel(float x, float y, const std::string &_name, int _size) : ciUIWidget()
{
    init(x, y, 0, 0, _name, _name, _size);
    autoSize = true;
}

ciUILabel::ciUILabel(const std::string &_name, const std::string &_label, int _size) : ciUIWidget()
{
    init(0, 0, 0, 0, _name, _label, _size);
    autoSize = true;
}

ciUILabel::ciUILabel(const std::string &_name, int _size) : ciUIWidget()
{
    init(0, 0, 0, 0, _name, _name, _size);
    autoSize = true;
}

ciUILabel::ciUILabel(float x, float y, float w, const std::string &_name, const std::string &_label, int _size) : ciUIWidget()
{
    init(x, y, w, 0, _name, _label, _size);
    autoSize = false;
}

ciUILabel::ciUILabel(float x, float y, float w, const std::string &_name, int _size) : ciUIWidget()
{
    init(x, y, w, 0, _name, _name, _size);
    autoSize = false;
}

ciUILabel::ciUILabel(float w, const std::string &_name, const std::string &_label, int _size) : ciUIWidget()
{
    init(0, 0, w, 0, _name, _label, _size);
    autoSize = false;
}

ciUILabel::ciUILabel(float w, const std::string &_name, int _size) : ciUIWidget()
{
    init(0, 0, w, 0, _name, _name, _size);
    autoSize = false;
}

ciUILabel::ciUILabel(float w, const std::string &_name, int _size, float h) : ciUIWidget()
{
    init(0, 0, w, h, _name, _name, _size);
    autoSize = false;
}

void ciUILabel::init(float x, float y, float w, float h, const std::string &_name, const std::string &_label, int _size)
{
    initRect(x,y,w,h);
    name = _name;
    kind = CI_UI_WIDGET_LABEL;
    label = _label;
    size = _size;
    
    font = nullptr;
    draw_back = CI_UI_LABEL_DRAW_BACK;
    draw_fill = true;
}

void ciUILabel::drawBack()
{
    if(draw_back)
    {
        drawBackLabel();
    }
}

void ciUILabel::drawFill()
{
    if(draw_fill)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill);
        font->drawString(label, ci::vec2(floor(rect->getX())+xOffset, floor(rect->getY()+rect->getHeight())+yOffset));
    }
}

void ciUILabel::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill_highlight);
        font->drawString(label, ci::vec2(floor(rect->getX())+xOffset, floor(rect->getY()+rect->getHeight())+yOffset));
    }
}

void ciUILabel::drawBackLabel()
{
    //ciUIFill();
    ci::gl::ScopedColor scopedColor(color_back);
    font->drawString(label, ci::vec2(floor(rect->getX())+1+xOffset, floor(rect->getY()+rect->getHeight())+1+yOffset));
}

void ciUILabel::drawString(float x, float y, const std::string &_string)
{
    font->drawString(_string, ci::vec2(floor(x), floor(y)));
}

void ciUILabel::drawStringShadow(float x, float y, const std::string &_string)
{
    //ciUIFill();
    ci::gl::ScopedColor scopedColor(color_back);
    font->drawString(_string, ci::vec2(floor(x)+1, floor(y)+1));
}

float ciUILabel::getStringWidth(const std::string &s) const
{
    std::string s2(s);
    std::replace(s2.begin(), s2.end(), ' ', '_');      //VIA: @gameoverhack
    ci::vec2 size = font->measureString(s2);
    return size.x;
}

float ciUILabel::getStringHeight(const std::string & s) const
{
    ci::vec2 size = font->measureString(s);
    return size.y;
}

float ciUILabel::getLineHeight() const
{
    return 1;//???font->getLineHeight();
}

ciUILabel* ciUILabel::getLabelWidget()
{
    return this;
}

void ciUILabel::setLabel(const std::string & _label)
{
    label = _label;
    if(autoSize)
    {
        float w = font->measureString(label).x;
        float h = font->measureString("1").y;          //otherwise we get some funky non-uniform spacing :(
        rect->setWidth(w);
        rect->setHeight(h);
        xOffset = 0;
        yOffset = 0;
    }
    else
    {
        while(getStringWidth(label) > rect->getWidth()-padding*4.0 && label.size())
        {
            label = label.substr(0, label.size()-1);
        }
        float h = (int)font->measureString("1").y;     //otherwise we get some funky non-uniform spacing :(
        if(rect->getHeight() > 0)
        {
            yOffset = 0;
        }
        else
        {
            rect->setHeight(h);
            yOffset = 0;
        }
        xOffset = 0;
    }
}

bool ciUILabel::getAutoSize() const
{
    return autoSize;
}

void ciUILabel::setAutoSize(bool _autoSize)
{
    autoSize = _autoSize;
}

const std::string &ciUILabel::getLabel() const
{
    return label;
}

void ciUILabel::setFont(ci::gl::TextureFontRef _font)
{
    font = _font;
    setLabel(label);
    calculatePaddingRect();
}

int ciUILabel::getSize() const
{
    return size;
}

void ciUILabel::focus()
{
    draw_fill_highlight = true;
    draw_fill = false;
}

void ciUILabel::unfocus()
{
    draw_fill_highlight	= false;
    draw_fill = true;
}

void ciUILabel::setVisible(bool _visible)
{
    visible = _visible;
    if(parent != nullptr)
    {
        parent->calculatePaddingRect();
    }
}

bool ciUILabel::isVisible() const
{
    return visible;
}

void ciUILabel::toggleVisible()
{
    setVisible(!visible);
}
