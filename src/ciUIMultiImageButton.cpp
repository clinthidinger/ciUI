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

#include "ciUIMultiImageButton.h"
#include "ciUI.h"

ciUIMultiImageButton::ciUIMultiImageButton(float x, float y, float w, float h, bool _value, string _pathURL, string _name, int _size) : ciUIButton()
{
    useReference = false;
    init(x, y, w, h, &_value, _pathURL, _name, _size);
}

ciUIMultiImageButton::ciUIMultiImageButton(float w, float h, bool _value, string _pathURL, string _name, int _size) : ciUIButton()
{
    useReference = false;
    init(0, 0, w, h, &_value, _pathURL, _name, _size);
}

ciUIMultiImageButton::ciUIMultiImageButton(float x, float y, float w, float h, bool *_value, string _pathURL, string _name, int _size) : ciUIButton()
{
    useReference = true;
    init(x, y, w, h, _value, _pathURL, _name, _size);
}

ciUIMultiImageButton::ciUIMultiImageButton(float w, float h, bool *_value, string _pathURL, string _name, int _size) : ciUIButton()
{
    useReference = true;
    init(0, 0, w, h, _value, _pathURL, _name, _size);
}

ciUIMultiImageButton::~ciUIMultiImageButton()
{
    delete back;
    delete over;
    delete on;
}

void ciUIMultiImageButton::init(float x, float y, float w, float h, bool *_value, string _pathURL, string _name, int _size)
{
    initRect(x,y,w,h);
    name = string(_name);
    kind = CI_UI_WIDGET_MULTIIMAGEBUTTON;
    
    label = new ciUILabel(w,0, (name+" LABEL"), name, _size);
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
    
    string coreURL = _pathURL;
    string extension = "";
    string period (".");
    size_t found;
    
    found=_pathURL.find(period);
    if (found!=string::npos)
    {
        coreURL = _pathURL.substr(0,found);
        extension = _pathURL.substr(found);
    }
    
    back = new ofImage(_pathURL);
    over = new ofImage(coreURL+"over"+extension);
    on = new ofImage(coreURL+"on"+extension);
}

void ciUIMultiImageButton::drawBack()                     //NORMAL
{
    if(draw_back)
    {
        ciUISetColor(255);
        back->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ciUIMultiImageButton::drawOutlineHighlight()         //OVER
{
    if(draw_outline_highlight)
    {
        ciUISetColor(255);
        over->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}

void ciUIMultiImageButton::drawFill()
{
    
}

void ciUIMultiImageButton::drawFillHighlight()            //DOWN/ON
{
    if(draw_fill_highlight)
    {
        ciUISetColor(255);
        on->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
    }
}


void ciUIMultiImageButton::stateChange()
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

void ciUIMultiImageButton::setValue(bool _value)
{
    *value = _value;
    draw_fill = *value;
}
