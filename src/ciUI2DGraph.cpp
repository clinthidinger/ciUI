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

#include "ciUI2DGraph.h"
#include "ciUI.h"

ciUI2DGraph::ciUI2DGraph(const std::string &_name, const ci::vec2 &_rangeX, const ci::vec2 &_rangeY, int _bufferSize, float * _xValues, float * _yValues, float w, float h, float x, float y) : ciUIWidget()
{
    init(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, w, h, x, y);
}

void ciUI2DGraph::init(const std::string &_name, ofPoint _rangeX, const ci::vec2 &_rangeY, float _bufferSize, float * _xValues, float * _yValues, float w, float h, float x, float y)
{
    initRect(x, y, w, h);
    name = _name;
    kind = CI_UI_WIDGET_2DGRAPH;
    draw_fill = true;
    
    bufferSize = _bufferSize;
    rangeX = _rangeX;
    rangeY = _rangeY;
    
    xValues = _xValues;
    yValues = _yValues;
    
    inc = MAX(rect->getHalfHeight(), rect->getHalfWidth())/6.0;
}

void ciUI2DGraph::drawBack()
{
    if(draw_back)
    {
        ofFill();
        ofSetColor(color_back);
        rect->draw();
    
        ofPushMatrix();
        ofTranslate(rect->getX(), rect->getY(), 0);
        
        for(int x = 0; x <= rect->getWidth(); x+=inc)
        {
            ciUIDrawLine(x, 0, x, rect->getHeight());   //y
        }
        
        for(int y = 0; y <= rect->getHeight(); y+=inc)
        {
            ciUIDrawLine(0, y, rect->getWidth(), y);   //x
        }
        
        ofSetLineWidth(2);
        ciUIDrawLine(rect->getHalfWidth(), 0, rect->getHalfWidth(), rect->getHeight());
        ciUIDrawLine(0, rect->getHalfHeight(), rect->getWidth(), rect->getHalfHeight());
        ofPopMatrix();
        ofNoFill();
        rect->draw();
        
        ciUISetLineWidth(1);
        ofFill();
    }
}


void ciUI2DGraph::drawFill()
{
    if(draw_fill)
    {
        ofNoFill();
        if(draw_fill_highlight)
        {
            ci::color(color_fill_highlight);
        }
        else
        {
            ci::color(color_fill);
        }
        if(xValues != nullptr && yValues != nullptr)
        {
            ofPushMatrix();
            ofTranslate(rect->getX(), rect->getY(), 0);
            ofSetLineWidth(1.5);
            ofPolyline line;
            for(int i =0; i < bufferSize; i++)
            {
                line.addVertex(ofMap(xValues[i], rangeX.x, rangeX.y, 0.0, rect->getWidth(), true), ofMap(yValues[i], rangeY.x, rangeY.y, 0.0, rect->getHeight(), true));
            }
            line.draw();
            ofSetLineWidth(1);
            ofPopMatrix();
        }
    }
}
