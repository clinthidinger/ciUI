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
#include "ciUIWidgetWithLabel.h"

template<typename T>
class ciUISlider_ : public ciUIWidgetWithLabel
{
public:
    ciUISlider_();
    ciUISlider_(const std::string &_name, T _min, T _max, T _value, float w, float h, float x = 0, float y = 0);
    ciUISlider_(const std::string &_name, T _min, T _max, T *_value, float w, float h, float x = 0, float y = 0);
    virtual ~ciUISlider_();
    void setKind();
    void setOrientation(float w, float h);
    virtual void init(const std::string &_name, T _min, T _max, T *_value, float w, float h, float x, float y);
    
    virtual void update() override;
    
    virtual void setDrawPadding(bool _draw_padded_rect) override;
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline) override;
    virtual void drawBack() override;
    virtual void drawOutline() override;
    virtual void drawOutlineHighlight() override;
    virtual void drawFill() override;
    virtual void drawFillHighlight() override;
    
    void mouseMoved(int x, int y) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void windowResized(int w, int h) override;
    
    bool getSetClampValue();
    void setClampValue(bool _bClampValue);
    
    ciUISlider_<T>* enableSticky(bool _bSticky);
    ciUISlider_<T>* setStickyValue(double _stickyValue);
    double getStickyValue() const;
    
    T getIncrement();
    ciUISlider_<T>* setIncrement(T _increment);
	
    virtual void input(float x, float y);
    void updateValueRef();
	virtual void updateLabel();
    virtual void stateChange() override;
	
    void setValue(T _value);
	const T getValue() const;
    T getNormalizedValue() const;
	
    float getPercentValue() const;
	const T getScaledValue() const;

    void setLabelPrecision(int _precision);
    
	virtual void setParent(ciUIWidget *_parent) override;
    
    void setMax(T _max, bool bKeepValueTheSame = false);
    T getMax();
    
    void setMin(T _min, bool bKeepValueTheSame = false);
    T getMin();
    
    ciUIVec2f getMaxAndMin() const;
    void setMaxAndMin(T _max, T _min, bool bKeepValueTheSame = false);
    
    void setValueReference(T *_value); 
    
    bool isDraggable() override;
    virtual bool hasState() override { return true; };
//#ifndef CI_UI_NO_XML
//    virtual void saveState(ofxXmlSettings *XML);
//    virtual void loadState(ofxXmlSettings *XML);
//#endif
    
protected:
    bool bSticky;
    double stickyValue;
    bool bRoundedToNearestInt;
    bool bClampValue;
    double value, increment;
    T *valueRef;
    bool useReference;
	T max, min;
    int labelPrecision;
    int orientation;
    std::string valueString;
};

typedef ciUISlider_<int> ciUIIntSlider;
typedef ciUISlider_<float> ciUISlider;
typedef ciUISlider_<double> ciUIDoubleSlider;
