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

#include "ciUIImageToggle.h"
#include "ciUI.h"

ciUIImageToggle::ciUIImageToggle(float x, float y, float w, float h, bool _value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIToggle()
{
    useReference = false;
    init(x, y, w, h, &_value, _pathURL, _name, _size);
}

ciUIImageToggle::ciUIImageToggle(float w, float h, bool _value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIToggle()
{
    useReference = false;
    init(0, 0, w, h, &_value, _pathURL, _name, _size);
}

ciUIImageToggle::ciUIImageToggle(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIToggle()
{
    useReference = true;
    init(x, y, w, h, _value, _pathURL, _name, _size);
}

ciUIImageToggle::ciUIImageToggle(float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIToggle()
{
    useReference = true;
    init(0, 0, w, h, _value, _pathURL, _name, _size);
}

void ciUIImageToggle::init(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size)
{
    initRect(x, y, w, h);
    name = _name;
    kind = CI_UI_WIDGET_IMAGETOGGLE;
    
    label = new ciUILabel(w+padding,0, (name+" LABEL"), name, _size);
    addEmbeddedWidget(label);
    drawLabel = false;
    label->setVisible(drawLabel);
    
    if(useReference)
    {
        value = _value;
    }
    else
    {
        value = new bool();
        *value = *_value;
    }
    
    setValue(*_value);
    
    img = ci::Surface::create(ci::loadImage(_pathURL));
    tex = ci::gl::Texture2d::create(*img);
    bChangedImage = false;
}

ciUIImageToggle::~ciUIImageToggle()
{
    if(!bChangedImage)
    {
        //delete img;
    }
}

void ciUIImageToggle::drawBack()
{
    if(draw_back && !draw_fill)
    {
        //ciUIFill();
        //ci::gl::ScopedColor scopedColor(color_back);
        //img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
        ci::gl::ScopedColor scopedColor(color_back);
        ci::gl::draw(tex, rect->getRectf());
    }
}

void ciUIImageToggle::drawFill()
{
    if(draw_fill)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill);
        ci::gl::draw(tex, rect->getRectf());
    }
}

void ciUIImageToggle::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill_highlight);
        ci::gl::draw(tex, rect->getRectf());
    }
}

void ciUIImageToggle::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        //ofNoFill();
        ci::gl::ScopedColor scopedColor(color_outline_highlight);
        ci::gl::draw(tex, rect->getRectf());
    }
}

const ci::SurfaceRef &ciUIImageToggle::getImage() const
{
    return img;
}

void ciUIImageToggle::setImage(const ci::SurfaceRef &_img)
{
    if(img != nullptr && !bChangedImage)
    {
        //delete img;
        //img = nullptr;
        img.reset();
        tex.reset();
    }
    img = _img;
    tex = ci::gl::Texture2d::create(*img);
    bChangedImage = true;
}
