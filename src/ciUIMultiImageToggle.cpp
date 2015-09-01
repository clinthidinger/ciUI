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

#include "ciUIMultiImageToggle.h"
#include "ciUI.h"

ciUIMultiImageToggle::ciUIMultiImageToggle(float x, float y, float w, float h, bool _value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIToggle()
{
    useReference = false;
    init(x, y, w, h, &_value, _pathURL, _name, _size);
}

ciUIMultiImageToggle::ciUIMultiImageToggle(float w, float h, bool _value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIToggle()
{
    useReference = false;
    init(0, 0, w, h, &_value, _pathURL, _name, _size);
}

ciUIMultiImageToggle::ciUIMultiImageToggle(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name,  int _size) : ciUIToggle()
{
    useReference = true;
    init(x, y, w, h, _value, _pathURL, _name, _size);
}

ciUIMultiImageToggle::ciUIMultiImageToggle(float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size) : ciUIToggle()
{
    useReference = true;
    init(0, 0, w, h, _value, _pathURL, _name, _size);
}


ciUIMultiImageToggle::~ciUIMultiImageToggle()
{
    delete down;
    delete back;
    delete over;
    delete on;
}

void ciUIMultiImageToggle::init(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size)
{
    initRect(x, y, w, h);
    name = string(_name);
    kind = CI_UI_WIDGET_MULTIIMAGETOGGLE;
    
    label = new ciUILabel(w+padding*2.0,0, (name+" LABEL"), name, _size);
    addEmbeddedWidget(label); 
    
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
    
    drawLabel = false;
    label->setVisible(drawLabel);
    
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
    
    back = new ci::Image(_pathURL);
    down = new ci::Image(coreURL+"down"+extension);
    over = new ci::Image(coreURL+"over"+extension);
    on = new ci::SImage(coreURL+"on"+extension);
}

void ciUIMultiImageToggle::drawBack()                     //NORMAL
{
    if(draw_back && !draw_fill)
    {
        ciUISetColor(255);
        back->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ciUIMultiImageToggle::drawOutlineHighlight()         //OVER
{
    if(draw_outline_highlight)
    {
        ciUISetColor(255);
        over->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ciUIMultiImageToggle::drawFill()
{
    if(draw_fill)
    {
        ciUISetColor(255);
        on->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ciUIMultiImageToggle::drawFillHighlight()            //DOWN/ON
{
    if(draw_fill_highlight)
    {
        ciUISetColor(255);
        down->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}


void ciUIMultiImageToggle::stateChange()
{
    switch (state) {
        case CI_UI_STATE_NORMAL:
        {
            draw_back = true;
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case CI_UI_STATE_OVER:
        {
            draw_back = false;
            draw_fill_highlight = false;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case CI_UI_STATE_DOWN:
        {
            draw_back = false;
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

void ciUIMultiImageToggle::setValue(bool _value)
{
    *value = _value;
    draw_fill = *value;
}
