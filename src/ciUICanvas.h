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

#include "ciUIWidget.h"
#include "ciUIDefines.h"
#include "ciUIEventArgs.h"
#include "ciUIWidgets.h"
#include "ciUISlider.h"
#include <vector>
#include <map>
#include <string>

class ciUICanvas : public ciUIWidget//, public ciUIAppCBGlue
{
public:
    virtual ~ciUICanvas();
    //Default Constructor:
    ciUICanvas(float defaultWidthSize = CI_UI_GLOBAL_CANVAS_WIDTH, float defaultHeightSize = CI_UI_GLOBAL_CANVAS_WIDTH);
    ciUICanvas(const ciUICanvas &other);              // Mitchell Nordine 2/2/14
    ciUICanvas& operator=(const ciUICanvas &other);   // Mitchell Nordine 2/2/14
    
    ciUICanvas(ciUIRectangle r);
    ciUICanvas(float x, float y, float w, float h);
    ciUICanvas(float x, float y, float w, float h, ciUICanvas *sharedResources);
    ciUICanvas(ciUICanvas *sharedResources, float defaultWidthSize = CI_UI_GLOBAL_CANVAS_WIDTH, float defaultHeightSize = CI_UI_GLOBAL_CANVAS_WIDTH);
    ciUICanvas(const std::string &title);
    
    void init(int x, int y, int w, int h, ciUICanvas *sharedResources = nullptr);
    void copyCanvasStyle(ciUICanvas *styler);
    void copyCanvasProperties(ciUICanvas *styler);
//#ifndef CI_UI_NO_XML
//    virtual void saveSettings(const std::string & fileName);
//    virtual void loadSettings(const std::string & fileName);
//    void setTriggerWidgetsUponLoad(bool _bTriggerWidgetsUponLoad);
//    bool getTriggerWidgetsUponLoad();
//#endif
    ci::gl::TextureFontRef getFontLarge();
    ci::gl::TextureFontRef getFontMedium();
    ci::gl::TextureFontRef getFontSmall();
    bool setFont(const std::string &filename, bool _bAntiAliased=true, bool _bFullCharacterSet=true, bool makeContours=false, float simplifyAmt=0.0, int dpi=CI_UI_FONT_RESOLUTION);
    void setFontSize(ciUIWidgetFontType _kind, int _size, int _resolution = CI_UI_FONT_RESOLUTION);
    void setWidgetSpacing(float _widgetSpacing);
    float getWidgetSpacing();
    bool isEnabled();
    void setVisible(bool _visible);
	void toggleVisible();
    bool hasKeyboardFocus();
	void enable();
	void disable();
    virtual void update();
    virtual void draw();
    void exit();
    
#ifdef CI_UI_TARGET_TOUCH
    virtual void canvasTouchDown(float x, float y, int id);
    virtual void canvasTouchMoved(float x, float y, int id);
    virtual void canvasTouchUp(float x, float y, int id);
    virtual void canvasTouchDoubleTap(float x, float y, int id);
    virtual void canvasTouchCancelled(float x, float y, int id);
    virtual void touchDown(float x, float y, int id);
	virtual void touchMoved(float x, float y, int id);
	virtual void touchUp(float x, float y, int id);
	virtual void touchDoubleTap(float x, float y, int id);
	virtual void touchCancelled(float x, float y, int id);
#else
	virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void windowResized(int w, int h);
#endif	

    virtual void keyPressed(int key);
    virtual void keyReleased(int key);
    virtual bool isHit(int x, int y);
    ciUIWidget *getWidgetHit(float x, float y);
    
    void stateChange();
    virtual void autoSizeToFitWidgets();
    virtual void alignWidgetsVertically(ciUIWidget *widgetToBeAligned, ciUIWidget *widgetToBeingAlignedTo);
    virtual void centerWidgetsOnCanvas(bool centerHorizontally=true, bool centerVertically=true);
    virtual void centerWidgetsHorizontallyOnCanvas();
    virtual void centerWidgetsVerticallyOnCanvas();
    virtual void centerWidgets();
    virtual void addModalWidget(ciUIWidget *widget);
    virtual void removeModalWidget(ciUIWidget *widget);
    virtual void removeWidgets();
    virtual void clearWidgets();  // Mitchell Nordine 2/2/14
    void removeWidget(ciUIWidget *widget);
    void addWidget(ciUIWidget *widget);
	
    ciUIWidget* addWidgetPosition(ciUIWidget *widget, 
                                   ciUIWidgetPosition position = CI_UI_WIDGET_POSITION_DOWN,
                                   ciUIWidgetAlignment align = CI_UI_ALIGN_LEFT,
                                   bool reAdd = false);
    
	ciUIWidget* addWidgetDown(ciUIWidget *widget, ciUIWidgetAlignment align = CI_UI_ALIGN_LEFT, bool reAdd = false);
	ciUIWidget* addWidgetUp(ciUIWidget *widget, ciUIWidgetAlignment align = CI_UI_ALIGN_LEFT, bool reAdd = false);
	ciUIWidget* addWidgetRight(ciUIWidget *widget, ciUIWidgetAlignment align = CI_UI_ALIGN_FREE, bool reAdd = false);
    ciUIWidget* addWidgetLeft(ciUIWidget *widget, ciUIWidgetAlignment align = CI_UI_ALIGN_FREE, bool reAdd = false);
    ciUIWidget* addWidgetSouthOf(ciUIWidget *widget, const std::string &referenceName, bool reAdd = false);
    ciUIWidget* addWidgetNorthOf(ciUIWidget *widget, const std::string &referenceName, bool reAdd = false);
    ciUIWidget* addWidgetWestOf(ciUIWidget *widget, const std::string &referenceName, bool reAdd = false);
    ciUIWidget* addWidgetEastOf(ciUIWidget *widget, const std::string &referenceName, bool reAdd = false);

    ciUISpacer* addSpacer(float h = CI_UI_GLOBAL_SPACING_HEIGHT);
    ciUISpacer* addSpacer(const std::string &name, float h = CI_UI_GLOBAL_SPACING_HEIGHT);
    ciUISpacer* addSpacer(float w, float h);
    ciUISpacer* addSpacer(float w, float h, const std::string &name);
    
    ciUILabel *addLabel(const std::string &name, int size = CI_UI_FONT_MEDIUM);
    ciUILabel *addLabel(const std::string &name, const std::string &label, int size = CI_UI_FONT_MEDIUM);
    
    ciUIFPS *addFPS(int size = CI_UI_FONT_MEDIUM);
    
    ciUISlider* addSlider(const std::string &_name, float _min, float _max, float _value);
    ciUISlider* addSlider(const std::string &_name, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0);
    ciUISlider* addSlider(const std::string &_name, float _min, float _max, float *_value);
    ciUISlider* addSlider(const std::string &_name, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0);
    
    ciUIIntSlider* addIntSlider(const std::string &_name, int _min, int _max, int _value);
    ciUIIntSlider* addIntSlider(const std::string &_name, int _min, int _max, int _value, float w, float h, float x = 0, float y = 0);
    ciUIIntSlider* addIntSlider(const std::string &_name, int _min, int _max, int *_value);
    ciUIIntSlider* addIntSlider(const std::string &_name, int _min, int _max, int *_value, float w, float h, float x = 0, float y = 0);

    ciUIDoubleSlider* addDoubleSlider(const std::string &_name, double _min, double _max, double _value);
    ciUIDoubleSlider* addDoubleSlider(const std::string &_name, double _min, double _max, double _value, float w, float h, float x = 0, float y = 0);
    ciUIDoubleSlider* addDoubleSlider(const std::string &_name, double _min, double _max, double *_value);
    ciUIDoubleSlider* addDoubleSlider(const std::string &_name, double _min, double _max, double *_value, float w, float h, float x = 0, float y = 0);
    
    ciUIRotarySlider* addRotarySlider(const std::string &_name, float _min, float _max, float _value, int _size = CI_UI_FONT_SMALL);
    ciUIRotarySlider* addRotarySlider(const std::string &_name, float _min, float _max, float _value, float w, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    ciUIRotarySlider* addRotarySlider(const std::string &_name, float _min, float _max, float *_value, int _size = CI_UI_FONT_SMALL);
    ciUIRotarySlider* addRotarySlider(const std::string &_name, float _min, float _max, float *_value, float w, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    
    ciUIImageSlider* addImageSlider(const std::string &_name, const std::string &_pathURL, float _min, float _max, float _value);
    ciUIImageSlider* addImageSlider(const std::string &_name, const std::string &_pathURL, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0);
    ciUIImageSlider* addImageSlider(const std::string &_name, const std::string &_pathURL, float _min, float _max, float *_value);
    ciUIImageSlider* addImageSlider(const std::string &_name, const std::string &_pathURL, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0);
    
    ciUINumberDialer *addNumberDialer(const std::string &_name, float _min, float _max, float _value, int _precision);
    ciUINumberDialer *addNumberDialer(const std::string &_name, float _min, float _max, float *_value, int _precision);
    
    ciUIMinimalSlider* addMinimalSlider(const std::string &_name, float _min, float _max, float _value, int size = CI_UI_FONT_SMALL);
    ciUIMinimalSlider* addMinimalSlider(const std::string &_name, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0, int size = CI_UI_FONT_SMALL);
    ciUIMinimalSlider* addMinimalSlider(const std::string &_name, float _min, float _max, float *_value, int size = CI_UI_FONT_SMALL);
    ciUIMinimalSlider* addMinimalSlider(const std::string &_name, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0, int size = CI_UI_FONT_SMALL);

    ciUIRangeSlider* addRangeSlider(const std::string &_name, float _min, float _max, float _valuelow, float _valuehigh);
    ciUIRangeSlider* addRangeSlider(const std::string &_name, float _min, float _max, float _valuelow, float _valuehigh, float w, float h, float x = 0, float y = 0);
    ciUIRangeSlider* addRangeSlider(const std::string &_name, float _min, float _max, float *_valuelow, float *_valuehigh);
    ciUIRangeSlider* addRangeSlider(const std::string &_name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h, float x = 0, float y = 0);
    
    ciUIFPSSlider* addFPSSlider(const std::string &_name, float _max = 400);
    ciUIFPSSlider* addFPSSlider(const std::string &_name, float w, float h, float _max = 400, float x = 0, float y = 0);
    
    ciUIRadio* addRadio(const std::string &_name, const std::vector<std::string> &names, int _orientation = CI_UI_ORIENTATION_VERTICAL, int _size = CI_UI_FONT_SMALL);
    ciUIRadio* addRadio(const std::string &_name, const std::vector<std::string> &names, int _orientation, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    
    ciUIButton* addButton(const std::string &_name, bool _value);
    ciUIButton* addButton(const std::string &_name, bool _value, float w, float h, float x = 0, float y = 0);
    ciUIButton* addButton(const std::string &_name, bool *_value);
    ciUIButton* addButton(const std::string &_name, bool *_value, float w, float h, float x = 0, float y = 0);
    
    ciUIToggle* addToggle(const std::string &_name, bool _value);
    ciUIToggle* addToggle(const std::string &_name, bool _value, float w, float h, float x = 0, float y = 0);
    ciUIToggle* addToggle(const std::string &_name, bool *_value);
    ciUIToggle* addToggle(const std::string &_name, bool *_value, float w, float h, float x = 0, float y = 0);
    
    ciUIToggleMatrix* addToggleMatrix(const std::string &_name, int _rows, int _cols);
    ciUIToggleMatrix* addToggleMatrix(const std::string &_name, int _rows, int _cols, float w, float h);

    ciUI2DPad* add2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f _value);
    ciUI2DPad* add2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f _value, float w, float h, float x = 0, float y = 0);
    ciUI2DPad* add2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f *_value);
    ciUI2DPad* add2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f *_value, float w, float h, float x = 0, float y = 0);
        
    ciUITextInput* addTextInput(const std::string &_name, const std::string &_textstring, int _size = -1);
    ciUITextInput* addTextInput(const std::string &_name, const std::string &_textstring, float w, float h = 0, float x = 0, float y = 0, int _size = -1);
    
    ciUILabelToggle* addLabelToggle(const std::string &_name, bool _value, bool _justifyLeft = false);
    ciUILabelToggle* addLabelToggle(const std::string &_name, bool _value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false);
    ciUILabelToggle* addLabelToggle(const std::string &_name, bool *_value, bool _justifyLeft = false);
    ciUILabelToggle* addLabelToggle(const std::string &_name, bool *_value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false);

    ciUILabelButton* addLabelButton(const std::string &_name, bool _value, bool _justifyLeft = false);
    ciUILabelButton* addLabelButton(const std::string &_name, bool _value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false);
    ciUILabelButton* addLabelButton(const std::string &_name, bool *_value, bool _justifyLeft = false);
    ciUILabelButton* addLabelButton(const std::string &_name, bool *_value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false);

    ciUIDropDownList* addDropDownList(const std::string &_name, const std::vector<std::string> &items);
    ciUIDropDownList* addDropDownList(const std::string &_name, const std::vector<std::string> &items, float w, float x = 0, float y = 0);

    ciUIWaveform* addWaveform(const std::string &_name, float *_buffer, int _bufferSize, float _min = -1.0, float _max = 1.0, float _h = -1);
    ciUIWaveform* addWaveform(const std::string &_name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h);
    
    ciUISpectrum* addSpectrum(const std::string &_name, float *_buffer, int _bufferSize, float _min = 0.0, float _max = 1.0, float _h = CI_UI_GLOBAL_GRAPH_HEIGHT);
    ciUISpectrum* addSpectrum(const std::string &_name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h);
    
    ciUIMovingGraph* addMovingGraph(const std::string &_name, const std::vector<float> &_buffer, int _bufferSize, float _min, float _max, float _h = CI_UI_GLOBAL_GRAPH_HEIGHT);
    ciUIMovingGraph* addMovingGraph(const std::string &_name, const std::vector<float> &_buffer, int _bufferSize, float _min, float _max, float _w, float _h);

    ciUIImage *addImage(const std::string &_name, ci::SurfaceRef _image, float _w, float _h, bool _showLabel = false);
    ciUIImage *addImage(const std::string &_name, ci::SurfaceRef _image, bool _showLabel = false);

    ciUIBaseDraws *addBaseDraws(const std::string &_name, const ci::SurfaceRef &_base, float _w, float _h, bool _showLabel = false);
    ciUIBaseDraws *addBaseDraws(const std::string &_name, const ci::SurfaceRef &_base, bool _showLabel = false);

    ciUIImageSampler *addImageSampler(const std::string &_name, ci::SurfaceRef _image, float _w, float _h);
    ciUIImageSampler *addImageSampler(const std::string &_name, ci::SurfaceRef _image);
    
    ciUIBiLabelSlider *addBiLabelSlider(const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, float _min, float _max, float _value, int _size = CI_UI_FONT_SMALL);
    ciUIBiLabelSlider *addBiLabelSlider(const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, float _min, float _max, float *_value, int _size = CI_UI_FONT_SMALL);
    ciUIBiLabelSlider *addBiLabelSlider(const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, float _min, float _max, float _value, float _w, float _h, int _size = CI_UI_FONT_SMALL);
    ciUIBiLabelSlider *addBiLabelSlider(const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, float _min, float _max, float *_value, float _w, float _h, int _size = CI_UI_FONT_SMALL);
    
    ciUICircleSlider* addCircleSlider(const std::string &_name, float _min, float _max, float _value);
    ciUICircleSlider* addCircleSlider(const std::string &_name, float _min, float _max, float _value, float w, float x = 0, float y = 0);
    ciUICircleSlider* addCircleSlider(const std::string &_name, float _min, float _max, float *_value);
    ciUICircleSlider* addCircleSlider(const std::string &_name, float _min, float _max, float *_value, float w, float x = 0, float y = 0);

    ciUIValuePlotter* addValuePlotter(const std::string &_name, int _bufferSize, float _min, float _max, float *_value, float _h = CI_UI_GLOBAL_GRAPH_HEIGHT);
    ciUIValuePlotter* addValuePlotter(const std::string &_name, int _bufferSize, float _min, float _max, float *_value, float _w, float _h);
    
    ciUI2DGraph *add2DGraph(const std::string &_name, ciUIVec2f _rangeX, ciUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues);
    ciUI2DGraph *add2DGraph(const std::string &_name, ciUIVec2f _rangeX, ciUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues, float _w, float _h, float _x = 0, float _y = 0);

    ciUIImageToggle *addImageToggle(const std::string &_name, const std::string &_path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    ciUIImageToggle *addImageToggle(const std::string &_name, const std::string &_path, bool _value, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    ciUIImageToggle *addImageToggle(const std::string &_name, const std::string &_path, bool *_value, int _size = CI_UI_FONT_SMALL);
    ciUIImageToggle *addImageToggle(const std::string &_name, const std::string &_path, bool _value, int _size = CI_UI_FONT_SMALL);

    ciUIImageButton *addImageButton(const std::string &_name, const std::string &_path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    ciUIImageButton *addImageButton(const std::string &_name, const std::string &_path, bool _value, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    ciUIImageButton *addImageButton(const std::string &_name, const std::string &_path, bool *_value, int _size = CI_UI_FONT_SMALL);
    ciUIImageButton *addImageButton(const std::string &_name, const std::string &_path, bool _value, int _size = CI_UI_FONT_SMALL);
    
    ciUIMultiImageButton *addMultiImageButton(const std::string &_name, const std::string &_path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    ciUIMultiImageButton *addMultiImageButton(const std::string &_name, const std::string &_path, bool _value, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    ciUIMultiImageButton *addMultiImageButton(const std::string &_name, const std::string &_path, bool *_value, int _size = CI_UI_FONT_SMALL);
    ciUIMultiImageButton *addMultiImageButton(const std::string &_name, const std::string &_path, bool _value, int _size = CI_UI_FONT_SMALL);
    
    ciUIMultiImageToggle *addMultiImageToggle(const std::string &_name, const std::string &_path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    ciUIMultiImageToggle *addMultiImageToggle(const std::string &_name, const std::string &_path, bool _value, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_SMALL);
    ciUIMultiImageToggle *addMultiImageToggle(const std::string &_name, const std::string &_path, bool *_value, int _size = CI_UI_FONT_SMALL);
    ciUIMultiImageToggle *addMultiImageToggle(const std::string &_name, const std::string &_path, bool _value, int _size = CI_UI_FONT_SMALL);
    
    ciUITextArea* addTextArea(const std::string &_name, const std::string &_textstring, int _size = CI_UI_FONT_MEDIUM);
    
    ciUISortableList *addSortableList(const std::string &_name, const std::vector<std::string> &_items, int _size = -1, int _itemHeight = 30);
    
    void resetPlacer();
    void setPlacer(ciUIWidget *referenceWidget);
	void setLabelFont(ciUILabel *label);
    void setRetinaResolution();
    void setGlobalSliderHeight(float _globalSliderHeight);
    void setGlobalGraphHeight(float _globalGraphHeight);
    void setGlobalButtonDimension(float _globalButtonDimension);
    void setGlobalSpacerHeight(float _globalSpacerHeight);
    float getGlobalSliderHeight();
    float getGlobalGraphHeight();
    float getGlobalButtonDimension();
    float getGlobalSpacerHeight();
    void setGlobalCanvasWidth(float _globalCanvasWidth);
    float getGlobalCanvasWidth();
	void setWidgetPosition(ciUIWidgetPosition _position, int _align = -1);
    void setWidgetFontSize(ciUIWidgetFontType _widgetFontSize);
    
    ciUIWidgetPosition getWidgetPosition();
    ciUIWidgetFontType getWidgetFontSize();
	void triggerEvent(ciUIWidget *child);
    void setUIColors(ciUIColor &cb, ciUIColor &co, ciUIColor &coh, ciUIColor &cf, ciUIColor &cfh, ciUIColor &cp, ciUIColor &cpo);
    void setTheme(int theme);
    ciUIColor& getWidgetColorPadded();
	ciUIColor& getWidgetColorPaddedOutline();
	ciUIColor& getWidgetColorBack();
	ciUIColor& getWidgetColorOutline();
	ciUIColor& getWidgetColorOutlineHighlight();
	ciUIColor& getWidgetColorFill();
	ciUIColor& getWidgetColorFillHighlight();
    void setWidgetDrawingProperties(ciUIWidget *widget);
    void setWidgetColor(ciUIWidget *widget);
	void setWidgetColor(int _target, ciUIColor _color);
    ciUIWidget *getWidget(const std::string &_name, int widgetID = -1);
    void removeWidget(const std::string &_name);
    virtual void setPosition(int x, int y);
    virtual void setHeight(float _height);
    virtual void setWidth(float _width);
    virtual void setDimensions(float _width, float _height);
	void setDrawPadding(bool _draw_padded_rect);
    void setDrawWidgetPadding(bool _draw_padded_rect);
    bool getDrawWidgetPadding();
	void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    void setDrawWidgetPaddingOutline(bool _draw_padded_rect_outline);
    bool getDrawWidgetPaddingOutline();
    const std::vector<ciUIWidget*> &getWidgets() const;
    const std::vector<ciUIWidget*> &getWidgetsOfType(ciUIWidgetType type) const;
    
    typedef ci::signals::Signal<void ( const ciUIEventArgs & )> NewGuiEventSignal_t;
	NewGuiEventSignal_t newGUIEvent;

protected:
    void pushbackWidget(ciUIWidget *widget, bool addWidgetToFront = false);
    //Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)
    bool updateFont(ciUIWidgetFontType _kind, const std::string &filename, int fontsize, bool _bAntiAliased=true, bool _bFullCharacterSet=false, bool makeContours=false, float simplifyAmt=0.3, int dpi=0);
    void checkForKeyFocus(ciUIWidget *child);

	ci::gl::TextureFontRef font_large;
	ci::gl::TextureFontRef font_medium; 		
	ci::gl::TextureFontRef font_small;
    ciUIEventArgs *GUIevent;

    bool bInsideCanvas;
    bool hasSharedResources;
    
    std::multimap<std::string, ciUIWidget*> widgets_map;
	std::vector<ciUIWidget*> widgets;
    std::map<std::string, ciUIWidget*> widgetsAreModal;
	std::vector<ciUIWidget*> widgetsWithState;
	std::vector<ciUIWidget*> lastAddeds;

	bool enable_highlight_outline;
	bool enable_highlight_fill;
	bool enabled;
    bool bTriggerWidgetsUponLoad;
    int uniqueIDs; 
    bool hasKeyBoard; 
    
    float widgetSpacing;
    float globalCanvasWidth;
    float globalSliderHeight;
    float globalGraphHeight;
    float globalButtonDimension;
    float globalSpacerHeight;
    
    std::string fontName;

    ciUIWidgetPosition widgetPosition;
    ciUIWidgetAlignment widgetAlign;
    ciUIWidgetFontType widgetFontSize;
    
	ciUIColor widget_color_back;
	ciUIColor widget_color_outline;
	ciUIColor widget_color_outline_highlight;
	ciUIColor widget_color_fill;
	ciUIColor widget_color_fill_highlight;
    ciUIColor widget_color_padded_rect;
	ciUIColor widget_color_padded_rect_outline;
    
    bool bDrawWidgetPadding;
    bool bDrawWidgetPaddingOutline;    
};
