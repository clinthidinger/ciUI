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

#include "ciUIWidgetWithLabel.h"
#include "ciUIToggle.h"
#include "ciUIDefines.h"

class ciUIToggleMatrix : public ciUIWidget
{
public:
    ciUIToggleMatrix(float x, float y, float w, float h, int _rows, int _cols, const std::string &_name, int _size = CI_UI_FONT_SMALL);
    ciUIToggleMatrix(float w, float h, int _rows, int _cols, const std::string &_name, int _size = CI_UI_FONT_SMALL);
    void init(float x, float y, float w, float h, int _rows, int _cols, const std::string &_name, int _size = CI_UI_FONT_SMALL);
    void setVisible(bool _visible) override;
	void activateToggle(const std::string &_name);
	void setParent(ciUIWidget *_parent) override;
    
    void setAllToggles(bool _value, bool _trigger = true);
    void setToggle(unsigned int row, unsigned int col, bool _value, bool _trigger = true);
    ciUIToggle * getToggle(unsigned int row, unsigned int col);
    bool getState(int row, int col);
    
    int getColumnCount() const;
    int getRowCount() const;
    
    const std::vector<ciUIToggle *> &getToggles() const;
    const std::vector<ciUIToggle *> *getTogglesPtr() const;
	void triggerEvent(ciUIWidget *child) override;
    void setAllowMultiple(bool _allowMultiple);
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void keyPressed(int key) override;
    void keyReleased(int key) override;
protected:
    std::vector<ciUIToggle *> toggles;
    int rows, cols;
    float toggleWidth, toggleHeight; 
    bool allowMultiple;
    bool isKeyPressed;
};
