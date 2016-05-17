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
#include "cinder/CinderMath.h"

ciUI2DGraph::ciUI2DGraph(const std::string &_name, const ci::vec2 &_rangeX, const ci::vec2 &_rangeY, int _bufferSize, float * _xValues, float * _yValues, float w, float h, float x, float y) : ciUIWidget()
{
    init(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, w, h, x, y);
}

void ciUI2DGraph::init(const std::string &_name, const ci::vec2 &_rangeX, const ci::vec2 &_rangeY, float _bufferSize, float * _xValues, float * _yValues, float w, float h, float x, float y)
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
    
    inc = std::max(rect->getHalfHeight(), rect->getHalfWidth())/6.0;
}

void ciUI2DGraph::drawBack()
{
    if(draw_back)
    {
        //ofFill();
        ci::gl::ScopedColor scopedColor(color_back);
        rect->draw(true);
    
        ci::gl::ScopedMatrices scopedMatrices;
        ci::gl::translate(rect->getX(), rect->getY(), 0);
        
        for(int x = 0; x <= rect->getWidth(); x+=inc)
        {
            ciUIDrawLine(x, 0, x, rect->getHeight());   //y
        }
        
        for(int y = 0; y <= rect->getHeight(); y+=inc)
        {
            ciUIDrawLine(0, y, rect->getWidth(), y);   //x
        }
        
        ci::gl::ScopedLineWidth scopedLineWidth(2.0f);
        ciUIDrawLine(rect->getHalfWidth(), 0, rect->getHalfWidth(), rect->getHeight());
        ciUIDrawLine(0, rect->getHalfHeight(), rect->getWidth(), rect->getHalfHeight());
        //ofPopMatrix();
        //ofNoFill();
        rect->draw(false);
        
        //ciUISetLineWidth(1);
        //ofFill();
    }
}


void ciUI2DGraph::drawFill()
{
    if(draw_fill)
    {
        ci::gl::ScopedColor scopedColor(draw_fill_highlight ? color_fill_highlight : color_fill);
        if(xValues != nullptr && yValues != nullptr)
        {
            ci::gl::ScopedMatrices scopedMatrices;
            ci::gl::translate(rect->getX(), rect->getY(), 0);
            ci::gl::ScopedLineWidth scopedLineWidth(1.5);
            polyLine.getPoints().clear();
            polyLine.getPoints().reserve(bufferSize);
            
            for(int i =0; i < bufferSize; i++)
            {
                float x = ci::math<float>::clamp(ci::lmap<float>(xValues[i], rangeX.x, rangeX.y, 0.0f, rect->getWidth()), 0.0f, rect->getWidth());
                float y = ci::math<float>::clamp(ci::lmap<float>(yValues[i], rangeY.x, rangeY.y, 0.0f, rect->getHeight()),0.0f, rect->getHeight());
                polyLine.push_back(ci::vec2(x, y));
            }
            ci::gl::draw(polyLine);
        }
    }
}
