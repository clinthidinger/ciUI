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
#include <vector>
#include <map>
#include "ciUIWrapper.h"
#include "ciUIDefines.h"

//#ifndef CI_UI_NO_XML
//    #include "ofxXmlSettings.h"
//#endif

class ciUIWidget           
{
public:
    ciUIWidget();
    virtual ~ciUIWidget();
    ciUIWidget(const ciUIWidget &other); // Mitchell Nordine 2/2/14
    virtual ciUIWidget& operator=(const ciUIWidget &other); // Mitchell Nordine 2/2/14
    
    virtual void initRect(float x = 0, float y = 0, float w = 0, float h = 0);
    virtual void initPaddingRect();
    virtual void calculatePaddingRect();
    
    virtual void setup(); 
    virtual void update();
    virtual void draw();
    
    virtual void drawBack();
    virtual void drawOutline();
    virtual void drawOutlineHighlight();
    virtual void drawFill();
    virtual void drawFillHighlight();
    virtual void drawPadded();
    virtual void drawPaddedOutline();
    
#ifdef CI_UI_TARGET_TOUCH
    void touchDown(float x, float y, int id);
    void touchMoved(float x, float y, int id);
    void touchUp(float x, float y, int id);
    void touchCancelled(float x, float y, int id);
    void touchDoubleTap(float x, float y, int id) {}
#endif

	virtual void mouseMoved(int x, int y ) {}
	virtual void mouseDragged(int x, int y, int button) {}
	virtual void mousePressed(int x, int y, int button) {}
	virtual void mouseReleased(int x, int y, int button) {}
    
	virtual void keyPressed(int key) {}
	virtual void keyReleased(int key) {}
	virtual void windowResized(int w, int h) {}           		
    
    ciUIWidget* setTriggerType(ciUITriggerType _triggerType);
    ciUITriggerType getTriggerType();
    
	virtual void setParent(ciUIWidget *_parent);
    virtual ciUIWidget *getParent();
    
    virtual void setName(const std::string &_name);
    virtual std::string& getName();
    
    virtual void setModal(bool _modal);
    virtual bool isModal();
	
    virtual void setVisible(bool _visible);
    virtual bool isVisible();
    virtual void toggleVisible();
	
    virtual void setEmbedded(bool _embedded);
    virtual bool isEmbedded();
    
    void setID(int _id);
    int getID();
    virtual void setKind(ciUIWidgetType _kind);
    virtual ciUIWidgetType getKind();
    
    virtual bool isDraggable();
    virtual bool hasLabel();

    virtual void triggerEvent(ciUIWidget *child);
    virtual void triggerSelf();
    virtual void stateChange();
    virtual bool isHit(float x, float y);
    
    virtual void addWidget(ciUIWidget *widget);
    virtual void removeWidget(ciUIWidget *widget);
    
    virtual void addEmbeddedWidget(ciUIWidget *widget);
    virtual void clearEmbeddedWidgets();
    virtual int getEmbeddedWidgetsSize();
    ciUIWidget *getEmbeddedWidget(int index);
    
    virtual void setState(int _state);
    virtual int getState();
    virtual void setFont(ci::UIFont *_font);

    virtual void setPadding(float _padding);
    virtual float getPadding();
    
	virtual ciUIRectangle* getRect();
    virtual ciUIRectangle *getPaddingRect();
    virtual void setRectParent(ciUIRectangle *_prect);
    
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual bool getDrawPadding();
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual bool getDrawPaddingOutline();
	
    virtual void setDrawBack(bool _draw_back);
	virtual bool getDrawBack();
	
    virtual void setDrawOutline(bool _draw_outline);
	virtual bool getDrawOutline();
	
    virtual void setDrawFill(bool _draw_fill);
	virtual bool getDrawFill();
    
    virtual void setDrawFillHighLight(bool _draw_fill_highlight);
	virtual bool getDrawFillHighLight();
    
    virtual void setDrawOutlineHighLight(bool _draw_outline_hightlight);
	virtual bool getDrawOutlineHighLight();
	
	virtual void setColorBack(ciUIColor _color_back);
    ciUIColor& getColorBack();
    
	virtual void setColorOutline(ciUIColor _color_outline);
    ciUIColor& getColorOutline();
    
	virtual void setColorOutlineHighlight(ciUIColor _color_outline_highlight);
	ciUIColor& getColorOutlineHighlight();
    
	virtual void setColorFill(ciUIColor _color_fill);
	ciUIColor& getColorFill();
    
	virtual void setColorFillHighlight(ciUIColor _color_fill_highlight);
	ciUIColor& getColorFillHighlight();
    
    virtual void setColorPadded(ciUIColor _color_padded_rect);
	ciUIColor& getColorPadded();
    
    virtual void setColorPaddedOutline(ciUIColor _color_padded_rect_outline);
    ciUIColor& getColorPaddedOutline();

    virtual void addModalWidget(ciUIWidget *widget);
    virtual void removeModalWidget(ciUIWidget *widget);

    ciUIWidget *getCanvasParent();
    
    virtual bool hasState();
    
    virtual bool getIsBindedToKey(int key); 
    virtual ciUIWidget* bindToKey(int key);
    virtual ciUIWidget* unbindToKey(int key);
    virtual ciUIWidget* unbindAllKeys(); 

//#ifndef CI_UI_NO_XML
    
//    virtual void saveState(ofxXmlSettings *XML);
//    virtual void loadState(ofxXmlSettings *XML);
    
//#endif
    
protected:
	ciUIWidget *parent;
	ciUIRectangle *rect;
	ciUIFont *font;
	
    std::string name;                    
	ciUIWidgetType kind; 
	bool visible;
    int ID;
    bool hit; 
    int state;
    ciUITriggerType triggerType; 
    bool embedded;
    bool modal;
    
	bool draw_back;    
	bool draw_outline;
	bool draw_outline_highlight; 
	bool draw_fill; 
	bool draw_fill_highlight; 

	ciUIColor color_back;
	ciUIColor color_outline; 
	ciUIColor color_outline_highlight;	
	ciUIColor color_fill; 
	ciUIColor color_fill_highlight; 

	float padding;                 
	ciUIRectangle *paddedRect; 	

	bool draw_padded_rect; 
	bool draw_padded_rect_outline;     
    ciUIColor color_padded_rect; 
	ciUIColor color_padded_rect_outline;
    
    std::vector<ciUIWidget *> embeddedWidgets;

    bool bKeyHit;
    std::map<int, bool> keyBindings;
#ifdef CI_UI_TARGET_TOUCH       
    int touchId;     
#endif
};
