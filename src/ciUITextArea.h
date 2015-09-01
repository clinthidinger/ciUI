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
#include "ciUIDefines.h"

class ciUITextArea : public ciUIWidgetWithLabel
{
public:
    ciUITextArea(const std::string &_name, const std::string &_textstring, float w, float h = 0, float x = 0, float y = 0, int _size = CI_UI_FONT_MEDIUM);
    void init(const std::string &_name, const std::string &_textstring, float w, float h = 0, float x = 0, float y = 0, int _size = CI_UI_FONT_MEDIUM);
    virtual void drawBack();
    virtual void drawFill();
    const std::string &getTextString();
	void setTextString(string s);
    void formatTextString();
	void setParent(ciUIWidget *_parent);
    void setDrawShadow(bool _drawShadow);
    
protected:    
    std::string textstring;
    std::vector<std::string> textLines;
    bool autoSize;
    bool drawShadow; 
    int lineSpaceSize;
    int lineHeight; 
    int offsetY; 
};