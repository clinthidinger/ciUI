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

#include "ciUIImageButton.h"
#include "ciUI.h"

ciUIImageButton::ciUIImageButton() : ciUIButton()
{
    
}

ciUIImageButton::ciUIImageButton(float x, float y, float w, float h, bool _value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIButton()
{
    useReference = false;
    init(x, y, w, h, &_value, _pathURL, _name, _size);
}

ciUIImageButton::ciUIImageButton(float w, float h, bool _value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIButton()
{
    useReference = false;
    init(0, 0, w, h, &_value, _pathURL, _name, _size);
}

ciUIImageButton::ciUIImageButton(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIButton()
{
    useReference = true;
    init(x, y, w, h, _value, _pathURL, _name, _size);
}

ciUIImageButton::ciUIImageButton(float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIButton()
{
    useReference = true;
    init(0, 0, w, h, _value, _pathURL, _name, _size);
}

void ciUIImageButton::init(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size)
{
    initRect(0,0,w,h);
    name = _name;
    kind = CI_UI_WIDGET_IMAGEBUTTON;
    
    label = new ciUILabel(w+padding,0, (name+" LABEL"), name, _size);
    addEmbeddedWidget(label);
    setLabelVisible(false); 
    
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
    
    img = new ofImage(_pathURL);
    bChangedImage = false;
}

ciUIImageButton::~ciUIImageButton()
{
    if(!bChangedImage)
    {
        delete img;
    }
}

void ciUIImageButton::drawBack()
{
    if(draw_back && !draw_fill)
    {
        ciUIFill();
        ciUISetColor(color_back);
        img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ciUIImageButton::drawFill()
{
    if(draw_fill)
    {
        ciUIFill();
        ciUISetColor(color_fill);
        img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ciUIImageButton::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ciUIFill();
        ciUISetColor(color_fill_highlight);
        img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ciUIImageButton::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        ofNoFill();
        ciUISetColor(color_outline_highlight);
        img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

ofImage *ciUIImageButton::getImage()
{
    return img;
}

void ciUIImageButton::setImage(ofImage *_img)
{
    if(img != nullptr && !bChangedImage)
    {
        delete img;
        img = nullptr;
    }
    img = _img;
    bChangedImage = true;
}
