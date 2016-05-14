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

#include "ciUIFPS.h"
#include "ciUI.h"

ciUIFPS::ciUIFPS(float x, float y, int _size) : ciUIWidgetWithLabel()
{
    init(x, y, "FPS", "FPS: 0000", _size);
}

ciUIFPS::ciUIFPS(int _size) : ciUIWidgetWithLabel()
{
    init(0, 0, "FPS", "FPS: 0000", _size);
}

void ciUIFPS::init(float x, float y, const std::string &_name, const std::string &_label, int _size)
{
    initRect(x, y, 0, 0);
    name = _name;
    kind = CI_UI_WIDGET_FPS;
    
    label = new ciUILabel(0,0,(name+" LABEL"), _label, _size);
    addEmbeddedWidget(label); 
    
    labelPrecision = 0;
    draw_back = CI_UI_LABEL_DRAW_BACK;
    draw_fill = false;
    draw_back = false;
}

void ciUIFPS::update()
{
    label->setLabel(name + ": " + ciUIToString(ci::app::getFrameRate(), labelPrecision));
}

void ciUIFPS::setLabelPrecision(int _precision) {
    labelPrecision = _precision;
}

void ciUIFPS::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    rect->setHeight(label->getRect()->getHeight());
    rect->setWidth(label->getRect()->getWidth());    
    calculatePaddingRect();
}
