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
#include "ciUIDefines.h"

class ciUISuperCanvas : public ciUICanvas
{
public:
    ciUISuperCanvas(const ciUISuperCanvas &other);
    ciUISuperCanvas(const std::string &_label, const ciUIRectangle &r, int _size = CI_UI_FONT_MEDIUM);
    ciUISuperCanvas(const std::string &_label, float x, float y, float w, float h, int _size = CI_UI_FONT_MEDIUM);
    ciUISuperCanvas(const std::string &_label, float x, float y, float w, float h, ciUICanvas *sharedResources, int _size = CI_UI_FONT_MEDIUM);
    ciUISuperCanvas(const std::string &_label, int _size = CI_UI_FONT_MEDIUM);
    ciUISuperCanvas(const std::string &_label, ciUICanvas *sharedResources, int _size = CI_UI_FONT_MEDIUM);
    void superInit(const std::string &_label, int _size);
    void setDeltaTime(float _deltaTime);
    void setMinified(bool _bIsMinified);
    bool isMinified();
    void toggleMinified();
    ciUILabel *getCanvasTitle();
    bool didHitHeaderWidgets(float x, float y); 
    void autoSizeToFitWidgets() override;

    virtual void keyPressed(int key) override;
    virtual void keyReleased(int key) override;

#ifdef CI_UI_TARGET_TOUCH
    virtual void touchDown(float x, float y, int id) override;
    virtual void touchMoved(float x, float y, int id) override;
    virtual void touchUp(float x, float y, int id) override;
    virtual void touchDoubleTap(float x, float y, int id) override;
    virtual void touchCancelled(float x, float y, int id) override;
#else
    virtual void onMouseReleased(ci::app::MouseEvent& data);
    virtual void onMousePressed(ci::app::MouseEvent& data);
    virtual void onMouseDragged(ci::app::MouseEvent& data);
    virtual void onMouseMoved(ci::app::MouseEvent& data);
#endif
    
    virtual void saveSettings(const std::string &fileName);
    virtual void loadSettings(const std::string &fileName);
    void addWidgetToHeader(ciUIWidget *widget);
    void removeWidgets() override;
    
protected:
    void minify();
    void maximize();
    
    int size; 
    std::string title;
    ciUILabel *canvasTitle;
    std::vector<ciUIWidget *> headerWidgets;
    
    ciUIVec2f hitPoint;
    ciUIVec2f lastPosition;
    ci::ivec2 mousePosition;
    float deltaTime;
    float lastHitTime;
    bool bIsMinified;
    bool bTitleLabelHit;
};
