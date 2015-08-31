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

#include "ciUITabBar.h"
#include "ciUI.h"

ciUITabBar::ciUITabBar() : ciUICanvas()
{
    initTabBar();
}

ciUITabBar::~ciUITabBar()
{
    ofRemoveListener(newGUIEvent, this, &ciUITabBar::mainUiEvent);
}

ciUITabBar::ciUITabBar(float x, float y, float w, float h) : ciUICanvas(x,y,w,h)
{
    initTabBar();
}

void ciUITabBar::initTabBar()
{
    kind = CI_UI_WIDGET_TABBAR;
    autoSizeToFitWidgets();
    ofAddListener(newGUIEvent, this, &ciUITabBar::mainUiEvent);
    active = NULL;
}

void ciUITabBar::addCanvas(ciUICanvas *_canvas)
{
    ciUIToggle* newToggle = addToggle(_canvas->getName(), false);
    canvases.insert ( pair<ciUIToggle*, ciUICanvas*>( newToggle, _canvas) );
    _canvas->disable();
    autoSizeToFitWidgets();
}

void ciUITabBar::addCanvas(ciUIScrollableCanvas *_canvas)
{
    ciUIToggle* newToggle = addToggle(_canvas->getName(), false);
    canvases.insert ( pair<ciUIToggle*, ciUICanvas*>( newToggle, _canvas) );
    _canvas->disable();
    autoSizeToFitWidgets();
}

void ciUITabBar::mainUiEvent(ciUIEventArgs &event)
{
    string name = event.getName();
    for (map<ciUIToggle*, ciUICanvas*>::iterator it=canvases.begin(); it!=canvases.end(); ++it)
    {
        if(active != NULL && active->getName() == name)
        {
            it->first->setValue(false);
            it->second->disable();
            active = NULL;
        }
        else if(it->second->getName() == name && event.getToggle()->getValue())
        {
            active = it->second;
            it->first->setValue(true);
            it->second->enable();
            it->second->setPosition(rect->getX() + rect->getWidth() + padding*0.5, this->rect->getY());
        }
        else
        {
            it->first->setValue(false);
            it->second->disable();
        }
    }
}

void ciUITabBar::enable()
{
    ciUICanvas::enable();
    
    if (active != NULL) {
        active->enable();
    }
}

void ciUITabBar::disable()
{
    ciUICanvas::disable();
    
    if (active != NULL) {
        active->disable();
    }
}

void ciUITabBar::toggleVisible()
{
    ciUICanvas::toggleVisible();
    
    if (active != NULL) {
        active->toggleVisible();
    }
}

ciUICanvas* ciUITabBar::getActiveCanvas()
{
    return active;
}

bool ciUITabBar::isHit(int x, int y)
{
    if (ciUICanvas::isHit(x, y)) {
        return true;
    } else {
        if (active != NULL) {
            return active->isHit(x, y);
        }
    }
    
    return false;
}

void ciUITabBar::saveSettings(string pathToSaveTo, string fileNamePrefix)
{
    for (map<ciUIToggle*, ciUICanvas*>::iterator it=canvases.begin(); it!=canvases.end(); ++it) {
        it->second->saveSettings(pathToSaveTo + fileNamePrefix + it->second->getName() + ".xml");
    }
}

void ciUITabBar::loadSettings(string pathToLoadFrom, string fileNamePrefix)
{
    for (map<ciUIToggle*, ciUICanvas*>::iterator it=canvases.begin(); it!=canvases.end(); ++it) {
        it->second->loadSettings(pathToLoadFrom + fileNamePrefix + it->second->getName() + ".xml");
    }
}
