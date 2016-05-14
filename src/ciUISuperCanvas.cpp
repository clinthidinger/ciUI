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

#include "ciUISuperCanvas.h"
#include "ciUI.h"


ciUISuperCanvas::ciUISuperCanvas(const ciUISuperCanvas &other)
: size(other.size),
title(other.title),
hitPoint(other.hitPoint),
deltaTime(other.deltaTime),
lastHitTime(other.lastHitTime),
bIsMinified(other.bIsMinified),
bTitleLabelHit(other.bTitleLabelHit)
{
    if (other.canvasTitle) {
        canvasTitle = new ciUILabel(*other.canvasTitle);
        headerWidgets.push_back(canvasTitle);
        addWidgetPosition(canvasTitle, widgetPosition, widgetAlign);
    }
    else {
        canvasTitle = nullptr;
    }
}

ciUISuperCanvas::ciUISuperCanvas(const std::string &_label, const ci::Rectf &r, int _size) : ciUICanvas(r)
{
    superInit(_label, _size);
}

ciUISuperCanvas::ciUISuperCanvas(const std::string &_label, float x, float y, float w, float h, int _size) : ciUICanvas(x, y, w, h)
{
    superInit(_label, _size);
}

ciUISuperCanvas::ciUISuperCanvas(const std::string &_label, float x, float y, float w, float h, ciUICanvas *sharedResources, int _size) : ciUICanvas(x, y, w, h, sharedResources)
{
    superInit(_label, _size);
}

ciUISuperCanvas::ciUISuperCanvas(const std::string &_label, int _size) : ciUICanvas()
{
    superInit(_label, _size);
}

ciUISuperCanvas::ciUISuperCanvas(const std::string &_label, ciUICanvas *sharedResources, int _size) : ciUICanvas(sharedResources)
{
    superInit(_label, _size);
}

void ciUISuperCanvas::superInit(const std::string &_label, int _size)
{
    size = _size;
    title = _label;
    kind = CI_UI_WIDGET_SUPERCANVAS;
    canvasTitle = new ciUILabel(rect->getWidth()-widgetSpacing*2, title, size);
    canvasTitle->setEmbedded(true);
    headerWidgets.push_back(canvasTitle);
    addWidgetPosition(canvasTitle, widgetPosition, widgetAlign);
    deltaTime = .35;
    lastHitTime = ci::app::getElapsedSeconds();
    bIsMinified = false;
    lastHitTime = 0;
    bTitleLabelHit = false;
    hitPoint = ciUIVec2f(0.0, 0.0);
}

void ciUISuperCanvas::setDeltaTime(float _deltaTime)
{
    deltaTime = _deltaTime;
}

void ciUISuperCanvas::setMinified(bool _bIsMinified)
{
    if(bIsMinified != _bIsMinified)
    {
        bIsMinified = _bIsMinified;
        if(bIsMinified)
        {
            minify();
        }
        else
        {
            maximize();
        }
    }
}

bool ciUISuperCanvas::isMinified()
{
    return bIsMinified;
}

void ciUISuperCanvas::toggleMinified()
{
    setMinified(!bIsMinified);
}

ciUILabel *ciUISuperCanvas::getCanvasTitle()
{
    return canvasTitle;
}

void ciUISuperCanvas::autoSizeToFitWidgets()
{
    ciUICanvas::autoSizeToFitWidgets();
    canvasTitle->getRect()->setWidth(rect->getWidth()-widgetSpacing*2);    
}

bool ciUISuperCanvas::didHitHeaderWidgets(float x, float y)
{
    std::vector<ciUIWidget *>::iterator it = headerWidgets.begin();
    std::vector<ciUIWidget *>::iterator eit = headerWidgets.end();
    for(; it != eit; ++it)
    {
        if((*it)->isHit(x, y))
        {
            return true;
        }
    }
    return false;
}

void ciUISuperCanvas::keyPressed(int key)
{
    if(getIsBindedToKey(key) && !bKeyHit)
    {
        bKeyHit = true;
        lastPosition = ciUIVec2f(rect->getX(), rect->getY());
        setMinified(false);
        ci::vec2 mousePos = ci::app::getMousePos();
        rect->setX(mousePos.x);
        rect->setY(mousePos.y);
        if(getTriggerType() & CI_UI_TRIGGER_BEGIN)
        {
            triggerEvent(this);
        }
    }

    ciUICanvas::keyPressed(key);
}

void ciUISuperCanvas::keyReleased(int key)
{
    if(getIsBindedToKey(key) && bKeyHit)
    {
        bKeyHit = false;
        if((ci::app::getElapsedSeconds() - lastHitTime) < deltaTime)
        {
            setMinified(false);
             ci::vec2 mousePos = ci::app::getMousePos();
            lastPosition = ciUIVec2f(mousePos.x, mousePos.y);
            if(getTriggerType() & CI_UI_TRIGGER_BEGIN)
            {
                triggerEvent(this);
            }
        }
        else
        {
            setMinified(true);
            rect->setX(lastPosition.x);
            rect->setY(lastPosition.y);
            if(getTriggerType() & CI_UI_TRIGGER_END)
            {
                triggerEvent(this);
            }
        }
        lastHitTime = ci::app::getElapsedSeconds();
    }
    ciUICanvas::keyReleased(key);
}

#ifdef CI_UI_TARGET_TOUCH

void ciUISuperCanvas::touchDown(float x, float y, int id)
{
    if(touchId == -1)
    {
        if(rect->inside(x, y) && didHitHeaderWidgets(x, y))
        {
            touchId = id;
            bTitleLabelHit = true;
            hitPoint.set(x - rect->getX(), y - rect->getY());
            return;
        }
    }
    canvasTouchDown(x, y, id);
}

void ciUISuperCanvas::touchMoved(float x, float y, int id)
{
    if(touchId == id)
    {
        if(bTitleLabelHit)
        {
            rect->setX(x - hitPoint.x);
            rect->setY(y - hitPoint.y);
            return;
        }
    }
    canvasTouchMoved(x, y, id);
}

void ciUISuperCanvas::touchUp(float x, float y, int id)
{
    if(touchId == id)
    {
        touchId = -1;
        bTitleLabelHit = false;
    }
    canvasTouchUp(x, y, id);
}

void ciUISuperCanvas::touchDoubleTap(float x, float y, int id)
{
    if(rect->inside(x, y) && didHitHeaderWidgets(x, y))
    {
        if(isMinified())
        {
            setMinified(false);
            if(getTriggerType() & CI_UI_TRIGGER_BEGIN)
            {
                triggerEvent(this);
            }
        }
        else
        {
            setMinified(true);
            if(getTriggerType() & CI_UI_TRIGGER_END)
            {
                triggerEvent(this);
            }
        }
        return;
    }
    canvasTouchDoubleTap(x, y, id);
}

void ciUISuperCanvas::touchCancelled(float x, float y, int id)
{
    if(touchId == id)
    {
        touchId = -1;
        bTitleLabelHit = false;
    }
    canvasTouchCancelled(x, y, id);
}

#else

void ciUISuperCanvas::onMouseReleased(ci::app::MouseEvent& data)
{
    bTitleLabelHit = false;
    mouseReleased(data.getX(), data.getY(), data.button);
}

void ciUISuperCanvas::onMousePressed(ci::app::MouseEvent& data)
{
    if(rect->inside(data.getX(), data.getY()) && didHitHeaderWidgets(data.x, data.y))
    {
        bTitleLabelHit = true;
        hitPoint.set(data.getX() - rect->getX(), data.getY() - rect->getY());
        
        if((ci::app::getElapsedSeconds() - lastHitTime) < deltaTime)
        {
            if(isMinified())
            {
                setMinified(false);
                if(getTriggerType() & CI_UI_TRIGGER_BEGIN)
                {
                    triggerEvent(this);
                }
            }
            else
            {
                setMinified(true);
                if(getTriggerType() & CI_UI_TRIGGER_END)
                {
                    triggerEvent(this);
                }
            }
            return;
        }
        lastHitTime = ci::app::getElapsedSeconds();
    }
    mousePressed(data.getX(), data.getY(), data.button);
}

void ciUISuperCanvas::onMouseDragged(ci::app::MouseEvent& data)
{
    if(bTitleLabelHit)
    {
        rect->setX(data.getX() - hitPoint.x);
        rect->setY(data.getY() - hitPoint.y);
        return;
    }
    mouseDragged(data.getX(), data.getY(), data.button);
}

#endif

#ifndef CI_UI_NO_XML

void ciUISuperCanvas::saveSettings(const std::string &fileName)
{
    ofxXmlSettings *XML = new ofxXmlSettings();
    XML->addTag("Canvas");
    XML->pushTag("Canvas", 0);
    XML->setValue("Kind", getKind(), 0);
    XML->setValue("Name", getName(), 0);
    XML->setValue("IsMinified", (bIsMinified ? 1 : 0), 0);
    XML->setValue("XPosition", rect->getX(), 0);
    XML->setValue("YPosition", rect->getY(), 0);
    XML->popTag();
    for(int i = 0; i < widgetsWithState.size(); i++)
    {
        int index = XML->addTag("Widget");
        if(XML->pushTag("Widget", index))
        {
            XML->setValue("Kind", widgetsWithState[i]->getKind(), 0);
            XML->setValue("Name", widgetsWithState[i]->getName(), 0);
            widgetsWithState[i]->saveState(XML);
        }
        XML->popTag();
    }
    XML->saveFile(fileName);
    delete XML;
}

void ciUISuperCanvas::loadSettings(const std::string & fileName)
{
    ofxXmlSettings *XML = new ofxXmlSettings();
    XML->loadFile(fileName);
    int widgetTags = XML->getNumTags("Widget");
    for(int i = 0; i < widgetTags; i++)
    {
        XML->pushTag("Widget", i);
        string name = XML->getValue("Name", "nullptr", 0);
        ciUIWidget *widget = getWidget(name);
        if(widget != nullptr && widget->hasState())
        {
            widget->loadState(XML);
            if(bTriggerWidgetsUponLoad)
            {
                triggerEvent(widget);
            }
        }
        XML->popTag();
    }
    XML->pushTag("Canvas", 0);
    int value = XML->getValue("IsMinified", (bIsMinified ? 1 : 0), 0);
    setMinified((value ? 1 : 0));
    rect->setX(XML->getValue("XPosition", rect->getX(), 0));
    rect->setY(XML->getValue("YPosition", rect->getY(), 0));
    XML->popTag();
    hasKeyBoard = false;
    delete XML;
}

#endif

void ciUISuperCanvas::addWidgetToHeader(ciUIWidget *widget)
{
    if(canvasTitle != nullptr)
    {
        float y = widget->getRect()->getY();
        float h = widget->getRect()->getHeight();
        float th = canvasTitle->getRect()->getHeight();
        float dh = (h-th)*0.5;
        canvasTitle->getRect()->setY(y + dh);
    }
    headerWidgets.push_back(widget);
}

void ciUISuperCanvas::removeWidgets()
{
    ciUICanvas::removeWidgets();
    headerWidgets.clear();
    resetPlacer(); 
    canvasTitle = new ciUILabel(rect->getWidth()-widgetSpacing*2, title, size);
    canvasTitle->setEmbedded(true);
    headerWidgets.push_back(canvasTitle);
    addWidgetPosition(canvasTitle, CI_UI_WIDGET_POSITION_DOWN, CI_UI_ALIGN_FREE);
}

void ciUISuperCanvas::minify()
{
    for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        ciUIWidget *w = (*it);
        if(w != nullptr)
        {
            w->setVisible(false);
        }
    }
    for(std::vector<ciUIWidget *>::iterator it = headerWidgets.begin(); it != headerWidgets.end(); ++it)
    {
        ciUIWidget *w = (*it);
        if(w != nullptr)
        {
            w->setVisible(true);
        }
    }
    autoSizeToFitWidgets();
}

void ciUISuperCanvas::maximize()
{
    for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        ciUIWidget *w = (*it);
        if(w != nullptr)
        {
            w->setVisible(true);
        }
    }
    autoSizeToFitWidgets();
}
