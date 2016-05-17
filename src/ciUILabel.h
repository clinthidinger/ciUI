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

#include <string>
#include "ciUIWidget.h"

class ciUILabel : public ciUIWidget
{
public:
    ciUILabel();
    ciUILabel(float x, float y, const std::string &_name, const std::string &_label, int _size);
    ciUILabel(float x, float y, const std::string &_name, int _size);
    ciUILabel(const std::string &_name, const std::string &_label, int _size);
    ciUILabel(const std::string &_name, int _size);
    ciUILabel(float x, float y, float w, const std::string &_name, const std::string &_label, int _size);
    ciUILabel(float x, float y, float w, const std::string &_name, int _size);
    ciUILabel(float w, const std::string &_name, const std::string &_label, int _size);
    ciUILabel(float w, const std::string &_name, int _size);
    ciUILabel(float w, const std::string &_name, int _size, float h);
    
    void init(float x, float y, float w, float h, const std::string &_name, const std::string &_label, int _size);
    
    void drawBack();
    void drawFill();
    
    void drawFillHighlight();
    void drawBackLabel();
	
    void drawString(float x, float y, const std::string &_string);
    void drawStringShadow(float x, float y, const std::string &_string);
	
    float getStringWidth(const std::string &s) const;
	float getStringHeight(const std::string &s) const;

    float getLineHeight() const;
    virtual ciUILabel* getLabelWidget();

    void setLabel(const std::string &_label);
    const std::string &getLabel() const;
    
    bool getAutoSize() const;
    void setAutoSize(bool _autoSize);
	
    void setFont(ci::gl::TextureFontRef _font);
	int getSize() const;
	
    void focus();
	void unfocus();
    
    void setVisible(bool _visible);
    bool isVisible() const;
    void toggleVisible();
    
protected:    
	int size;
    std::string label;
    bool autoSize;
    int xOffset, yOffset; 
}; 
