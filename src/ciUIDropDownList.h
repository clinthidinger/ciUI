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

#pragma once

#include "ciUIToggle.h"
#include "ciUILabelToggle.h"

class ciUIDropDownList : public ciUIToggle
{
public:    
    ciUIDropDownList(string _name, vector<string> items, float w = 0, float x = 0, float y = 0, int _size = CI_UI_FONT_MEDIUM);
    ciUIDropDownList(float x, float y, float w, string _name, vector<string> items, int _size);
    ciUIDropDownList(float w, string _name, vector<string> items, int _size);
    ciUIDropDownList(float x, float y, string _name, vector<string> items, int _size);
    void init(string _name, vector<string> items, float w = 0, float x = 0, float y = 0, int _size = CI_UI_FONT_MEDIUM);
    void clearToggles();
    void clearSelected();
    void addToggle(string toggleName);
    void addToggles(vector<string>& toggleNames);
    void removeToggle(string toggleName);
    bool* getShowCurrentSelectedPtr();
    bool getShowCurrentSelected();
    void setShowCurrentSelected(bool _bShowCurrentSelected);
    void checkAndSetTitleLabel();
    vector<ciUIWidget *> & getSelected();
    vector<int> & getSelectedIndeces();
    vector<string> getSelectedNames(); 
    void setLabelText(string labeltext);
    void setParent(ciUIWidget *_parent);
    void mouseReleased(int x, int y, int button);
    void setAutoClose(bool _autoClose);
    void open();
    void close();
    void setVisible(bool _visible);
    void setToggleVisibility(bool _value);
    vector<ciUILabelToggle *> &getToggles();
    void triggerSelf();
    void triggerEvent(ciUIWidget *child);
	void activateToggle(string _name);
    void setAllowMultiple(bool _allowMultiple);
    virtual void setValue(bool _value);
    virtual void setModal(bool _modal);      
    bool isOpen();
    bool hasState() { return true; }
    
#ifndef CI_UI_NO_XML
    virtual void saveState(ofxXmlSettings *XML);
    virtual void loadState(ofxXmlSettings *XML);
#endif
    
    //sets the selected toggle for a dropdown and displays it; does not allow multiple selected options
    void setSingleSelected(int index);
    
protected:
    bool autoSize; 
    bool autoClose;
    bool bShowCurrentSelected; 
    vector<ciUILabelToggle *> toggles;
    ciUILabelToggle *singleSelected;
    vector<ciUIWidget *> selected;
    vector<int> selectedIndeces;
    bool allowMultiple;
    int size;     
}; 
