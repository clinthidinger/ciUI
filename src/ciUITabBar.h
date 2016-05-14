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

#include "ciUICanvas.h"
#include "ciUIScrollableCanvas.h"
#include "ciUIToggle.h"

class ciUITabBar : public ciUICanvas
{
public:
    ciUITabBar();
    virtual ~ciUITabBar();
    ciUITabBar(float x, float y, float w, float h);
    void initTabBar();
    void addCanvas(ciUICanvas *_canvas);
    void addCanvas(ciUIScrollableCanvas *_canvas);
    void mainUiEvent(ciUIEventArgs &event);
    void enable();
    void disable();
    void toggleVisible();
    ciUICanvas* getActiveCanvas();
    bool isHit(int x, int y);
    void saveSettings(const std::string &pathToSaveTo, const std::string &fileNamePrefix);
    void loadSettings(const std::string &pathToLoadFrom, const std::string &fileNamePrefix);
    
protected:
    std::map<ciUIToggle*, ciUICanvas*> canvases;
    ciUICanvas *active;
};
