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

class ciUI2DPad : public ciUIWidgetWithLabel
{
public:
    ciUI2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f _value, float w, float h, float x = 0, float y = 0);
    ciUI2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f *_value, float w, float h, float x = 0, float y = 0);
    virtual ~ciUI2DPad();
    void init(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f *_value, float w, float h, float x = 0, float y = 0);
    virtual void update();
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawFill();
    virtual void drawFillHighlight();
    float getIncrement();
    void setIncrement(float _increment);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
	void input(float x, float y);
    void updateValueRef();
	void updateLabel();
    void stateChange();
	void setValue(ciUIVec3f _value);
	ciUIVec3f getValue();
	ciUIVec3f getPercentValue();
	ciUIVec3f getScaledValue();
    bool isDraggable();
    void setLabelPrecision(int _precision);
    bool hasState(){ return true; };
//#ifndef CI_UI_NO_XML
//    virtual void saveState(ofxXmlSettings *XML);
//    virtual void loadState(ofxXmlSettings *XML);
//#endif

protected:
	ciUIVec3f value;
	ciUIVec3f *valueRef;     
    float increment;
    int labelPrecision;     
    bool useReference; 
    ciUIVec3f rangeX, rangeY;
}; 
