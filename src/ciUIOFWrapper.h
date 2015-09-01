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

//#include "ofMain.h"
//#include "ofPoint.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/app/Event.h"
#include "cinder/Font.h"

#ifndef CI_UI_FONT_RENDERER
#define CI_UI_FONT_RENDERER ofTrueTypeFont
#endif

typedef ci::vec3 ciUIVec3f;
typedef ci::vec2 ciUIVec2f;
//typedef CI_UI_FONT_RENDERER ci::Font;//ciUIFont;
typedef ci::Color ciUIColor;

/*
#if defined( TARGET_OF_IPHONE ) || defined( TARGET_OF_IOS ) || defined( TARGET_ANDROID )
    #define CI_UI_TARGET_TOUCH
#endif

#define CI_UI_RECTMODE_CORNER OF_RECTMODE_CORNER
#define CI_UI_RECTMODE_CENTER OF_RECTMODE_CENTER

class ciUIAppCBGlue
{
public:        
    //ofBaseApp *app;
    
    void EnableCallbacks()
	{
        enableAppDrawCallback();
        enableAppUpdateCallback();
        enableAppExitCallback();
#ifdef CI_UI_TARGET_TOUCH
        enableTouchEventCallbacks();
#else
        enableMouseEventCallbacks();
        enableWindowEventCallbacks();
#endif
        enableKeyEventCallbacks();
	}
	
	void DisableCallbacks()
	{
        disableAppDrawCallback();
        disableAppUpdateCallback();
        disableAppExitCallback();
#ifdef CI_UI_TARGET_TOUCH
        disableTouchEventCallbacks();
#else
        disableMouseEventCallbacks();
        disableWindowEventCallbacks();
#endif
        disableKeyEventCallbacks();
    }
    
   	//App Callbacks
    void enableAppEventCallbacks()
    {
        enableAppUpdateCallback();
        enableAppDrawCallback();
        enableAppExitCallback();
    }
	
	//App Callbacks
    void disableAppEventCallbacks()
    {
        disableAppUpdateCallback();
        disableAppDrawCallback();
        disableAppExitCallback();
    }
	
    void enableAppDrawCallback()
    {
        ofAddListener(ofEvents().draw, this, &ciUIAppCBGlue::onDraw);
    }
    
    void enableAppUpdateCallback()
    {
        ofAddListener(ofEvents().update, this, &ciUIAppCBGlue::onUpdate, OF_EVENT_ORDER_BEFORE_APP);
    }
    
    void enableAppExitCallback()
    {
        ofAddListener(ofEvents().exit, this, &ciUIAppCBGlue::onExit, OF_EVENT_ORDER_BEFORE_APP);
    }
    
    void disableAppDrawCallback()
    {
        ofRemoveListener(ofEvents().draw, this, &ciUIAppCBGlue::onDraw);
    }
    
    void disableAppUpdateCallback()
    {
        ofRemoveListener(ofEvents().update, this, &ciUIAppCBGlue::onUpdate, OF_EVENT_ORDER_BEFORE_APP);
    }
    
    void disableAppExitCallback()
    {
        ofRemoveListener(ofEvents().exit, this, &ciUIAppCBGlue::onExit, OF_EVENT_ORDER_BEFORE_APP);
    }
    
#ifdef CI_UI_TARGET_TOUCH
	
	//Touch Callbacks
    void enableTouchEventCallbacks()
    {
        
        ofAddListener(ofEvents().touchUp, this, &ciUIAppCBGlue::onTouchUp, OF_EVENT_ORDER_BEFORE_APP);
        ofAddListener(ofEvents().touchDown, this, &ciUIAppCBGlue::onTouchDown, OF_EVENT_ORDER_BEFORE_APP);
        ofAddListener(ofEvents().touchMoved, this, &ciUIAppCBGlue::onTouchMoved, OF_EVENT_ORDER_BEFORE_APP);
        ofAddListener(ofEvents().touchCancelled, this, &ciUIAppCBGlue::onTouchCancelled, OF_EVENT_ORDER_BEFORE_APP);
        ofAddListener(ofEvents().touchDoubleTap, this, &ciUIAppCBGlue::onTouchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    }
    
	void disableTouchEventCallbacks()
    {
        ofRemoveListener(ofEvents().touchUp, this, &ciUIAppCBGlue::onTouchUp, OF_EVENT_ORDER_BEFORE_APP);
        ofRemoveListener(ofEvents().touchDown, this, &ciUIAppCBGlue::onTouchDown, OF_EVENT_ORDER_BEFORE_APP);
        ofRemoveListener(ofEvents().touchMoved, this, &ciUIAppCBGlue::onTouchMoved, OF_EVENT_ORDER_BEFORE_APP);
        ofRemoveListener(ofEvents().touchCancelled, this, &ciUIAppCBGlue::onTouchCancelled, OF_EVENT_ORDER_BEFORE_APP);
        ofRemoveListener(ofEvents().touchDoubleTap, this, &ciUIAppCBGlue::onTouchDoubleTap, OF_EVENT_ORDER_BEFORE_APP);
    }
	
#else
	
	//Mouse Callbacks
    void enableMouseEventCallbacks()
    {
        ofAddListener(ofEvents().mouseReleased, this, &ciUIAppCBGlue::onMouseReleased, OF_EVENT_ORDER_BEFORE_APP);
        ofAddListener(ofEvents().mousePressed, this, &ciUIAppCBGlue::onMousePressed, OF_EVENT_ORDER_BEFORE_APP);
        ofAddListener(ofEvents().mouseMoved, this, &ciUIAppCBGlue::onMouseMoved, OF_EVENT_ORDER_BEFORE_APP);
        ofAddListener(ofEvents().mouseDragged, this, &ciUIAppCBGlue::onMouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    }
    
	//Mouse Callbacks
    void disableMouseEventCallbacks()
    {
        ofRemoveListener(ofEvents().mouseReleased, this, &ciUIAppCBGlue::onMouseReleased, OF_EVENT_ORDER_BEFORE_APP);
        ofRemoveListener(ofEvents().mousePressed, this, &ciUIAppCBGlue::onMousePressed, OF_EVENT_ORDER_BEFORE_APP);
        ofRemoveListener(ofEvents().mouseMoved, this, &ciUIAppCBGlue::onMouseMoved, OF_EVENT_ORDER_BEFORE_APP);
        ofRemoveListener(ofEvents().mouseDragged, this, &ciUIAppCBGlue::onMouseDragged, OF_EVENT_ORDER_BEFORE_APP);
    }
    
    //Window Resize Callback
    void enableWindowEventCallbacks()
    {
        ofAddListener(ofEvents().windowResized, this, &ciUIAppCBGlue::onWindowResized, OF_EVENT_ORDER_BEFORE_APP);
    }
    
	//Window Resize Callback
    void disableWindowEventCallbacks()
    {
        ofRemoveListener(ofEvents().windowResized, this, &ciUIAppCBGlue::onWindowResized, OF_EVENT_ORDER_BEFORE_APP);
    }
	
#endif
    
    //KeyBoard Callbacks
	void enableKeyEventCallbacks()
	{
		ofAddListener(ofEvents().keyPressed, this, &ciUIAppCBGlue::onKeyPressed, OF_EVENT_ORDER_BEFORE_APP);
		ofAddListener(ofEvents().keyReleased, this, &ciUIAppCBGlue::onKeyReleased, OF_EVENT_ORDER_BEFORE_APP);
	}
    
	//KeyBoard Callbacks
	void disableKeyEventCallbacks()
	{
		ofRemoveListener(ofEvents().keyPressed, this, &ciUIAppCBGlue::onKeyPressed, OF_EVENT_ORDER_BEFORE_APP);
		ofRemoveListener(ofEvents().keyReleased, this, &ciUIAppCBGlue::onKeyReleased, OF_EVENT_ORDER_BEFORE_APP);
	}
    
    void onUpdate(ofEventArgs &data)
    {
        update();
    }
        
    void onDraw(ofEventArgs &data)
    {
        draw();
    }
        
    void onExit(ofEventArgs &data)
    {
        exit();
    }
    
    void onKeyPressed(ofKeyEventArgs& data)
    {
		keyPressed(data.key);
    }
    
    void onKeyReleased(ofKeyEventArgs& data)
    {
		keyReleased(data.key);
    }
    
    virtual void onMousePressed(ofMouseEventArgs& data)
    {
        mousePressed(data.x, data.y, data.button);
    }

    virtual void onMouseDragged(ofMouseEventArgs& data)
    {
        mouseDragged(data.x, data.y, data.button);
    }

    virtual void onMouseReleased(ofMouseEventArgs& data)
    {
        mouseReleased(data.x, data.y, data.button);
    }
        
    virtual void onMouseMoved(ofMouseEventArgs& data)
    {
        mouseMoved(data.x, data.y);
    }

    void onWindowResized(ofResizeEventArgs& data)
    {
		windowResized(data.width, data.height);
    }
    
    virtual void update()
    {
        
    }
    
    virtual void draw()
    {
        
    }
    
    virtual void exit()
    {
        
    }
    
    virtual void keyPressed(int key)
    {
        
    }
    
    virtual void keyReleased(int key)
    {
        
    }
    
    virtual void mousePressed(int x, int y, int button)
    {
        
    }

    virtual void mouseDragged(int x, int y, int button)
    {
        
    }

    virtual void mouseReleased(int x, int y, int button)
    {
        
    }
    
    virtual void mouseMoved(int x, int y)
    {
        
    }

    virtual void windowResized(int w, int h)
    {

    }
    
#ifdef CI_UI_TARGET_TOUCH
	
    virtual void onTouchDown(ofTouchEventArgs &data)
    {
		touchDown(data.x, data.y, data.id);
    }
    
    virtual void onTouchMoved(ofTouchEventArgs &data)
    {
		touchMoved(data.x, data.y, data.id);
    }

    virtual void onTouchUp(ofTouchEventArgs &data)
    {
		touchUp(data.x, data.y, data.id);
    }

    virtual void onTouchDoubleTap(ofTouchEventArgs &data)
    {
		touchDoubleTap(data.x, data.y, data.id);
    }
    
	virtual void onTouchCancelled(ofTouchEventArgs &data)
    {
		touchCancelled(data.x, data.y, data.id);
    }
    
    virtual void touchDown(float x, float y, int id)
    {
        
    }
    
    virtual void touchMoved(float x, float y, int id)
    {
        
    }
    
    virtual void touchUp(float x, float y, int id)
    {
        
    }
    
    virtual void touchDoubleTap(float x, float y, int id)
    {
        
    }

    virtual void touchCancelled(float x, float y, int id)
    {
        
    }

#endif
};

static void ciUISetColor(ciUIColor color, float alpha)
{
    ofSetColor(color, alpha);
}

static void ciUISetColor(ciUIColor color)
{
    ofSetColor(color);
}

static void ciUIFill()
{
    ofFill();
}

static void ciUINoFill()
{
    ofNoFill();
}

static void ciUIPushStyle()
{
    ofPushStyle();
#ifndef TARGET_OPENGLES
    glPushAttrib(GL_ALL_ATTRIB_BITS);
#endif
}

static void ciUIPopStyle()
{
#ifndef TARGET_OPENGLES    
    glPopAttrib();
#endif
    ofPopStyle();
}

static void ciUISetLineWidth(float lineWidth)
{
    ofSetLineWidth(lineWidth);
}

static float ciUIGetFrameRate()
{
    return ofGetFrameRate();
}

static void ciUISetRectMode(ofRectMode rectMode)
{
    ofSetRectMode(rectMode);
}

static void ciUICircle(float x, float y, float radius)
{
    ci::drawCircle(x, y, radius);
}

static void ciUIDrawRect(float x, float y, float w, float h)
{
    ci::drawRectangle(x,y,w,h);
}

static void ciUIDrawLine(float x1, float y1, float x2, float y2)
{
    ci::drawLine(x1, y1, x2, y2);
}

static int ciUIGetHeight()
{
    return ci::GetHeight();
}

static int ciUIGetWidth()
{
    return ci::GetWidth();
}
*/
