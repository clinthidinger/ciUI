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
#include "ciUIImage.h"

class ciUIImageSampler : public ciUIImage
{
public:
    ciUIImageSampler(float x, float y, float w, float h, ci::SurfaceRef _image, const std::string &_name);
    ciUIImageSampler(float w, float h, ci::SurfaceRef _image, const std::string &_name);
    void initSampler();
    void setSquareSize(float _squareSize);
    void drawFill();
    void drawFillHighlight();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void stateChange();
    void input(int x, int y);
    const ci::Color &getColor() const;
    void setColor(const ci::Color &_sampledColor);
    const ci::vec2 &getValue() const;
    void setValue(const ci::vec2 &_value);
    bool isDraggable();
    bool hasState(){ return true; };
//#ifndef CI_UI_NO_XML
//    virtual void saveState(ofxXmlSettings *XML);
//    virtual void loadState(ofxXmlSettings *XML);
//#endif    
    
protected: 
    ci::Color sampledColor;
    ci::vec2 value;
    float squareSize; 
}; 
