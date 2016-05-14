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

#include "ciUIBiLabelSlider.h"
#include "ciUI.h"

ciUIBiLabelSlider::ciUIBiLabelSlider(float x, float y, float w, float h, float _min, float _max, float _value, const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, int _size) : ciUISlider()
{
    useReference = false;
    init(x, y, w, h, _min, _max, &_value, _name, _leftLabel, _rightLabel, _size);
}

ciUIBiLabelSlider::ciUIBiLabelSlider(float w, float h, float _min, float _max, float _value, const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, int _size) : ciUISlider()
{
    useReference = false;
    init(0, 0, w, h, _min, _max, &_value, _name, _leftLabel, _rightLabel, _size);
}

ciUIBiLabelSlider::ciUIBiLabelSlider(float x, float y, float w, float _min, float _max, float _value, const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, int _size) : ciUISlider()
{
    useReference = false;
    init(x, y, w, 0, _min, _max, &_value, _name, _leftLabel, _rightLabel, _size);
}

ciUIBiLabelSlider::ciUIBiLabelSlider(float w, float _min, float _max, float _value, const std::string &_name, const std::const std::string &_leftLabel, const std::string &_rightLabel, int _size) : ciUISlider()
{
    useReference = false;
    init(0, 0, w, 0, _min, _max, &_value, _name, _leftLabel, _rightLabel, _size);
}

ciUIBiLabelSlider::ciUIBiLabelSlider(float x, float y, float w, float h, float _min, float _max, float *_value, const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, int _size) : ciUISlider()
{
    useReference = true;
    init(x, y, w, h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
}

ciUIBiLabelSlider::ciUIBiLabelSlider(float w, float h, float _min, float _max, float *_value, const std::string _name, const std::string _leftLabel, const std::string &_rightLabel, int _size) : ciUISlider()
{
    useReference = true;
    init(0, 0, w, h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
}

ciUIBiLabelSlider::ciUIBiLabelSlider(float x, float y, float w, float _min, float _max, float *_value, const std::string _name, const std::string &_leftLabel, const std::string &_rightLabel, int _size) : ciUISlider()
{
    useReference = true;
    init(x, y, w, 0, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
}

ciUIBiLabelSlider::ciUIBiLabelSlider(float w, float _min, float _max, float *_value, const std::string _name, const std::string _leftLabel, const std::string &_rightLabel, int _size) : ciUISlider()
{
    useReference = true;
    init(0, 0, w, 0, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
}

void ciUIBiLabelSlider::init(float x, float y, float w, float h, float _min, float _max, float *_value, const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, int _size)
{
    (h > 0) ? autoSize = false : autoSize = true;
    initRect(x,y,w,h);
    name = _name;
    leftLabel = _leftLabel;
    rightLabel = _rightLabel;
    kind = CI_UI_WIDGET_BILABELSLIDER;
    
    draw_fill = true;
    
    value = *_value;                                               //the widget's value
    if(useReference)
    {
        valueRef = _value;
    }
    else
    {
        valueRef = new float();
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
    
    value = ciUIMap(value, min, max, 0.0, 1.0, true);
    increment = fabs(max - min) / 10.0;
    
    label = new ciUILabel(padding,h*.5,(name+" LABEL"), name, _size);
    label->setDrawBack(true);
    addEmbeddedWidget(label);
    
    rlabel = new ciUILabel(padding,h*.5,(name+" LABEL"), rightLabel, _size);
    rlabel->setDrawBack(true);
    addEmbeddedWidget(rlabel);
    setTriggerType(CI_UI_TRIGGER_ALL);    
}

void ciUIBiLabelSlider::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
    rlabel->setDrawPadding(false);
}

void ciUIBiLabelSlider::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
    rlabel->setDrawPaddingOutline(false);
}

void ciUIBiLabelSlider::drawFill()
{
    if(draw_fill)
    {
        ciUIFill();
        ciUISetColor(color_fill);
        ciUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*value, rect->getHeight());
    }
}
void ciUIBiLabelSlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ciUIFill();
        ciUISetColor(color_fill_highlight);
        ciUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*value, rect->getHeight());
    }
}

void ciUIBiLabelSlider::input(float x, float y)
{    
    value = MIN(1.0, MAX(0.0, rect->percentInside(x, y).x));
    updateValueRef();
    updateLabel();
}

void ciUIBiLabelSlider::updateLabel()
{
    
}

void ciUIBiLabelSlider::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    label->setLabel(leftLabel);
    ciUIRectangle *labelrect = label->getRect();
    ciUIRectangle *rightlabelrect = rlabel->getRect();
    
    if(autoSize || rect->getHeight() < label->getPaddingRect()->getHeight())
    {
        rect->setHeight(label->getPaddingRect()->getHeight());
    }
    
    float h = labelrect->getHeight();
    float ph = rect->getHeight();
    
    labelrect->setY((int)(ph*.5 - h*.5));
    
    rightlabelrect->setY(labelrect->getY(false));
    rightlabelrect->setX(rect->getWidth()-rightlabelrect->getWidth()-padding*2.0);
    labelrect->setX(padding);
    
    calculatePaddingRect();
    updateValueRef();
    updateLabel();
}

ciUILabel * ciUIBiLabelSlider::getRightLabel()
{
    return rlabel;
}
