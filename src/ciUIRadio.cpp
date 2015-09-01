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

#include "ciUIRadio.h"

ciUIRadio::ciUIRadio(const std::string &_name, const std::vector<std::string> &names, int _orientation, float w, float h, float x, float y, int _size) : ciUIWidget()
{
    init(_name, names, _orientation, w, h, x, y, _size);
}

void ciUIRadio::init(const std::string &_name, const std::vector<std::string> &names, int _orientation, float w, float h, float x, float y, int _size)
{
    initRect(x,y,w,h);
    name = string(_name);
    kind = CI_UI_WIDGET_RADIO;
    
    draw_back = false;
    orientation = _orientation;
    
    value = -1;
    
    if(names.size() == 0)
    {
        setEmbedded(true);
    }
    else
    {
        for(unsigned int i = 0; i < names.size(); i++)
        {
            std::string tname = names[i];
            ciUIToggle *toggle = new ciUIToggle(tname, false, w, h, 0, 0, _size);
            addEmbeddedWidget(toggle);
            toggles.push_back(toggle);            
        }
    }
    
    active = NULL;
}

void ciUIRadio::setVisible(bool _visible)
{
    visible = _visible;
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUIToggle *t = toggles[i];
        t->setVisible(visible);
    }
}

bool ciUIRadio::hasToggle(const std::string &_name)
{
	std::vector<ciUIToggle *>::iterator it = toggles.begin();
    std::vector<ciUIToggle *>::iterator eit = toggles.end();
    for(; it != eit; ++it)
    {
        ciUIToggle *t = (*it);
        if(t->getName() == _name)
        {
            return true;
        }
    }
    return false;
}

void ciUIRadio::activateToggle(const std::string &_name)
{
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUIToggle *t = toggles[i];
        if(t->getName() == _name)
        {
            t->setValue(true);
            active = t;
            value = i;
        }
        else
        {
            t->setValue(false);
        }
    }
}

void ciUIRadio::triggerSelf()
{
    if(parent != nullptr)
    {
        if(active != nullptr)
        {
            parent->triggerEvent(active);
        }
        parent->triggerEvent(this);
    }
}

void ciUIRadio::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    
    float tWidth = 0;
    float tHeight = 0;
    
    float xt = 0;
    float yt = 0;
    
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUIToggle *t = toggles[i];
        t->setParent(this);
        t->setRectParent(this->getRect());
        if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
        {
            t->getRect()->x = xt;
            t->getRect()->y = 0;
            xt+=t->getPaddingRect()->width;
            tHeight = t->getPaddingRect()->height;
        }
        else
        {
            t->getRect()->x = 0;
            t->getRect()->y = yt;
            if(t->getPaddingRect()->width > tWidth)
            {
                tWidth = t->getPaddingRect()->width;
            }
            tHeight+=t->getPaddingRect()->getHeight();
            yt +=t->getPaddingRect()->getHeight();
        }
    }
    
    if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
    {
        if(xt > tWidth)
        {
            tWidth = xt;
        }
    }
    rect->setWidth(tWidth - padding);
    rect->setHeight(tHeight - padding*2.0);
    calculatePaddingRect();
}

vector<ciUIToggle *> ciUIRadio::getToggles()
{
    return toggles;
}

ciUIToggle* ciUIRadio::getActive()
{
    return active;
}

void ciUIRadio::triggerEvent(ciUIWidget *child)
{
    activateToggle(child->getName());
    triggerSelf();
}

ciUIToggle *ciUIRadio::addToggle(ciUIToggle *toggle)
{
    toggle->setParent(this);
    toggles.push_back(toggle);
    if(toggle->getValue())
    {
        activateToggle(toggle->getName());
    }
    return toggle;
}

int ciUIRadio::getValue()
{
    return value;
}

string ciUIRadio::getActiveName()
{
    if(active != NULL)
    {
        return active->getName();
    }
    return ""; 
}
