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

#include "ciUIDropDownList.h"
#include "ciUI.h"

ciUIDropDownList::ciUIDropDownList(const std::string &_name, const std::vector<std::string> &items, float w, float x, float y, int _size) : ciUIToggle()
{
    init(_name, items, w, x, y, _size);
}
ciUIDropDownList::ciUIDropDownList(float x, float y, float w, const std::string &_name, const std::vector<std::string> &items, int _size)
{
    init(_name, items, w, x, y, _size);
}
ciUIDropDownList::ciUIDropDownList(float w, const std::string &_name, const std::vector<std::string> &items, int _size)
{
    init(_name, items, w, _size);
}
ciUIDropDownList::ciUIDropDownList(float x, float y, const std::string &_name, const std::vector<std::string> &items, int _size)
{
    init(_name, items, 0, x, y, _size);
}

void ciUIDropDownList::init(const std::string &_name, const std::vector<std::string> &items, float w, float x, float y, int _size)
{
    initRect(x,y,w,0);
    autoSize = (w == 0) ? true : false;
    name = string(_name);
    kind = CI_UI_WIDGET_DROPDOWNLIST;
    
    size = _size;
    label = new ciUILabel(0,0,(name+" LABEL"), name, _size);
    addEmbeddedWidget(label);
    
    value = new bool();
    *value = false;
    draw_fill = *value;

    bShowCurrentSelected = false;
    allowMultiple = false;
    addToggles(items);
    autoClose = false;
    singleSelected = NULL;
}

void ciUIDropDownList::clearToggles()
{
    while(toggles.size())
    {
        ciUILabelToggle *t = toggles[0];
        removeToggle(t->getName());
    }
}

void ciUIDropDownList::clearSelected()
{
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        toggles[i]->setValue(false);
    }
    selected.clear();
    selectedIndeces.clear();
}

void ciUIDropDownList::addToggle(const std::string &toggleName)
{
    float yt = rect->getHeight();
    
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUILabelToggle *t = toggles[i];
        yt +=t->getRect()->getHeight();
    }
    
    ciUILabelToggle *ltoggle;
    if(autoSize)
    {
        ltoggle = new ciUILabelToggle(toggleName, false, 0, 0, 0, 0, size);
    }
    else
    {
        ltoggle = new ciUILabelToggle(toggleName, false, rect->getWidth(), rect->getHeight(), 0, 0, size);
    }
    ltoggle->getRect()->setY(yt);
    ltoggle->getRect()->setX(0);
    ltoggle->setVisible(*value);
    addEmbeddedWidget(ltoggle);
    toggles.push_back(ltoggle);
    if(parent != NULL)
    {
        parent->addWidget(ltoggle);
        
    }
    ltoggle->setParent(this);
    ltoggle->setRectParent(rect);    
    ltoggle->setModal(modal);
    if(isOpen())
    {
        open();
    }
    else
    {
        close();
    }
}

void ciUIDropDownList::addToggles(vector<string>& toggleNames)
{
    for(unsigned int i = 0; i < toggleNames.size(); i++){
        addToggle(toggleNames[i]);
    }
}

void ciUIDropDownList::removeToggle(string toggleName)
{
    ciUILabelToggle *t = NULL;
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUILabelToggle *other = (ciUILabelToggle *)toggles[i];
        if(other->getName() == toggleName)
        {
            t = other;
            toggles.erase(toggles.begin()+i);
            break;
        }
    }
    for(unsigned int i = 0; i < selected.size(); i++)
    {
        ciUILabelToggle *other = (ciUILabelToggle *)selected[i];
        if(other->getName() == toggleName)
        {
            selected.erase(selected.begin()+i);
            selectedIndeces.erase(selectedIndeces.begin()+i);
            break;
        }
    }
    if(t != NULL)
    {
        parent->removeWidget(t);
        
        float yt = rect->getHeight();
        for(unsigned int i = 0; i < toggles.size(); i++)
        {
            ciUILabelToggle *t = toggles[i];
            t->getRect()->setY(yt);
            t->getRect()->setX(0);
            yt +=t->getRect()->getHeight();
        }
    }
}

bool* ciUIDropDownList::getShowCurrentSelectedPtr()
{
    return &bShowCurrentSelected;
}

bool ciUIDropDownList::getShowCurrentSelected()
{
    return bShowCurrentSelected;
}

void ciUIDropDownList::setShowCurrentSelected(bool _bShowCurrentSelected)
{
    bShowCurrentSelected = _bShowCurrentSelected;
    checkAndSetTitleLabel();
}

void ciUIDropDownList::checkAndSetTitleLabel()
{
    if(bShowCurrentSelected && selected.size() > 0)
    {
        string title = "";
        int index = 0;
        for(vector<ciUIWidget *>::iterator it = selected.begin(); it != selected.end(); it++)
        {
            if(index == 0)
            {
                title+=(*it)->getName();
            }
            else
            {
                title+=","+(*it)->getName();
            }
            index++;
        }
        if(title.length())
        {
            setLabelText(title);
        }
    }
    else
    {
        setLabelText(name);
    }
}

vector<ciUIWidget *> & ciUIDropDownList::getSelected()
{
    return selected;
}

vector<int> & ciUIDropDownList::getSelectedIndeces()
{
    return selectedIndeces;
}

vector<string> ciUIDropDownList::getSelectedNames()
{
    vector<string> names;
    
    for(vector<ciUIWidget *>::iterator it = selected.begin(); it != selected.end(); ++it)
    {
        ciUILabelToggle *lt = (ciUILabelToggle *) (*it);
        names.push_back(lt->getName());
    }
    return names;
}

void ciUIDropDownList::setLabelText(string labeltext)
{
    label->setLabel(labeltext);
    if(!autoSize)
    {
        ciUIRectangle *labelrect = label->getRect();
        float h = labelrect->getHeight();
        float ph = rect->getHeight();
        float w = labelrect->getWidth();
        float pw = rect->getWidth();
        labelrect->setY((int)(ph*.5 - h*.5));
        labelrect->setX((int)(pw*.5 - w*.5-padding*.5));
    }
}

void ciUIDropDownList::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    rect->setHeight(label->getPaddingRect()->getHeight()+padding*2.0);
    ciUIRectangle *labelrect = label->getRect();
    if(autoSize)
    {
        rect->setWidth(label->getPaddingRect()->getWidth()+padding*2.0);
    }
    else
    {
        while(labelrect->getWidth()+padding*4.0 > rect->getWidth())
        {
            string labelstring = label->getLabel();
            string::iterator it;
            it=labelstring.end();
            it--;
            labelstring.erase (it);
            label->setLabel(labelstring);
        }
    }
    
    float h = labelrect->getHeight();
    float ph = rect->getHeight();
    float w = labelrect->getWidth();
    float pw = rect->getWidth();
    
    labelrect->setY((int)(ph*.5 - h*.5));
    labelrect->setX((int)(pw*.5 - w*.5-padding*.5));
    
    float yt = rect->getHeight();
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUILabelToggle *toggle = (ciUILabelToggle *)toggles[i];
        ciUIRectangle *trect = toggle->getRect();
        toggle->setParent(this);
        trect->setParent(rect);
        trect->setY(yt);
        yt+=trect->getHeight();
    }
    paddedRect->set(-padding, -padding, rect->getWidth()+padding*2.0, rect->getHeight()+padding*2.0);
}

void ciUIDropDownList::mouseReleased(int x, int y, int button)
{
    if(rect->inside(x, y) && hit)
    {
        setValue(!(*value));
#ifdef CI_UI_TARGET_TOUCH
        state = CI_UI_STATE_NORMAL;
#else
        state = CI_UI_STATE_OVER;
#endif
        triggerEvent(this);
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

void ciUIDropDownList::setAutoClose(bool _autoClose)
{
    autoClose = _autoClose;
}

void ciUIDropDownList::open()
{
    setValue(true);
}

void ciUIDropDownList::close()
{
    setValue(false);
}


void ciUIDropDownList::setVisible(bool _visible)
{
    visible = _visible;
    label->setVisible((visible && drawLabel));
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUILabelToggle * toggle = (ciUILabelToggle *) toggles[i];
        toggle->setVisible((visible && isOpen()));
    }
}

void ciUIDropDownList::setToggleVisibility(bool _value)
{
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUILabelToggle * toggle = (ciUILabelToggle *) toggles[i];
        toggle->setVisible(_value);
    }
}

vector<ciUILabelToggle *> &ciUIDropDownList::getToggles()
{
    return toggles;
}

void ciUIDropDownList::triggerSelf()
{
    if(parent != NULL)
    {
        parent->triggerEvent(singleSelected);
    }
}

void ciUIDropDownList::triggerEvent(ciUIWidget *child)
{
    if(child == this)
    {
        parent->triggerEvent(child);
        return;
    }
    
    if(autoClose)
    {
        if(isOpen())
        {
            close();
        }
    }
    
    if(!allowMultiple)
    {
        activateToggle(child->getName().c_str());
    }
    
    selected.clear();
    selectedIndeces.clear();
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUILabelToggle *t = toggles[i];
        if(t->getValue())
        {
            selected.push_back(t);
            selectedIndeces.push_back(i);
        }
    }
    
    checkAndSetTitleLabel();
    
    if(parent != NULL)
    {
        parent->triggerEvent(this);
        parent->triggerEvent(child);
    }
}

void ciUIDropDownList::activateToggle(string _name)
{
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ciUILabelToggle *t = toggles[i];
        if(t->getName() == _name)
        {
            t->setValue(true);
            singleSelected = t;
        }
        else
        {
            t->setValue(false);
        }
    }
}

void ciUIDropDownList::setAllowMultiple(bool _allowMultiple)
{
    allowMultiple = _allowMultiple;
}

void ciUIDropDownList::setValue(bool _value)
{
    *value = _value;
    draw_fill = *value;
    setModal(*value);
    setToggleVisibility(*value);
    label->setDrawBack((*value));
}

void ciUIDropDownList::setModal(bool _modal)      //allows for piping mouse/touch input to widgets that are outside of parent's rect/canvas
{
    modal = _modal;
    if(parent != NULL)
    {
        if(modal)
        {
            parent->addModalWidget(this);
        }
        else
        {
            parent->removeModalWidget(this);
        }
    }
    
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        toggles[i]->setModal(modal);
    }
}

bool ciUIDropDownList::isOpen()
{
    return *value;
}

void ciUIDropDownList::setSingleSelected(int index){
    
    vector<ciUILabelToggle*> toggles = getToggles();
    if(index < toggles.size()){
        selected.clear();
        ciUILabelToggle *lt = toggles.at(index);
        selected.push_back(lt);
        setShowCurrentSelected(true);
    }else{
        ofLogWarning("index for ufxUIDropDownList::setSingleSelected is out of range");
    }
    
}

#ifndef CI_UI_NO_XML

void ciUIDropDownList::saveState(ofxXmlSettings *XML)
{
    XML->setValue("Open", (isOpen() ? 1 : 0), 0);
    int index = XML->addTag("Selected");
    if(XML->pushTag("Selected", index)) {
        int cnt = 0;
        for(vector<ciUIWidget *>::iterator it = selected.begin(); it != selected.end(); ++it) {
            ciUILabelToggle *lt = (ciUILabelToggle *) (*it);
            XML->setValue("Name", lt->getName(), cnt++);
        }
    }
    XML->popTag();
}

void ciUIDropDownList::loadState(ofxXmlSettings *XML)
{
    selected.clear();
    selectedIndeces.clear();
    singleSelected = nullptr;
    
    int value = XML->getValue("Open", (isOpen() ? 1 : 0), 0);
    if(value) { open(); } else { close(); }
    XML->pushTag("Selected", 0);
    int widgetTags = XML->getNumTags("Name");
    for(int i = 0; i < widgetTags; ++i) {
        string selName = XML->getValue("Name", "NULL", i);
        if(selName != "NULL"){
            if(allowMultiple) {
                for(unsigned int i = 0; i < toggles.size(); i++) {
                    ciUILabelToggle *t = toggles[i];
                    if(t->getName() == selName) {
                        t->setValue(true);
                        selected.push_back(t);
                        selectedIndeces.push_back(i);
                    }
                }
            } else {
                activateToggle(selName);
            }
        }
    }
    XML->popTag();
}

#endif
