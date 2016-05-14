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

#include "ciUIWidgetWithLabel.h"
#include "ciUILabel.h"

ciUIWidgetWithLabel::ciUIWidgetWithLabel() : ciUIWidget(), drawLabel(true)
{
    
}

ciUIWidgetWithLabel::~ciUIWidgetWithLabel()
{
    
}

bool ciUIWidgetWithLabel::hasLabel()
{
    return true;
}

void ciUIWidgetWithLabel::setVisible(bool _visible)
{
    visible = _visible;
    label->setVisible((drawLabel && visible));
}

void ciUIWidgetWithLabel::setParent(ciUIWidget *_parent)
{
    ciUIWidget::setParent(_parent);
    calculatePaddingRect(); 
}

ciUILabel* ciUIWidgetWithLabel::getLabelWidget()
{
    return label;
}

void ciUIWidgetWithLabel::setLabelVisible(bool _visible)
{
    drawLabel = _visible;
    label->setVisible((drawLabel && visible));
    calculatePaddingRect();
}

void ciUIWidgetWithLabel::toggleColors()
{
    ciUIColor fill = getColorFill();
    float af = fill.a;
    ciUIColor back = getColorBack();
    float ab = back.a;
    
    setColorFill(ciUIColor(back, af));
    setColorBack(ciUIColor(fill, ab));
}

void ciUIWidgetWithLabel::setModal(bool _modal)
{
    modal = _modal;
    ciUIWidget *labelWidget = (ciUIWidget *) label;
    labelWidget->setModal(modal);
    if(parent != nullptr)
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
}

bool ciUIWidgetWithLabel::hasState()
{
    return false; 
}
