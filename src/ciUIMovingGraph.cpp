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

#include "ciUIMovingGraph.h"
#include "ciUI.h"

ciUIMovingGraph::ciUIMovingGraph(float x, float y, float w, float h, vector<float> _buffer, int _bufferSize, float _min, float _max, string _name) : ciUIWidget()
{
    init(x, y, w, h, _buffer, _bufferSize, _min, _max, _name);
}

ciUIMovingGraph::ciUIMovingGraph(float w, float h, vector<float> _buffer, int _bufferSize, float _min, float _max, string _name) : ciUIWidget()
{
    init(0, 0, w, h, _buffer, _bufferSize, _min, _max, _name);
}

void ciUIMovingGraph::init(float x, float y, float w, float h, vector<float> _buffer, int _bufferSize, float _min, float _max, string _name)
{
    initRect(x,y,w,h);
    name = string(_name);
    kind = CI_UI_WIDGET_MOVINGGRAPH;
    
    draw_fill = true;
    
    buffer = _buffer;					//the widget's value
    
    bufferSize = _bufferSize;
    max = _max;
    min = _min;
    scale = rect->getHeight()*.5;
    inc = rect->getWidth()/((float)bufferSize-1.0);
}

void ciUIMovingGraph::drawFill()
{
    if(draw_fill)
    {
        ofNoFill();
        if(draw_fill_highlight)
        {
            ciUISetColor(color_fill_highlight);
        }
        else
        {
            ciUISetColor(color_fill);
        }
        ofPushMatrix();
        ofTranslate(rect->getX(), rect->getY()+scale, 0);
        ofSetLineWidth(2.0);
        ofBeginShape();
        for (unsigned int i = 0; i < bufferSize; i++)
        {
            ofVertex(inc*(float)i, ciUIMap(buffer[i], min, max, scale, -scale, true));
        }
        ofEndShape();
        ofSetLineWidth(1);
        ofPopMatrix();
    }
}

void ciUIMovingGraph::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    calculatePaddingRect();
}

void ciUIMovingGraph::addPoint(float _point)
{
    buffer.push_back(_point);
    
    if( buffer.size() >= bufferSize )
    {
        buffer.erase(buffer.begin(), buffer.begin()+1);
    }
}

vector<float> &ciUIMovingGraph::getBuffer()
{
    return buffer;
}

void ciUIMovingGraph::setBuffer(vector<float> _buffer)
{
    buffer = _buffer;
}

void ciUIMovingGraph::setMax(float _max)
{
    max = _max;
}

float ciUIMovingGraph::getMax()
{
    return max;
}

void ciUIMovingGraph::setMin(float _min)
{
    min = _min;
}

float ciUIMovingGraph::getMin()
{
    return min;
}

ofVec2f ciUIMovingGraph::getMaxAndMind()
{
    return ofVec2f(max, min);
}

void ciUIMovingGraph::setMaxAndMin(float _max, float _min)
{
    max = _max;
    min = _min;
}
