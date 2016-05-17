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

#include "ciUISlider.h"
#include "ciUI.h"

template<typename T>
ciUISlider_<T>::ciUISlider_() : ciUIWidgetWithLabel()
{
    
}

template<typename T>
ciUISlider_<T>::ciUISlider_(const std::string &_name, T _min, T _max, T _value, float w, float h, float x, float y) : ciUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_value, w, h, x, y);
}

template<typename T>
ciUISlider_<T>::ciUISlider_(const std::string &_name, T _min, T _max, T *_value, float w, float h, float x, float y) : ciUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _value, w, h, x, y);
}

template<typename T>
ciUISlider_<T>::~ciUISlider_()
{
    if(!useReference)
    {
        delete valueRef;
    }
}

template<typename T>
void ciUISlider_<T>::init(const std::string &_name, T _min, T _max, T *_value, float w, float h, float x, float y)
{
    initRect(x,y,w,h);
    name = _name;
    setOrientation(w, h);
    setKind();
    
    draw_fill = true;
    
    value = *_value;                                               //the widget's value
    if(useReference)
    {
        valueRef = _value;
    }
    else
    {
        valueRef = new T();
        *valueRef = value;
    }
    
    max = _max;
    min = _min;
    labelPrecision = 2;
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    value = ciUIMap<float>(value, min, max, 0.0f, 1.0f, true);
    valueString = ciUIToString(getScaledValue(),labelPrecision);
    
    if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
    {
        label = new ciUILabel(0,h+padding, std::string(name+" LABEL"), std::string(name + ": " + ciUIToString(max,labelPrecision)), CI_UI_FONT_SMALL);
    }
    else
    {
        label = new ciUILabel(0,h+padding, std::string(name+" LABEL"), std::string(name), CI_UI_FONT_SMALL);
    }
    addEmbeddedWidget(label);
    label->setVisible(drawLabel);

    increment = glm::abs(max - min) / 10.0;
    bRoundedToNearestInt = false;
    bClampValue = true;
    bSticky = false;
    stickyValue = glm::abs(max - min) / 100.0;
}

template<typename T>
void ciUISlider_<T>::setOrientation(float w, float h)
{
    if(w > h)
    {
        orientation = CI_UI_ORIENTATION_HORIZONTAL;
    }
    else
    {
        orientation = CI_UI_ORIENTATION_VERTICAL;
    }
}

template<>
void ciUISlider_<float>::setKind()
{
    if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
    {
        kind = CI_UI_WIDGET_SLIDER_H;
    }
    else
    {
        kind = CI_UI_WIDGET_SLIDER_V;
    }
}

template<>
void ciUISlider_<int>::setKind()
{
    if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
    {
        kind = CI_UI_WIDGET_INTSLIDER_H;
    }
    else
    {
        kind = CI_UI_WIDGET_INTSLIDER_V;
    }
}


template<>
void ciUISlider_<double>::setKind()
{
    if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
    {
        kind = CI_UI_WIDGET_DOUBLESLIDER_H;
    }
    else
    {
        kind = CI_UI_WIDGET_DOUBLESLIDER_V;
    }
}

template<typename T>
bool ciUISlider_<T>::getSetClampValue()
{
    return bClampValue;
}

template<typename T>
void ciUISlider_<T>::setClampValue(bool _bClampValue)
{
    bClampValue = _bClampValue;
}

template<typename T>
ciUISlider_<T>* ciUISlider_<T>::enableSticky(bool _bSticky)
{
    bSticky = _bSticky;
    return this;
}

template<typename T>
ciUISlider_<T>* ciUISlider_<T>::setStickyValue(double _stickyValue)
{
    stickyValue = _stickyValue;
    return this;
}

template<typename T>
double ciUISlider_<T>::getStickyValue() const
{
    return stickyValue;
}

template<typename T>
void ciUISlider_<T>::update()
{
    if(useReference)
    {
        value = ciUIMap<float>(*valueRef, min, max, 0.0f, 1.0f, bClampValue);
        updateLabel();
    }
}

template<typename T>
void ciUISlider_<T>::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

template<typename T>
void ciUISlider_<T>::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

template<typename T>
void ciUISlider_<T>::drawBack()
{
    if(draw_back)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_back);
        rect->draw(true);
    }
}

template<typename T>
void ciUISlider_<T>::drawOutline()
{
    if(draw_outline)
    {
        //ofNoFill();
        ci::gl::ScopedColor scopedColor(color_outline);
        rect->draw(false);
    }
}

template<typename T>
void ciUISlider_<T>::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        //ofNoFill();
        ci::gl::ScopedColor scopedColor(color_outline_highlight);
        rect->draw(false);
    }
}

template<typename T>
void ciUISlider_<T>::drawFill()
{
    if(draw_fill && value > 0.0)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill);
        if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
        {
            ciUIDrawCorneredRect(rect->getX(), rect->getY(), rect->getWidth()*std::min(std::max(value, 0.0), 1.0), rect->getHeight(), true);
        }
        else
        {
            ciUIDrawCorneredRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*std::min(std::max(value, 0.0), 1.0), true);
        }
    }
}

template<typename T>
void ciUISlider_<T>::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill_highlight);
        if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
        {
            ciUIDrawCorneredRect(rect->getX(), rect->getY(), rect->getWidth()*std::min(std::max(value, 0.0), 1.0), rect->getHeight(), true);
        }
        else
        {
            ciUIDrawCorneredRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*std::min(std::max(value, 0.0), 1.0), true);
        }
        if(kind == CI_UI_WIDGET_SLIDER_V)
        {
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*std::min(std::max(value, 0.0), 1.0), valueString);
        }
    }
}

template<typename T>
void ciUISlider_<T>::mouseMoved(int x, int y )
{
    if(rect->inside(x, y))
    {
        state = CI_UI_STATE_OVER;
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

template<typename T>
void ciUISlider_<T>::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = CI_UI_STATE_DOWN;
        input(x, y);
        if(triggerType & CI_UI_TRIGGER_CHANGE)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

template<typename T>
void ciUISlider_<T>::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = CI_UI_STATE_DOWN;
        input(x, y);
        if(triggerType & CI_UI_TRIGGER_BEGIN)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

template<typename T>
void ciUISlider_<T>::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef CI_UI_TARGET_TOUCH
        state = CI_UI_STATE_NORMAL;
#else
        state = CI_UI_STATE_OVER;
#endif
        input(x, y);
        if(triggerType & CI_UI_TRIGGER_END)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

template<typename T>
void ciUISlider_<T>::keyPressed(int key)
{
    if(state == CI_UI_STATE_OVER || state == CI_UI_STATE_DOWN)
    {
        switch (key)
        {
            case ci::app::KeyEvent::KEY_RIGHT:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case ci::app::KeyEvent::KEY_UP:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case ci::app::KeyEvent::KEY_LEFT:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            case ci::app::KeyEvent::KEY_DOWN:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            case ci::app::KeyEvent::KEY_LSHIFT:
            case ci::app::KeyEvent::KEY_RSHIFT:
                bRoundedToNearestInt = true;
                break;

            case ci::app::KeyEvent::KEY_LMETA: // Command
            case ci::app::KeyEvent::KEY_RMETA:
                bSticky = true;
                break;
                
            default:
                break;
        }
    }
}

template<typename T>
void ciUISlider_<T>::keyReleased(int key)
{
    bRoundedToNearestInt = false;
    bSticky = false;
}

template<typename T>
void ciUISlider_<T>::windowResized(int w, int h)
{
    
}

template<typename T>
T ciUISlider_<T>::getIncrement()
{
    return increment;
}

template<typename T>
ciUISlider_<T>* ciUISlider_<T>::setIncrement(T _increment)
{
    increment = _increment;
    return this; 
}

template<typename T>
void ciUISlider_<T>::input(float x, float y)
{
    if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
    {
        value = rect->percentInside(x, y).x;
    }
    else
    {
        value = 1.0-rect->percentInside(x, y).y;
    }
    
    value = std::min(1.0, std::max(0.0, value));
    updateValueRef();
    updateLabel();
}

template<typename T>
void ciUISlider_<T>::updateValueRef()
{
    (*valueRef) = bRoundedToNearestInt ? ceil(getScaledValue()) : getScaledValue();
}

template<typename T>
void ciUISlider_<T>::updateLabel()
{
    valueString = ciUIToString(getValue(),labelPrecision);
    if(orientation == CI_UI_ORIENTATION_HORIZONTAL)
    {
        label->setLabel(name + ": " + valueString);
    }
}

template<typename T>
void ciUISlider_<T>::stateChange()
{
    switch (state) {
        case CI_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case CI_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
            label->unfocus();
        }
            break;
        case CI_UI_STATE_DOWN:
        {
            draw_fill_highlight = true;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case CI_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
            
        default:
            break;
    }
}

template<typename T>
void ciUISlider_<T>::setValue(T _value)
{
    value = ciUIMap<float>(_value, min, max, 0.0f, 1.0f, bClampValue);
    updateValueRef();
    updateLabel();
}

template<typename T>
const T ciUISlider_<T>::getValue() const
{
    return (*valueRef);
}

template<typename T>
T ciUISlider_<T>::getNormalizedValue() const
{
    return value;
}

template<typename T>
float ciUISlider_<T>::getPercentValue() const
{
    return value;
}

template<typename T>
const T ciUISlider_<T>::getScaledValue() const
{
    T val = ciUIMap<float>(value, 0.0f, 1.0f, min, max, bClampValue);
    if(!bRoundedToNearestInt && bSticky)
    {
        val = ceil((double)val/(double)stickyValue)*(double)stickyValue;
    }
    return val; 
}

template<typename T>
void ciUISlider_<T>::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    label->getRect()->setY(rect->getHeight()+padding);
    calculatePaddingRect();
    updateValueRef();
    updateLabel();
}

template<typename T>
void ciUISlider_<T>::setLabelPrecision(int _precision)
{
    labelPrecision = _precision;
    updateValueRef();
    updateLabel();
}

template<typename T>
void ciUISlider_<T>::setMax(T _max, bool bKeepValueTheSame)
{
    setMaxAndMin(_max, min, bKeepValueTheSame);
}

template<typename T>
T ciUISlider_<T>::getMax()
{
    return max;
}

template<typename T>
void ciUISlider_<T>::setMin(T _min, bool bKeepValueTheSame)
{
    setMaxAndMin(max, _min, bKeepValueTheSame);
}

template<typename T>
T ciUISlider_<T>::getMin()
{
    return min;
}

template<typename T>
ciUIVec2f ciUISlider_<T>::getMaxAndMin() const
{
    return ciUIVec2f(max, min);
}

template<typename T>
void ciUISlider_<T>::setMaxAndMin(T _max, T _min, bool bKeepValueTheSame)
{
    max = _max;
    min = _min;
    
    if(!bKeepValueTheSame)
    {
        value = ciUIMap<float>(value, 0.0f, 1.0f, min, max, bClampValue);
        value = ciUIMap<float>(value, min, max, 0.0f, 1.0f, bClampValue);
        updateValueRef();
        updateLabel();
    }
}
template<typename T>
void ciUISlider_<T>::setValueReference(T *_value)
{
    if(!useReference)
    {
        useReference = false;
        delete valueRef;
    }
    valueRef = _value;
}

template<typename T>
bool ciUISlider_<T>::isDraggable()
{
    return true;
}

#ifndef CI_UI_NO_XML

template<typename T>
void ciUISlider_<T>::saveState(ofxXmlSettings *XML)
{
    XML->setValue("Value", getValue(), 0);
}

template<typename T>
void ciUISlider_<T>::loadState(ofxXmlSettings *XML)
{
    T value = XML->getValue("Value", getValue(), 0);
    setValue(value);
}

#endif

template class ciUISlider_<int>;
template class ciUISlider_<float>;
template class ciUISlider_<double>;
