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

#include "ciUICanvas.h"
#include "ciUI.h"

ciUICanvas::~ciUICanvas()
{
    disable();
    if(GUIevent != nullptr)
    {
        delete GUIevent;
    }
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it)
    {
        ciUIWidget *w = (*it);
        delete w;
    }
    widgets.clear();
}

// Copy constructor to handle heap allocation during a copy.
ciUICanvas::ciUICanvas(const ciUICanvas &other)
: ciUIWidget(),
hasSharedResources(false),
widget_color_back(other.widget_color_back),
widget_color_outline(other.widget_color_outline),
widget_color_outline_highlight(other.widget_color_outline_highlight),
widget_color_fill(other.widget_color_fill),
widget_color_fill_highlight(other.widget_color_fill_highlight),
widget_color_padded_rect(other.widget_color_padded_rect),
widget_color_padded_rect_outline(other.widget_color_padded_rect_outline),
widgetSpacing(other.widgetSpacing),
globalCanvasWidth(other.globalCanvasWidth),
globalSliderHeight(other.globalSliderHeight),
globalGraphHeight(other.globalGraphHeight),
globalButtonDimension(other.globalButtonDimension),
globalSpacerHeight(other.globalSpacerHeight),
bDrawWidgetPadding(other.bDrawWidgetPadding),
bDrawWidgetPaddingOutline(other.bDrawWidgetPaddingOutline),
fontName(other.fontName),
widgetPosition(other.widgetPosition),
widgetAlign(other.widgetAlign),
widgetFontSize(other.widgetFontSize),
enable_highlight_outline(other.enable_highlight_outline),
enable_highlight_fill(other.enable_highlight_fill),
bTriggerWidgetsUponLoad(other.bTriggerWidgetsUponLoad),
uniqueIDs(other.uniqueIDs),                             //might be problematic
hasKeyBoard(other.hasKeyBoard),
bInsideCanvas(other.bInsideCanvas),
enabled(other.enabled)
{
    if(other.rect) {
        init(other.rect->getX(), other.rect->getY(), other.rect->getWidth(), other.rect->getHeight());
    }
    else {
        init(0,0,CI_UI_GLOBAL_CANVAS_WIDTH, CI_UI_GLOBAL_CANVAS_WIDTH);
    }
    //Handle Adding Widgets...
    //widgets_map(other.widgets_map),                         //might be problematic
    //widgets(other.widgets),                                 //might be problematic
    //widgetsAreModal(other.widgetsAreModal),                 //might be problematic
    //widgetsWithState(other.widgetsWithState),               //might be problematic
    //lastAddeds(other.lastAddeds),                           //might be problematic
}

// Assignment operator to handle heap allocation during assignment.
ciUICanvas& ciUICanvas::operator=(const ciUICanvas &other)
{
    hasSharedResources = false;
    widget_color_back = other.widget_color_back;
    widget_color_outline = other.widget_color_outline;
    widget_color_outline_highlight = other.widget_color_outline_highlight;
    widget_color_fill = other.widget_color_fill;
    widget_color_fill_highlight = other.widget_color_fill_highlight;
    widget_color_padded_rect = other.widget_color_padded_rect;
    widget_color_padded_rect_outline = other.widget_color_padded_rect_outline;
    widgetSpacing = other.widgetSpacing;
    globalCanvasWidth = other.globalCanvasWidth;
    globalSliderHeight = other.globalSliderHeight;
    globalGraphHeight = other.globalGraphHeight;
    globalButtonDimension = other.globalButtonDimension;
    globalSpacerHeight = other.globalSpacerHeight;
    bDrawWidgetPadding = other.bDrawWidgetPadding;
    bDrawWidgetPaddingOutline = other.bDrawWidgetPaddingOutline;
    fontName = other.fontName;
    widgetPosition = other.widgetPosition;
    widgetAlign = other.widgetAlign;
    widgetFontSize = other.widgetFontSize;
    enable_highlight_outline = other.enable_highlight_outline;
    enable_highlight_fill = other.enable_highlight_fill;
    bTriggerWidgetsUponLoad = other.bTriggerWidgetsUponLoad;
    uniqueIDs = other.uniqueIDs;
    hasKeyBoard = other.hasKeyBoard;
    bInsideCanvas = other.bInsideCanvas;
    enabled = other.enabled;
    state = other.state;
    if(other.rect) {
        init(other.rect->getX(), other.rect->getY(), other.rect->getWidth(), other.rect->getHeight());
    }
    else {
        init(0,0,CI_UI_GLOBAL_CANVAS_WIDTH, CI_UI_GLOBAL_CANVAS_WIDTH);
    }
    for(int i = 0; i < other.widgets.size(); ++i)
    {
        addWidget((new ciUIWidget(*(other.widgets[i]))));
    }

    return *this;
}

ciUICanvas::ciUICanvas(ciUIRectangle r)
: ciUIWidget(),
hasSharedResources(false),
widget_color_back(CI_UI_COLOR_BACK),
widget_color_outline(CI_UI_COLOR_OUTLINE),
widget_color_outline_highlight(CI_UI_COLOR_OUTLINE_HIGHLIGHT),
widget_color_fill(CI_UI_COLOR_FILL),
widget_color_fill_highlight(CI_UI_COLOR_FILL_HIGHLIGHT),
widget_color_padded_rect(CI_UI_COLOR_PADDED),
widget_color_padded_rect_outline(CI_UI_COLOR_PADDED_OUTLINE),
widgetSpacing(CI_UI_GLOBAL_WIDGET_SPACING),
globalCanvasWidth(CI_UI_GLOBAL_CANVAS_WIDTH),
globalSliderHeight(CI_UI_GLOBAL_SLIDER_HEIGHT),
globalGraphHeight(CI_UI_GLOBAL_GRAPH_HEIGHT),
globalButtonDimension(CI_UI_GLOBAL_BUTTON_DIMENSION),
globalSpacerHeight(CI_UI_GLOBAL_SPACING_HEIGHT),
bDrawWidgetPadding(CI_UI_DRAW_PADDING),
bDrawWidgetPaddingOutline(CI_UI_DRAW_PADDING_OUTLINE),
fontName(CI_UI_FONT_NAME),
widgetPosition(CI_UI_WIDGET_POSITION_DOWN),
widgetAlign(CI_UI_ALIGN_LEFT),
widgetFontSize(CI_UI_FONT_SMALL),
enable_highlight_outline(false),
enable_highlight_fill(false),
bTriggerWidgetsUponLoad(true),
uniqueIDs(0),
hasKeyBoard(false),
bInsideCanvas(false),
enabled(false)
{
    init(r.getX(false), r.getY(false), r.width, r.height);
}

ciUICanvas::ciUICanvas(float x, float y, float w, float h)
: ciUIWidget(),
hasSharedResources(false),
widget_color_back(CI_UI_COLOR_BACK),
widget_color_outline(CI_UI_COLOR_OUTLINE),
widget_color_outline_highlight(CI_UI_COLOR_OUTLINE_HIGHLIGHT),
widget_color_fill(CI_UI_COLOR_FILL),
widget_color_fill_highlight(CI_UI_COLOR_FILL_HIGHLIGHT),
widget_color_padded_rect(CI_UI_COLOR_PADDED),
widget_color_padded_rect_outline(CI_UI_COLOR_PADDED_OUTLINE),
widgetSpacing(CI_UI_GLOBAL_WIDGET_SPACING),
globalCanvasWidth(CI_UI_GLOBAL_CANVAS_WIDTH),
globalSliderHeight(CI_UI_GLOBAL_SLIDER_HEIGHT),
globalGraphHeight(CI_UI_GLOBAL_GRAPH_HEIGHT),
globalButtonDimension(CI_UI_GLOBAL_BUTTON_DIMENSION),
globalSpacerHeight(CI_UI_GLOBAL_SPACING_HEIGHT),
bDrawWidgetPadding(CI_UI_DRAW_PADDING),
bDrawWidgetPaddingOutline(CI_UI_DRAW_PADDING_OUTLINE),
fontName(CI_UI_FONT_NAME),
widgetPosition(CI_UI_WIDGET_POSITION_DOWN),
widgetAlign(CI_UI_ALIGN_LEFT),
widgetFontSize(CI_UI_FONT_SMALL),
enable_highlight_outline(false),
enable_highlight_fill(false),
bTriggerWidgetsUponLoad(true),
uniqueIDs(0),
hasKeyBoard(false),
bInsideCanvas(false),
enabled(false)
{
    init(x, y, w, h);
}

ciUICanvas::ciUICanvas(float x, float y, float w, float h, ciUICanvas *sharedResources)
: ciUIWidget(),
hasSharedResources(true),
widget_color_back(CI_UI_COLOR_BACK),
widget_color_outline(CI_UI_COLOR_OUTLINE),
widget_color_outline_highlight(CI_UI_COLOR_OUTLINE_HIGHLIGHT),
widget_color_fill(CI_UI_COLOR_FILL),
widget_color_fill_highlight(CI_UI_COLOR_FILL_HIGHLIGHT),
widget_color_padded_rect(CI_UI_COLOR_PADDED),
widget_color_padded_rect_outline(CI_UI_COLOR_PADDED_OUTLINE),
widgetSpacing(CI_UI_GLOBAL_WIDGET_SPACING),
globalCanvasWidth(CI_UI_GLOBAL_CANVAS_WIDTH),
globalSliderHeight(CI_UI_GLOBAL_SLIDER_HEIGHT),
globalGraphHeight(CI_UI_GLOBAL_GRAPH_HEIGHT),
globalButtonDimension(CI_UI_GLOBAL_BUTTON_DIMENSION),
globalSpacerHeight(CI_UI_GLOBAL_SPACING_HEIGHT),
bDrawWidgetPadding(CI_UI_DRAW_PADDING),
bDrawWidgetPaddingOutline(CI_UI_DRAW_PADDING_OUTLINE),
fontName(CI_UI_FONT_NAME),
widgetPosition(CI_UI_WIDGET_POSITION_DOWN),
widgetAlign(CI_UI_ALIGN_LEFT),
widgetFontSize(CI_UI_FONT_SMALL),
enable_highlight_outline(false),
enable_highlight_fill(false),
bTriggerWidgetsUponLoad(true),
uniqueIDs(0),
hasKeyBoard(false),
bInsideCanvas(false),
enabled(false)
{
    init(x, y, w, h, sharedResources);
}

ciUICanvas::ciUICanvas(float defaultWidthSize, float defaultHeightSize)
: ciUIWidget(),
hasSharedResources(false),
widget_color_back(CI_UI_COLOR_BACK),
widget_color_outline(CI_UI_COLOR_OUTLINE),
widget_color_outline_highlight(CI_UI_COLOR_OUTLINE_HIGHLIGHT),
widget_color_fill(CI_UI_COLOR_FILL),
widget_color_fill_highlight(CI_UI_COLOR_FILL_HIGHLIGHT),
widget_color_padded_rect(CI_UI_COLOR_PADDED),
widget_color_padded_rect_outline(CI_UI_COLOR_PADDED_OUTLINE),
widgetSpacing(CI_UI_GLOBAL_WIDGET_SPACING),
globalCanvasWidth(CI_UI_GLOBAL_CANVAS_WIDTH),
globalSliderHeight(CI_UI_GLOBAL_SLIDER_HEIGHT),
globalGraphHeight(CI_UI_GLOBAL_GRAPH_HEIGHT),
globalButtonDimension(CI_UI_GLOBAL_BUTTON_DIMENSION),
globalSpacerHeight(CI_UI_GLOBAL_SPACING_HEIGHT),
bDrawWidgetPadding(CI_UI_DRAW_PADDING),
bDrawWidgetPaddingOutline(CI_UI_DRAW_PADDING_OUTLINE),
fontName(CI_UI_FONT_NAME),
widgetPosition(CI_UI_WIDGET_POSITION_DOWN),
widgetAlign(CI_UI_ALIGN_LEFT),
widgetFontSize(CI_UI_FONT_SMALL),
enable_highlight_outline(false),
enable_highlight_fill(false),
bTriggerWidgetsUponLoad(true),
uniqueIDs(0),
hasKeyBoard(false),
bInsideCanvas(false),
enabled(false)
{
    init(0, 0, defaultWidthSize, defaultHeightSize);
    setGlobalCanvasWidth(defaultWidthSize);
}

ciUICanvas::ciUICanvas(ciUICanvas *sharedResources, float defaultWidthSize, float defaultHeightSize)
: ciUIWidget(),
hasSharedResources(true),
widget_color_back(CI_UI_COLOR_BACK),
widget_color_outline(CI_UI_COLOR_OUTLINE),
widget_color_outline_highlight(CI_UI_COLOR_OUTLINE_HIGHLIGHT),
widget_color_fill(CI_UI_COLOR_FILL),
widget_color_fill_highlight(CI_UI_COLOR_FILL_HIGHLIGHT),
widget_color_padded_rect(CI_UI_COLOR_PADDED),
widget_color_padded_rect_outline(CI_UI_COLOR_PADDED_OUTLINE),
widgetSpacing(CI_UI_GLOBAL_WIDGET_SPACING),
globalCanvasWidth(CI_UI_GLOBAL_CANVAS_WIDTH),
globalSliderHeight(CI_UI_GLOBAL_SLIDER_HEIGHT),
globalGraphHeight(CI_UI_GLOBAL_GRAPH_HEIGHT),
globalButtonDimension(CI_UI_GLOBAL_BUTTON_DIMENSION),
globalSpacerHeight(CI_UI_GLOBAL_SPACING_HEIGHT),
bDrawWidgetPadding(CI_UI_DRAW_PADDING),
bDrawWidgetPaddingOutline(CI_UI_DRAW_PADDING_OUTLINE),
fontName(CI_UI_FONT_NAME),
widgetPosition(CI_UI_WIDGET_POSITION_DOWN),
widgetAlign(CI_UI_ALIGN_LEFT),
widgetFontSize(CI_UI_FONT_SMALL),
enable_highlight_outline(false),
enable_highlight_fill(false),
bTriggerWidgetsUponLoad(true),
uniqueIDs(0),
hasKeyBoard(false),
bInsideCanvas(false),
enabled(false)
{
    init(0, 0, defaultWidthSize, defaultHeightSize, sharedResources);
    setGlobalCanvasWidth(defaultWidthSize);
}

ciUICanvas::ciUICanvas(const std::string &title)
: ciUIWidget(),
hasSharedResources(false),
widget_color_back(CI_UI_COLOR_BACK),
widget_color_outline(CI_UI_COLOR_OUTLINE),
widget_color_outline_highlight(CI_UI_COLOR_OUTLINE_HIGHLIGHT),
widget_color_fill(CI_UI_COLOR_FILL),
widget_color_fill_highlight(CI_UI_COLOR_FILL_HIGHLIGHT),
widget_color_padded_rect(CI_UI_COLOR_PADDED),
widget_color_padded_rect_outline(CI_UI_COLOR_PADDED_OUTLINE),
widgetSpacing(CI_UI_GLOBAL_WIDGET_SPACING),
globalCanvasWidth(CI_UI_GLOBAL_CANVAS_WIDTH),
globalSliderHeight(CI_UI_GLOBAL_SLIDER_HEIGHT),
globalGraphHeight(CI_UI_GLOBAL_GRAPH_HEIGHT),
globalButtonDimension(CI_UI_GLOBAL_BUTTON_DIMENSION),
globalSpacerHeight(CI_UI_GLOBAL_SPACING_HEIGHT),
bDrawWidgetPadding(CI_UI_DRAW_PADDING),
bDrawWidgetPaddingOutline(CI_UI_DRAW_PADDING_OUTLINE),
fontName(CI_UI_FONT_NAME),
widgetPosition(CI_UI_WIDGET_POSITION_DOWN),
widgetAlign(CI_UI_ALIGN_LEFT),
widgetFontSize(CI_UI_FONT_SMALL),
enable_highlight_outline(false),
enable_highlight_fill(false),
bTriggerWidgetsUponLoad(true),
uniqueIDs(0),
hasKeyBoard(false),
bInsideCanvas(false),
enabled(false)
{
    init(0,0,CI_UI_GLOBAL_CANVAS_WIDTH, CI_UI_GLOBAL_CANVAS_WIDTH);
    addLabel(title);
    addSpacer();
}

void ciUICanvas::init(int x, int y, int w, int h, ciUICanvas *sharedResources)
{
    initRect(x, y, w, h);
    name = "CI_UI_WIDGET_CANVAS";
    kind = CI_UI_WIDGET_CANVAS;
    if(hasSharedResources)
    {
        font_large = sharedResources->getFontLarge();
        font_medium = sharedResources->getFontMedium();
        font_small = sharedResources->getFontSmall();
    }
    else
    {
        //ci::Font font(fontName, fontName);
        font_large.reset(); //ci::gl::TextureFont::create(font);
        font_medium.reset(); //ci::gl::TextureFont::create(font);
        font_small.reset();// = //ci::gl::TextureFont::create(font);
        setFont(fontName,true, true, false, 0.0, CI_UI_FONT_RESOLUTION);
    }
    
    font = font_medium;
    GUIevent = new ciUIEventArgs(this);
    enable();
}

void ciUICanvas::copyCanvasStyle(ciUICanvas *styler)
{
    setUIColors(styler->getWidgetColorBack(),
                styler->getWidgetColorOutline(),
                styler->getWidgetColorOutlineHighlight(),
                styler->getWidgetColorFill(),
                styler->getWidgetColorFillHighlight(),
                styler->getWidgetColorPadded(),
                styler->getWidgetColorPaddedOutline());
    
    setColorBack(styler->getColorBack());
    setColorOutline(styler->getColorOutline());
    setColorOutlineHighlight(styler->getColorOutlineHighlight());
    setColorFill(styler->getColorFill());
    setColorFillHighlight(styler->getColorFillHighlight());
    setColorPadded(styler->getColorPadded());
    setColorPaddedOutline(styler->getColorPaddedOutline());
    
    setDrawBack(styler->getDrawBack());
    setDrawOutline(styler->getDrawOutline());
    setDrawOutlineHighLight(styler->getDrawOutlineHighLight());
    setDrawFill(styler->getDrawFill());
    setDrawFillHighLight(styler->getDrawFillHighLight());
    setDrawPadding(styler->getDrawPadding());
    setDrawPaddingOutline(styler->getDrawPaddingOutline());
    
    setDrawWidgetPadding(styler->getDrawWidgetPadding());
    setDrawWidgetPaddingOutline(styler->getDrawWidgetPaddingOutline());
}

void ciUICanvas::copyCanvasProperties(ciUICanvas *styler) {
    setGlobalCanvasWidth(styler->getRect()->getWidth());
    setGlobalButtonDimension(styler->getGlobalButtonDimension());
    setGlobalSliderHeight(styler->getGlobalSliderHeight());
    setGlobalSpacerHeight(styler->getGlobalSpacerHeight());
    setGlobalGraphHeight(styler->getGlobalGraphHeight());
    
    setPadding(styler->getPadding());
    setWidgetSpacing(styler->getWidgetSpacing());
    
    setWidgetPosition(styler->getWidgetPosition());
    setWidgetFontSize(styler->getWidgetFontSize());
}

#ifndef CI_UI_NO_XML

void ciUICanvas::saveSettings(const std::string &fileName)
{
    ofxXmlSettings *XML = new ofxXmlSettings();
    int len = widgetsWithState.size();
    for(int i = 0; i < len; ++i) {
        int index = XML->addTag("Widget");
        if(XML->pushTag("Widget", index)) {
            XML->setValue("Kind", widgetsWithState[i]->getKind(), 0);
            XML->setValue("Name", widgetsWithState[i]->getName(), 0);
            widgetsWithState[i]->saveState(XML);
        }
        XML->popTag();
    }
    XML->saveFile(fileName);
    delete XML;
}

void ciUICanvas::setTriggerWidgetsUponLoad(bool _bTriggerWidgetsUponLoad)
{
    bTriggerWidgetsUponLoad = _bTriggerWidgetsUponLoad;
}

bool ciUICanvas::getTriggerWidgetsUponLoad()
{
    return bTriggerWidgetsUponLoad;
}

void ciUICanvas::loadSettings(const string &fileName)
{
    ofxXmlSettings *XML = new ofxXmlSettings();
    XML->loadFile(fileName);
    int widgetTags = XML->getNumTags("Widget");
    for(int i = 0; i < widgetTags; ++i) {
        XML->pushTag("Widget", i);
        string name = XML->getValue("Name", "nullptr", 0);
        ciUIWidget *widget = getWidget(name);
        if(widget != nullptr && widget->hasState()) {
            widget->loadState(XML);
            if(bTriggerWidgetsUponLoad) {
                triggerEvent(widget);
            }
        }
        XML->popTag();
    }
    hasKeyBoard = false;
    delete XML;
}

#endif

ci::gl::TextureFontRef ciUICanvas::getFontLarge()
{
    return font_large;
}

ci::gl::TextureFontRef ciUICanvas::getFontMedium()
{
    return font_medium;
}

ci::gl::TextureFontRef ciUICanvas::getFontSmall()
{
    return font_small;
}

//Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)
bool ciUICanvas::setFont(const std::string &filename,
                          bool _bAntiAliased,
                          bool _bFullCharacterSet,
                          bool makeContours,
                          float simplifyAmt,
                          int dpi)
{
    bool bLarge = updateFont(CI_UI_FONT_LARGE, filename, CI_UI_FONT_LARGE_SIZE, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
    bool bMedium = updateFont(CI_UI_FONT_MEDIUM, filename, CI_UI_FONT_MEDIUM_SIZE, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
    bool bSmall = updateFont(CI_UI_FONT_SMALL, filename, CI_UI_FONT_SMALL_SIZE, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
    bool successful = bLarge && bMedium && bSmall;
    if( successful ) fontName = filename;
    return successful;
}

void ciUICanvas::setFontSize(ciUIWidgetFontType _kind, int _size, int _resolution) {
    //ci::gl::TextureFont::Format fmt;
    //fmt.textureWidth(_resolution);
    //fmt.textureHeight(_resolution);
    
    switch(_kind) {
        case CI_UI_FONT_LARGE:
        {
            
            font_large = ci::gl::TextureFont::create(ci::Font(fontName, _size));
        }
            break;
            
        case CI_UI_FONT_MEDIUM:
        {
            font_medium = ci::gl::TextureFont::create(ci::Font(fontName, _size));
        }
            break;
            
        case CI_UI_FONT_SMALL:
        {
            font_small = ci::gl::TextureFont::create(ci::Font(fontName, _size));
        }
            break;
    }
}

void ciUICanvas::setWidgetSpacing(float _widgetSpacing) {
    widgetSpacing = _widgetSpacing;
}

float ciUICanvas::getWidgetSpacing() {
    return widgetSpacing;
}

bool ciUICanvas::isEnabled() {
    return enabled;
}

void ciUICanvas::setVisible(bool _visible) {
    visible = _visible;
    if(visible) {
        enable();
    }
    else {
        disable();
    }
}


void ciUICanvas::toggleVisible() {
    if(isEnabled()) {
        disable();
    }
    else {
        enable();
    }
}

bool ciUICanvas::hasKeyboardFocus() {
    return hasKeyBoard;
}

void ciUICanvas::enable() {
    if(!isEnabled()) {
        enabled = true;
        visible = true;
        EnableCallbacks();
    }
}

void ciUICanvas::disable() {
    if(isEnabled()) {
        enabled = false;
        visible = false;
        DisableCallbacks();
    }
}

void ciUICanvas::update()
{
    if (!isVisible()) { return; } // Custom to save framerate
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it)
    {
        (*it)->update();
    }
}

void ciUICanvas::draw() {
    //ciUIPushStyle();

    // TODO Scoped states!!!
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_LIGHTING);

    
    glEnable(GL_BLEND);
#ifndef CI_UI_TARGET_TOUCH
    glBlendEquation(GL_FUNC_ADD);
#endif
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //ciUISetRectMode(CI_UI_RECTMODE_CORNER);
    //ciUISetLineWidth(1.0);

    drawPadded();
    drawPaddedOutline();
    drawBack();
    drawFill();
    drawFillHighlight();
    drawOutline();
    drawOutlineHighlight();

    std::vector<ciUIWidget *>::reverse_iterator it = widgets.rbegin();
    std::vector<ciUIWidget *>::reverse_iterator eit = widgets.rend();
    for(; it != eit; ++it) {
        if((*it)->isVisible() && ((*it)->getRect()->rInside(*rect) || (*it)->isModal())) {
            (*it)->draw();
        }
    }
    //ciUIPopStyle();
}

void ciUICanvas::exit() {
    
}

#ifdef CI_UI_TARGET_TOUCH

void ciUICanvas::canvasTouchDown(float x, float y, int id)
{
    if(rect->inside(x, y))
    {
        vector<ciUIWidget *>::iterator it = widgets.begin();
        vector<ciUIWidget *>::iterator eit = widgets.end();
        for(; it != eit; ++it)
        {
            if((*it)->isVisible())
            {
                (*it)->touchDown(x, y, id);
            }
        }
    }
    else
    {
        map<string, ciUIWidget*>::iterator it = widgetsAreModal.begin();
        map<string, ciUIWidget*>::iterator eit = widgetsAreModal.end();
        for (; it != eit; ++it)
        {
            if((*it).second->isVisible()) (*it).second->touchDown(x, y, id);
        }
    }
}

void ciUICanvas::canvasTouchMoved(float x, float y, int id)
{
    vector<ciUIWidget *>::iterator it = widgets.begin();
    vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it)
    {
        if((*it)->isVisible())
        {
            (*it)->touchMoved(x, y, id);
        }
    }
}

void ciUICanvas::canvasTouchUp(float x, float y, int id)
{
    vector<ciUIWidget *>::iterator it = widgets.begin();
    vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it)
    {
        if((*it)->isVisible())
        {
            (*it)->touchUp(x, y, id);
        }
    }
}

void ciUICanvas::canvasTouchDoubleTap(float x, float y, int id)
{
    if(rect->inside(x, y))
    {
        vector<ciUIWidget *>::iterator it = widgets.begin();
        vector<ciUIWidget *>::iterator eit = widgets.end();
        for(; it != eit; ++it)
        {
            if((*it)->isVisible())
            {
                (*it)->touchDoubleTap(x, y, id);
            }
        }
    }
    else
    {
        map<string, ciUIWidget*>::iterator it = widgetsAreModal.begin();
        map<string, ciUIWidget*>::iterator eit = widgetsAreModal.end();
        for(; it != eit; ++it)
        {
            if((*it).second->isVisible())
            {
                (*it).second->touchDoubleTap(x, y, id);
            }
        }
    }
}

void ciUICanvas::canvasTouchCancelled(float x, float y, int id) {
    if(rect->inside(x, y)) {
        vector<ciUIWidget *>::iterator it = widgets.begin();
        vector<ciUIWidget *>::iterator eit = widgets.end();
        for(; it != eit; ++it) {
            if((*it)->isVisible()) {
                (*it)->touchCancelled(x, y, id);
            }
        }
    }
    else {
        map<string, ciUIWidget*>::iterator it = widgetsAreModal.begin();
        map<string, ciUIWidget*>::iterator eit = widgetsAreModal.end();
        for(; it != eit; ++it) {
            if((*it).second->isVisible()) {
                (*it).second->touchCancelled(x, y, id);
            }
        }
    }
}

void ciUICanvas::touchDown(float x, float y, int id) {
    canvasTouchDown(x, y, id);
}

void ciUICanvas::touchMoved(float x, float y, int id) {
    canvasTouchMoved(x, y, id);
}

void ciUICanvas::touchUp(float x, float y, int id) {
    canvasTouchUp(x, y, id);
}

void ciUICanvas::touchDoubleTap(float x, float y, int id) {
    canvasTouchDoubleTap(x, y, id);
}

void ciUICanvas::touchCancelled(float x, float y, int id) {
    canvasTouchCancelled(x, y, id);
}

#else

void ciUICanvas::mouseMoved(int x, int y) {
    if(rect->inside(x, y)) {
        std::vector<ciUIWidget *>::iterator it = widgets.begin();
        std::vector<ciUIWidget *>::iterator eit = widgets.end();
        for(; it != eit; ++it) {
            if((*it)->isVisible()) {
                (*it)->mouseMoved(x, y);
            }
        }
        bInsideCanvas = true;
    }
    else{
        bInsideCanvas = false;
        std::map<std::string, ciUIWidget*>::iterator it = widgetsAreModal.begin();
        std::map<std::string, ciUIWidget*>::iterator eit = widgetsAreModal.end();
        for(; it != eit; ++it) {
            if((*it).second->isVisible()) {
                (*it).second->mouseMoved(x, y);
            }
        }
    }
}

void ciUICanvas::mouseDragged(int x, int y, int button) {
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it) {
        if((*it)->isVisible()) {
            (*it)->mouseDragged(x, y, button);
        }
    }
}

void ciUICanvas::mousePressed(int x, int y, int button) {
    if(rect->inside(x, y)) {
        std::vector<ciUIWidget *>::iterator it = widgets.begin();
        std::vector<ciUIWidget *>::iterator eit = widgets.end();
        for(; it != eit; ++it) {
            if((*it)->isVisible()) {
                (*it)->mousePressed(x, y, button);
            }
        }
    }
    else {
        std::map<std::string, ciUIWidget*>::iterator it = widgetsAreModal.begin();
        std::map<std::string, ciUIWidget*>::iterator eit = widgetsAreModal.end();
        for(; it != eit; ++it) {
            if((*it).second->isVisible()) {
                (*it).second->mousePressed(x, y, button);
            }
        }
    }
}

void ciUICanvas::mouseReleased(int x, int y, int button)
{
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it)
    {
        if((*it)->isVisible())
        {
            (*it)->mouseReleased(x, y, button);
        }
    }
}

void ciUICanvas::windowResized(int w, int h) {
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it)
    {
        (*it)->windowResized(w, h);
    }
}

#endif

void ciUICanvas::keyPressed(int key)
{
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it)
    {
        (*it)->keyPressed(key);
    }
}

void ciUICanvas::keyReleased(int key)
{
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it)
    {
        (*it)->keyReleased(key);
    }
}

bool ciUICanvas::isHit(int x, int y)
{
    if(isEnabled() && rect->inside(x, y)) {
        return true;
    }
    else {
        std::map<std::string, ciUIWidget*>::iterator it = widgetsAreModal.begin();
        std::map<std::string, ciUIWidget*>::iterator eit = widgetsAreModal.end();
        for(; it != eit; ++it) {
            if((*it).second->isVisible() && (*it).second->isHit(x, y)) {
                return true;
            }
        }
    }
    return false;
}

ciUIWidget *ciUICanvas::getWidgetHit(float x, float y)
{
    if(isEnabled() && rect->inside(x, y)) {
        std::vector<ciUIWidget *>::iterator it = widgets.begin();
        std::vector<ciUIWidget *>::iterator eit = widgets.end();
        for(; it != eit; ++it) {
            if((*it)->isHit(x, y)) {
                return (*it);
            }
        }
        return nullptr;
    }
    else {
        return nullptr;
    }
}


void ciUICanvas::stateChange()
{
    switch (state) {
        case CI_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
        }
            break;
        case CI_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            if(enable_highlight_outline)
            {
                draw_outline_highlight = true;
            }
        }
            break;
        case CI_UI_STATE_DOWN:
        {
            if(enable_highlight_fill)
            {
                draw_fill_highlight = true;
            }
            draw_outline_highlight = false;
        }
            break;
        case CI_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
        }
            break;
            
        default:
            break;
    }
}

void ciUICanvas::autoSizeToFitWidgets()
{
    float maxWidth = 0;
    float maxHeight = 0;
    
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it) {
        if((*it)->isVisible()) {
            ciUIRectangle* wr = (*it)->getRect();
            ciUIRectangle* wrp = (*it)->getPaddingRect();
            float widgetwidth = wr->getX()+wrp->getWidth() - rect->getX();
            float widgetheight = wr->getY()+wrp->getHeight() - rect->getY();
            
            float widgetpaddingwidth = wrp->getX()+wrp->getWidth() - rect->getX();
            float widgetpaddingheight = wrp->getY()+wrp->getHeight() - rect->getY();
            
            
            if(widgetwidth > maxWidth)
            {
                maxWidth = widgetwidth;
            }
            else if(widgetpaddingwidth > maxWidth)
            {
                maxWidth = widgetpaddingwidth;
            }
            
            if(widgetheight > maxHeight)
            {
                maxHeight = widgetheight;
            }
            else if(widgetpaddingheight > maxHeight)
            {
                maxHeight = widgetpaddingheight;
            }
        }
    }
    setDimensions(maxWidth, maxHeight);
}

void ciUICanvas::alignWidgetsVertically(ciUIWidget *widgetToBeAligned, ciUIWidget *widgetToBeingAlignedTo)
{
    float yRef = widgetToBeingAlignedTo->getRect()->getY();
    float hRef = widgetToBeingAlignedTo->getRect()->getHeight();
    
    float yWgt = widgetToBeAligned->getRect()->getY();
    float hWgt = widgetToBeAligned->getRect()->getHeight();
    
    float y = (hRef - hWgt)*0.5;
    
    widgetToBeAligned->getRect()->setY(yWgt+y);
}
    
void ciUICanvas::centerWidgetsOnCanvas(bool centerHorizontally, bool centerVertically)
{
    float xMin = 0;
    float yMin = 0;
    
    float xMax = 0;
    float yMax = 0;
    
    float w = 0;
    float h = 0;
    
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it) {
        //            if((*it)->isVisible())
        //            {
        ciUIRectangle* wr = (*it)->getRect();
        if(wr->x < xMin) {
            xMin = wr->x;
        }
        if((wr->x + wr->getWidth()) > xMax) {
            xMax = (wr->x + wr->getWidth());
        }
        if(wr->y < yMin) {
            yMin = wr->y;
        }
        if((wr->y + wr->getHeight()) > yMax) {
            yMax = (wr->y + wr->getHeight());
        }
        //            }
    }
    
    w = xMax - xMin;
    h = yMax - yMin;
    
    float moveDeltaX = rect->getHalfWidth() - w*.5;
    float moveDeltaY = rect->getHalfHeight() - h*.5;
    
    it = widgets.begin();
    for(; it != eit; ++it) {
        if((*it)->isVisible() && !((*it)->isEmbedded())) {
            ciUIRectangle* wr = (*it)->getRect();
            if(centerHorizontally) wr->x += moveDeltaX-padding;
            if(centerVertically) wr->y += moveDeltaY-padding;
        }
    }
}

void ciUICanvas::centerWidgetsHorizontallyOnCanvas() {
    centerWidgetsOnCanvas(true, false);
}

void ciUICanvas::centerWidgetsVerticallyOnCanvas() {
    centerWidgetsOnCanvas(false, true);
}

void ciUICanvas::centerWidgets() {
    centerWidgetsOnCanvas(true, true);
}

void ciUICanvas::addModalWidget(ciUIWidget *widget) {
    widgetsAreModal[widget->getName()] = widget;
}

void ciUICanvas::removeModalWidget(ciUIWidget *widget) {
    std::map<std::string, ciUIWidget*>::iterator it;
    it = widgetsAreModal.find(widget->getName());
    if(it != widgetsAreModal.end()) {
        widgetsAreModal.erase(it);
    }
}

void ciUICanvas::removeWidgets() {
    std::vector<ciUIWidget *>::iterator it = widgets.begin();
    std::vector<ciUIWidget *>::iterator eit = widgets.end();
    for(; it != eit; ++it) {
        ciUIWidget *w = (*it);
        delete w;
    }
    clearWidgets();
    resetPlacer();
}

// To be called before destructor if "widgets" are pointing to stack-based widgets.
void ciUICanvas::clearWidgets() {
    widgets.clear();
    widgets_map.clear();
    widgetsAreModal.clear();
    widgetsWithState.clear();
    lastAddeds.clear();
}

void ciUICanvas::removeWidget(ciUIWidget *widget)
{
    if(widget == nullptr)
    {
        return;
    }
    
    //MODAL WIDGETS
    {
        if(widget->isModal())
        {
            std::map<std::string, ciUIWidget*>::iterator it = widgetsAreModal.begin();
            std::map<std::string, ciUIWidget*>::iterator eit = widgetsAreModal.end();
            for(; it != eit; ++it)
            {
                if(it->second == widget)
                {
                    widgetsAreModal.erase(it);
                    break;
                }
            }
        }
    }

    //WIDGET MAP
    {
        std::multimap<std::string, ciUIWidget*>::iterator it = widgets_map.begin();
        std::multimap<std::string, ciUIWidget*>::iterator eit = widgets_map.end();
        for(; it != eit; ++it)
        {
            if(it->second == widget)
            {
                widgets_map.erase(it);
                break;
            }
        }
    }
    
    widgetsWithState.erase(std::remove(widgetsWithState.begin(), widgetsWithState.end(), widget), widgetsWithState.end());
    widgets.erase(std::remove(widgets.begin(), widgets.end(), widget), widgets.end());
    
    ciUIWidget * labelignore = nullptr;
    if(widget->hasLabel())
    {
        ciUIWidgetWithLabel *wwl = (ciUIWidgetWithLabel *) widget;
        ciUILabel *label = wwl->getLabelWidget();
        labelignore = label;
        removeWidget(label);
    }
    
    for(int i = 0; i < widget->getEmbeddedWidgetsSize(); ++i)
    {
        ciUIWidget *w = widget->getEmbeddedWidget(i);
        if(w != labelignore)
        {
            removeWidget(w);
        }
    }
    widget->clearEmbeddedWidgets();
    
    lastAddeds.erase( std::remove( lastAddeds.begin(), lastAddeds.end(), widget ), lastAddeds.end() );
    delete widget;
}

void ciUICanvas::addWidget(ciUIWidget *widget) {
    if(widget->hasState()) {
       widgetsWithState.push_back(widget);
    }
    widget->setPadding(padding);
    
    for(int i = 0; i < widget->getEmbeddedWidgetsSize(); ++i) {
        ciUIWidget *child = widget->getEmbeddedWidget(i);
        this->addWidget(child);
        child->setParent(widget);
        child->setRectParent(widget->getRect());
    }
    
    if(widget->getKind() == CI_UI_WIDGET_LABEL) {
        ciUILabel *label = (ciUILabel *) widget;
        setLabelFont(label);
        setWidgetColor(label);
    }
    
    setWidgetDrawingProperties(widget);
    setWidgetColor(widget);
    widget->setParent(this);
    widget->setRectParent(this->rect);
    pushbackWidget(widget);
}

ciUIWidget* ciUICanvas::addWidgetPosition(ciUIWidget *widget, ciUIWidgetPosition position, ciUIWidgetAlignment align, bool reAdd)
{
    if(!reAdd) addWidget(widget);
    ciUIRectangle *widgetRect = widget->getRect();
    ciUIWidget* lastAdded = lastAddeds.empty() ? nullptr : lastAddeds.back();
    if(lastAdded != nullptr) {
        ciUIRectangle *lastPaddedRect = lastAdded->getPaddingRect();
        switch(position) {
            case CI_UI_WIDGET_POSITION_DOWN:
            {
                widgetRect->y = lastPaddedRect->getY()+lastPaddedRect->getHeight()-rect->getY()+widgetSpacing;
            }
                break;
            case CI_UI_WIDGET_POSITION_UP:
            {
                ciUIRectangle *widgetPaddedRect = widget->getPaddingRect();
                widgetRect->y = lastPaddedRect->getY()-widgetPaddedRect->getHeight()-rect->getY();
                break;
            }
            case CI_UI_WIDGET_POSITION_RIGHT:
            {
                ciUIRectangle *lastRect = lastAdded->getRect();
                widgetRect->x = lastPaddedRect->getX()+lastPaddedRect->getWidth()-rect->getX()+widgetSpacing;
                
                widgetRect->y = lastRect->getY()-rect->getY();
                break;
            }
            case CI_UI_WIDGET_POSITION_LEFT:
            {
                ciUIRectangle *lastRect = lastAdded->getRect();
                ciUIRectangle *widgetPaddedRect = widget->getPaddingRect();
                widgetRect->x = lastPaddedRect->getX()-widgetPaddedRect->getWidth()-rect->getX();
                widgetRect->y = lastRect->getY()-rect->getY();
            }
                break;
        }
    }
    else
    {
        widgetRect->y = widgetSpacing;
        if (position == CI_UI_WIDGET_POSITION_LEFT || position == CI_UI_WIDGET_POSITION_RIGHT) {
            widgetRect->x = widgetSpacing;
        }
        
    }
    
    switch(align) {
        case CI_UI_ALIGN_LEFT:
            widgetRect->x = widgetSpacing;
            break;
        case CI_UI_ALIGN_FREE:
            
            break;
        case CI_UI_ALIGN_CENTER:   //Experimental
            widgetRect->x = (rect->getWidth()-widgetRect->getWidth())*0.5;
            break;
        case CI_UI_ALIGN_RIGHT:
            widgetRect->x = rect->getWidth()-widgetRect->getWidth()-widgetSpacing;
            break;
        case CI_UI_ALIGN_TOP:
            widgetRect->y = widgetSpacing;
            break;
        case CI_UI_ALIGN_BOTTOM:
            widgetRect->y = rect->getHeight()-widgetRect->getHeight()-widgetSpacing;
            break;
    }
    
    if(widget->getRect()->getHeight() != 0 || widget->getRect()->getWidth() != 0) {
        lastAddeds.push_back( widget );
    }
    
    return widget;
}

ciUIWidget* ciUICanvas::addWidgetDown(ciUIWidget *widget, ciUIWidgetAlignment align, bool reAdd) {
    return addWidgetPosition(widget, CI_UI_WIDGET_POSITION_DOWN, align, reAdd);
}

ciUIWidget* ciUICanvas::addWidgetUp(ciUIWidget *widget, ciUIWidgetAlignment align, bool reAdd) {
    return addWidgetPosition(widget, CI_UI_WIDGET_POSITION_UP, align, reAdd);
}

ciUIWidget* ciUICanvas::addWidgetRight(ciUIWidget *widget, ciUIWidgetAlignment align, bool reAdd) {
    return addWidgetPosition(widget, CI_UI_WIDGET_POSITION_RIGHT, align, reAdd);
}

ciUIWidget* ciUICanvas::addWidgetLeft(ciUIWidget *widget, ciUIWidgetAlignment align, bool reAdd) {
    return addWidgetPosition(widget, CI_UI_WIDGET_POSITION_LEFT, align, reAdd);
}

ciUIWidget* ciUICanvas::addWidgetSouthOf(ciUIWidget *widget, const std::string &referenceName, bool reAdd) {
    if(!reAdd) addWidget(widget);
    ciUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != nullptr) {
        ciUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect();
        ciUIRectangle *referenceRect = referenceWidget->getRect();
        ciUIRectangle *widgetRect = widget->getRect();
        
        widgetRect->y = referencePaddedRect->getY()+referencePaddedRect->getHeight()-rect->getY()+widgetSpacing;
        widgetRect->x = referenceRect->getX()-rect->getX();
    }
    else {
        ciUIRectangle *widgetRect = widget->getRect();
        widgetRect->y = widgetSpacing;
    }
    lastAddeds.push_back( widget );
    return widget;
}

ciUIWidget* ciUICanvas::addWidgetNorthOf(ciUIWidget *widget, const std::string &referenceName, bool reAdd) {
    if(!reAdd) addWidget(widget);
    ciUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != nullptr) {
        ciUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect();
        ciUIRectangle *referenceRect = referenceWidget->getRect();
        ciUIRectangle *widgetRect = widget->getRect();
        ciUIRectangle *widgetPaddedRect = widget->getPaddingRect();
        
        widgetRect->y = referencePaddedRect->getY()-widgetPaddedRect->getHeight()-rect->getY();
        widgetRect->x = referenceRect->getX()-rect->getX();
    }
    else {
        ciUIRectangle *widgetRect = widget->getRect();
        widgetRect->y = widgetSpacing;
    }
    lastAddeds.push_back( widget );
    return widget;
}

ciUIWidget* ciUICanvas::addWidgetWestOf(ciUIWidget *widget, const std::string &referenceName, bool reAdd) {
    if(!reAdd) addWidget(widget);
    ciUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != nullptr) {
        ciUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect();
        ciUIRectangle *referenceRect = referenceWidget->getRect();
        ciUIRectangle *widgetRect = widget->getRect();
        ciUIRectangle *widgetPaddedRect = widget->getPaddingRect();
        
        widgetRect->y = referenceRect->getY()-rect->getY();
        widgetRect->x = referencePaddedRect->getX()-rect->getX()-widgetPaddedRect->getWidth();
    }
    else {
        ciUIRectangle *currentRect = widget->getRect();
        currentRect->y = widgetSpacing;
    }
    lastAddeds.push_back( widget );
    return widget;
}

ciUIWidget* ciUICanvas::addWidgetEastOf(ciUIWidget *widget, const std::string &referenceName, bool reAdd) {
    if(!reAdd) addWidget(widget);
    ciUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != nullptr) {
        ciUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect();
        ciUIRectangle *referenceRect = referenceWidget->getRect();
        ciUIRectangle *widgetRect = widget->getRect();
        widgetRect->y = referenceRect->getY()-rect->getY();
        widgetRect->x = referencePaddedRect->getX()-rect->getX()+referencePaddedRect->getWidth()+widgetSpacing;
    }
    else {
        ciUIRectangle *currentRect = widget->getRect();
        currentRect->y = widgetSpacing;
    }
    lastAddeds.push_back( widget );
    return widget;
}

ciUISpacer* ciUICanvas::addSpacer(float h) {
    if(h != globalSpacerHeight) {
        h = globalSpacerHeight;
    }
    ciUISpacer* widget = new ciUISpacer(rect->getWidth()-widgetSpacing*2, h);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISpacer* ciUICanvas::addSpacer(const std::string &name, float h) {
    if(h != globalSpacerHeight) {
        h = globalSpacerHeight;
    }
    ciUISpacer* widget = new ciUISpacer(rect->getWidth()-widgetSpacing*2, h, name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISpacer* ciUICanvas::addSpacer(float w, float h) {
    ciUISpacer* widget = new ciUISpacer(w, h);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISpacer* ciUICanvas::addSpacer(float w, float h, const std::string &name) {
    ciUISpacer* widget = new ciUISpacer(w, h, name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabel* ciUICanvas::addLabel(const std::string &name, int size) {
    ciUILabel* widget = new ciUILabel(name, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabel* ciUICanvas::addLabel(const std::string &name, const std::string &label, int size) {
    ciUILabel* widget = new ciUILabel(name, label, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIFPS* ciUICanvas::addFPS(int size) {
    ciUIFPS* widget = new ciUIFPS(size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISlider* ciUICanvas::addSlider(const std::string &_name, float _min, float _max, float _value) {
    ciUISlider* widget = new ciUISlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISlider* ciUICanvas::addSlider(const std::string &_name, float _min, float _max, float _value, float w, float h, float x, float y) {
    ciUISlider* widget = new ciUISlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISlider* ciUICanvas::addSlider(const std::string &_name, float _min, float _max, float *_value) {
    ciUISlider* widget = new ciUISlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISlider* ciUICanvas::addSlider(const std::string &_name, float _min, float _max, float *_value, float w, float h, float x, float y) {
    ciUISlider* widget = new ciUISlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIIntSlider* ciUICanvas::addIntSlider(const std::string &_name, int _min, int _max, int _value) {
    ciUIIntSlider* widget = new ciUIIntSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);    
    return widget;
}

ciUIIntSlider* ciUICanvas::addIntSlider(const std::string &_name, int _min, int _max, int _value, float w, float h, float x, float y) {
    ciUIIntSlider* widget = new ciUIIntSlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIIntSlider* ciUICanvas::addIntSlider(const std::string &_name, int _min, int _max, int *_value) {
    ciUIIntSlider* widget = new ciUIIntSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIIntSlider* ciUICanvas::addIntSlider(const std::string &_name, int _min, int _max, int *_value, float w, float h, float x, float y) {
    ciUIIntSlider* widget = new ciUIIntSlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIDoubleSlider* ciUICanvas::addDoubleSlider(const std::string &_name, double _min, double _max, double _value) {
    ciUIDoubleSlider* widget = new ciUIDoubleSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIDoubleSlider* ciUICanvas::addDoubleSlider(const std::string &_name, double _min, double _max, double _value, float w, float h, float x, float y) {
    ciUIDoubleSlider* widget = new ciUIDoubleSlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIDoubleSlider* ciUICanvas::addDoubleSlider(const std::string &_name, double _min, double _max, double *_value) {
    ciUIDoubleSlider* widget = new ciUIDoubleSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIDoubleSlider* ciUICanvas::addDoubleSlider(const std::string &_name, double _min, double _max, double *_value, float w, float h, float x, float y) {
    ciUIDoubleSlider* widget = new ciUIDoubleSlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRotarySlider* ciUICanvas::addRotarySlider(const std::string &_name, float _min, float _max, float _value, int _size) {
    ciUIRotarySlider* widget = new ciUIRotarySlider(rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRotarySlider* ciUICanvas::addRotarySlider(const std::string &_name, float _min, float _max, float _value, float w, float x, float y, int _size) {
    ciUIRotarySlider* widget = new ciUIRotarySlider(x, y, w, _min, _max, _value, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRotarySlider* ciUICanvas::addRotarySlider(const std::string &_name, float _min, float _max, float *_value, int _size) {
    ciUIRotarySlider* widget = new ciUIRotarySlider(rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRotarySlider* ciUICanvas::addRotarySlider(const std::string &_name, float _min, float _max, float *_value, float w, float x, float y, int _size) {
    ciUIRotarySlider* widget = new ciUIRotarySlider(x, y, w, _min, _max, _value, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageSlider* ciUICanvas::addImageSlider(const std::string &_name, const std::string &_pathURL, float _min, float _max, float _value) {
    ciUIImageSlider* widget = new ciUIImageSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _pathURL, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageSlider* ciUICanvas::addImageSlider(const std::string &_name, const std::string &_pathURL, float _min, float _max, float _value, float w, float h, float x, float y) {
    ciUIImageSlider* widget = new ciUIImageSlider(x, y, w, h, _min, _max, _value, _pathURL, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageSlider* ciUICanvas::addImageSlider(const std::string &_name, const std::string &_pathURL, float _min, float _max, float *_value) {
    ciUIImageSlider* widget = new ciUIImageSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _pathURL, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageSlider* ciUICanvas::addImageSlider(const std::string &_name, const std::string &_pathURL, float _min, float _max, float *_value, float w, float h, float x, float y) {
    ciUIImageSlider* widget = new ciUIImageSlider(x, y, w, h, _min, _max, _value, _pathURL, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUINumberDialer* ciUICanvas::addNumberDialer(const std::string &_name, float _min, float _max, float _value, int _precision) {
    ciUINumberDialer* widget = new ciUINumberDialer(_min, _max, _value, _precision, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUINumberDialer* ciUICanvas::addNumberDialer(const std::string &_name, float _min, float _max, float *_value, int _precision) {
    ciUINumberDialer* widget = new ciUINumberDialer(_min, _max, _value, _precision, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMinimalSlider* ciUICanvas::addMinimalSlider(const std::string &_name, float _min, float _max, float _value, int size) {
    ciUIMinimalSlider* widget = new ciUIMinimalSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMinimalSlider* ciUICanvas::addMinimalSlider(const std::string &_name, float _min, float _max, float _value, float w, float h, float x, float y, int size)
{
    if(w < 0)
    {
        w = rect->getWidth()-widgetSpacing*2;
    }
    if(h < 0)
    {
        h = globalSliderHeight;
    }
    ciUIMinimalSlider* widget = new ciUIMinimalSlider(_name, _min, _max, _value, w, h, x, y, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMinimalSlider* ciUICanvas::addMinimalSlider(const std::string &_name, float _min, float _max, float *_value, int size) {
    ciUIMinimalSlider* widget = new ciUIMinimalSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMinimalSlider* ciUICanvas::addMinimalSlider(const std::string &_name, float _min, float _max, float *_value, float w, float h, float x, float y, int size)
{
    if(w < 0)
    {
        w = rect->getWidth()-widgetSpacing*2;
    }
    if(h < 0)
    {
        h = globalSliderHeight;
    }
    ciUIMinimalSlider* widget = new ciUIMinimalSlider(_name, _min, _max, _value, w, h, x, y, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRangeSlider* ciUICanvas::addRangeSlider(const std::string &_name, float _min, float _max, float _valuelow, float _valuehigh) {
    ciUIRangeSlider* widget = new ciUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRangeSlider* ciUICanvas::addRangeSlider(const std::string &_name, float _min, float _max, float _valuelow, float _valuehigh,
                                 float w, float h, float x, float y) {
    ciUIRangeSlider* widget = new ciUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRangeSlider* ciUICanvas::addRangeSlider(const std::string &_name, float _min, float _max, float *_valuelow, float *_valuehigh) {
    ciUIRangeSlider* widget = new ciUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRangeSlider* ciUICanvas::addRangeSlider(const std::string &_name, float _min, float _max, float *_valuelow, float *_valuehigh,
                                 float w, float h, float x, float y) {
    ciUIRangeSlider* widget = new ciUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIFPSSlider* ciUICanvas::addFPSSlider(const std::string &_name, float _max) {
    ciUIFPSSlider* widget = new ciUIFPSSlider(_name, rect->getWidth()-widgetSpacing*2, globalSliderHeight, _max, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIFPSSlider* ciUICanvas::addFPSSlider(const std::string &_name, float w, float h, float _max, float x, float y) {
    ciUIFPSSlider* widget = new ciUIFPSSlider(_name, w, h, _max, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRadio* ciUICanvas::addRadio(const std::string &_name, const std::vector<std::string> &names, int _orientation, int _size) {
    ciUIRadio* widget = new ciUIRadio(_name, names, _orientation, globalButtonDimension, globalButtonDimension, 0, 0, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIRadio* ciUICanvas::addRadio(const std::string &_name, const std::vector<std::string> &names, int _orientation, float w, float h, float x, float y, int _size) {
    ciUIRadio* widget = new ciUIRadio(_name, names, _orientation, w, h, x, y, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIButton* ciUICanvas::addButton(const std::string &_name, bool _value) {
    ciUIButton* widget = new ciUIButton(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIButton* ciUICanvas::addButton(const std::string &_name, bool _value, float w, float h, float x, float y) {
    ciUIButton* widget = new ciUIButton(_name, _value, w, h, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIButton* ciUICanvas::addButton(const std::string &_name, bool *_value) {
    ciUIButton* widget = new ciUIButton(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIButton* ciUICanvas::addButton(const std::string &_name, bool *_value, float w, float h, float x, float y) {
    ciUIButton* widget = new ciUIButton(_name, _value, w, h, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIToggle* ciUICanvas::addToggle(const std::string &_name, bool _value) {
    ciUIToggle* widget = new ciUIToggle(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIToggle* ciUICanvas::addToggle(const std::string &_name, bool _value, float w, float h, float x, float y) {
    ciUIToggle* widget = new ciUIToggle(_name, _value, w, h, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIToggle* ciUICanvas::addToggle(const std::string &_name, bool *_value) {
    ciUIToggle* widget = new ciUIToggle(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIToggle* ciUICanvas::addToggle(const std::string &_name, bool *_value, float w, float h, float x, float y) {
    ciUIToggle* widget = new ciUIToggle(_name, _value, w, h, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIToggleMatrix* ciUICanvas::addToggleMatrix(const std::string &_name, int _rows, int _cols) {
    float dim = globalButtonDimension;
    float width = rect->getWidth()-widgetSpacing*2;
    if(_cols*dim+_cols*padding > width)
    {
        dim = (width-(_cols-1)*padding)/_cols;
    }
    ciUIToggleMatrix* widget = new ciUIToggleMatrix(dim, dim, _rows, _cols, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIToggleMatrix* ciUICanvas::addToggleMatrix(const std::string &_name, int _rows, int _cols, float w, float h) {
    ciUIToggleMatrix* widget = new ciUIToggleMatrix(w, h, _rows, _cols, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUI2DPad* ciUICanvas::add2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f _value) {
    float dim = rect->getWidth()-widgetSpacing*2;
    ciUI2DPad* widget = new ciUI2DPad(_name, _rangeX, _rangeY, _value, dim, dim, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}


ciUI2DPad* ciUICanvas::add2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f _value, float w, float h, float x, float y) {
    ciUI2DPad* widget = new ciUI2DPad(_name, _rangeX, _rangeY, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUI2DPad* ciUICanvas::add2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f *_value) {
    float dim = rect->getWidth()-widgetSpacing*2;
    ciUI2DPad* widget = new ciUI2DPad(_name, _rangeX, _rangeY, _value, dim, dim, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUI2DPad* ciUICanvas::add2DPad(const std::string &_name, ciUIVec3f _rangeX, ciUIVec3f _rangeY, ciUIVec3f *_value, float w, float h, float x, float y) {
    ciUI2DPad* widget = new ciUI2DPad(_name, _rangeX, _rangeY, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUITextInput* ciUICanvas::addTextInput(const std::string &_name, const std::string &_textstring, int _size) {
    float h = 0;
    float x = 0;
    float y = 0;
    if(_size == -1) {
        _size = widgetFontSize;
    }
    ciUITextInput* widget = new ciUITextInput(_name, _textstring, rect->getWidth()-widgetSpacing*2, h, x, y, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUITextInput* ciUICanvas::addTextInput(const std::string &_name, const std::string &_textstring, float w, float h, float x, float y, int _size) {
    if(_size == -1) {
        _size = widgetFontSize;
    }
    ciUITextInput* widget = new ciUITextInput(_name, _textstring, w, h, x, y, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabelToggle* ciUICanvas::addLabelToggle(const std::string &_name, bool _value, bool _justifyLeft) {
    ciUILabelToggle* widget = new ciUILabelToggle(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabelToggle* ciUICanvas::addLabelToggle(const std::string &_name, bool _value, float w, float h, float x, float y, bool _justifyLeft) {
    if(h == 0) {
        h = globalButtonDimension;
    }
    ciUILabelToggle* widget = new ciUILabelToggle(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabelToggle* ciUICanvas::addLabelToggle(const std::string &_name, bool *_value, bool _justifyLeft) {
    ciUILabelToggle* widget = new ciUILabelToggle(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabelToggle* ciUICanvas::addLabelToggle(const std::string &_name, bool *_value, float w, float h, float x, float y, bool _justifyLeft) {
    ciUILabelToggle* widget = new ciUILabelToggle(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabelButton* ciUICanvas::addLabelButton(const std::string &_name, bool _value, bool _justifyLeft) {
    ciUILabelButton* widget = new ciUILabelButton(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabelButton* ciUICanvas::addLabelButton(const std::string &_name, bool _value, float w, float h, float x, float y, bool _justifyLeft) {
    if(h == 0) {
        h = globalButtonDimension;
    }
    ciUILabelButton* widget = new ciUILabelButton(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabelButton* ciUICanvas::addLabelButton(const std::string &_name, bool *_value, bool _justifyLeft) {
    ciUILabelButton* widget = new ciUILabelButton(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUILabelButton* ciUICanvas::addLabelButton(const std::string &_name, bool *_value, float w, float h, float x, float y, bool _justifyLeft) {
    if(h == 0) {
        h = globalButtonDimension;
    }
    ciUILabelButton* widget = new ciUILabelButton(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIDropDownList* ciUICanvas::addDropDownList(const std::string &_name, const std::vector<std::string> &items) {
    ciUIDropDownList* widget = new ciUIDropDownList(_name, items, rect->getWidth()-widgetSpacing*2, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIDropDownList* ciUICanvas::addDropDownList(const std::string &_name, const std::vector<std::string> &items, float w, float x, float y) {
    ciUIDropDownList* widget = new ciUIDropDownList(_name, items, w, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIWaveform* ciUICanvas::addWaveform(const std::string &_name, float *_buffer, int _bufferSize, float _min, float _max, float _h) {
    if(_h == -1)
    {
        _h = getGlobalGraphHeight();
    }
    ciUIWaveform* widget = new ciUIWaveform(rect->getWidth()-widgetSpacing*2, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIWaveform* ciUICanvas::addWaveform(const std::string &_name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h) {
    ciUIWaveform* widget = new ciUIWaveform(_w, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISpectrum* ciUICanvas::addSpectrum(const std::string &_name, float *_buffer, int _bufferSize, float _min, float _max, float _h) {
    if(_h != globalGraphHeight) {
        _h = globalGraphHeight;
    }
    ciUISpectrum* widget = new ciUISpectrum(rect->getWidth()-widgetSpacing*2, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISpectrum* ciUICanvas::addSpectrum(const std::string &_name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h) {
    ciUISpectrum* widget = new ciUISpectrum(_w, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMovingGraph* ciUICanvas::addMovingGraph(const std::string &_name, const std::vector<float> &_buffer, int _bufferSize, float _min, float _max, float _h) {
    if(_h != globalGraphHeight)
    {
        _h = globalGraphHeight;
    }
    ciUIMovingGraph* widget = new ciUIMovingGraph(rect->getWidth()-widgetSpacing*2, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMovingGraph* ciUICanvas::addMovingGraph(const std::string &_name, const std::vector<float> &_buffer, int _bufferSize, float _min, float _max, float _w, float _h) {
    ciUIMovingGraph* widget = new ciUIMovingGraph(_w, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImage* ciUICanvas::addImage(const std::string &_name, const ci::SurfaceRef &_image, float _w, float _h, bool _showLabel) {
    ciUIImage* widget = new ciUIImage(_w, _h, _image, _name, _showLabel);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImage* ciUICanvas::addImage(const std::string &_name, const ci::SurfaceRef &_image, bool _showLabel) {
    float _w = rect->getWidth()-widgetSpacing*2;
    float _h = _w*(float)_image->getHeight()/(float)_image->getWidth();
    ciUIImage* widget = new ciUIImage(_w, _h, _image, _name, _showLabel);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIBaseDraws* ciUICanvas::addBaseDraws(const std::string &_name, const ci::SurfaceRef &_base, float _w, float _h, bool _showLabel) {
    ciUIBaseDraws* widget = new ciUIBaseDraws(_w, _h, _base, _name, _showLabel);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIBaseDraws* ciUICanvas::addBaseDraws(const std::string &_name, const ci::SurfaceRef &_base, bool _showLabel) {
    float _w = rect->getWidth()-widgetSpacing*2;
    float _h = _w*(float)_base->getHeight()/(float)_base->getWidth();
    ciUIBaseDraws* widget = new ciUIBaseDraws(_w, _h, _base, _name, _showLabel);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}
ciUIImageSampler* ciUICanvas::addImageSampler(const std::string &_name, const ci::SurfaceRef &_image, float _w, float _h) {
    ciUIImageSampler* widget = new ciUIImageSampler(_w, _h, _image, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageSampler* ciUICanvas::addImageSampler(const std::string &_name, const ci::SurfaceRef &_image) {
    float _w = rect->getWidth()-widgetSpacing*2;
    float _h = _w*(float)_image->getHeight()/(float)_image->getWidth();
    ciUIImageSampler* widget = new ciUIImageSampler(_w, _h, _image, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIBiLabelSlider* ciUICanvas::addBiLabelSlider(const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, float _min, float _max, float _value, int _size) {
    ciUIBiLabelSlider* widget = new ciUIBiLabelSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIBiLabelSlider* ciUICanvas::addBiLabelSlider(const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, float _min, float _max, float *_value, int _size) {
    ciUIBiLabelSlider* widget = new ciUIBiLabelSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIBiLabelSlider* ciUICanvas::addBiLabelSlider(const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, float _min, float _max, float _value, float _w, float _h, int _size) {
    ciUIBiLabelSlider* widget = new ciUIBiLabelSlider(_w, _h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIBiLabelSlider* ciUICanvas::addBiLabelSlider(const std::string &_name, const std::string &_leftLabel, const std::string &_rightLabel, float _min, float _max, float *_value, float _w, float _h, int _size) {
    ciUIBiLabelSlider* widget = new ciUIBiLabelSlider(_w, _h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUICircleSlider* ciUICanvas::addCircleSlider(const std::string &_name, float _min, float _max, float _value) {
    ciUICircleSlider* widget = new ciUICircleSlider(rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUICircleSlider* ciUICanvas::addCircleSlider(const std::string &_name, float _min, float _max, float _value, float w, float x, float y) {
    ciUICircleSlider* widget = new ciUICircleSlider(x, y, w, _min, _max, _value, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUICircleSlider* ciUICanvas::addCircleSlider(const std::string &_name, float _min, float _max, float *_value) {
    ciUICircleSlider* widget = new ciUICircleSlider(0, 0, rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUICircleSlider* ciUICanvas::addCircleSlider(const std::string &_name, float _min, float _max, float *_value, float w, float x, float y) {
    ciUICircleSlider* widget = new ciUICircleSlider(x, y, w, _min, _max, _value, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIValuePlotter* ciUICanvas::addValuePlotter(const std::string &_name, int _bufferSize, float _min, float _max, float *_value, float _h) {
    if(_h != globalGraphHeight)
    {
        _h = globalGraphHeight;
    }
    ciUIValuePlotter* widget = new ciUIValuePlotter(rect->getWidth()-widgetSpacing*2, _h, _bufferSize, _min, _max, _value, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIValuePlotter* ciUICanvas::addValuePlotter(const std::string &_name, int _bufferSize, float _min, float _max, float *_value, float _w, float _h) {
    ciUIValuePlotter* widget = new ciUIValuePlotter(_w, _h, _bufferSize, _min, _max, _value, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}


ciUI2DGraph* ciUICanvas::add2DGraph(const std::string &_name, ciUIVec2f _rangeX, ciUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues) {
    ciUI2DGraph* widget = new ciUI2DGraph(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, rect->getWidth()-widgetSpacing*2, rect->getWidth()-widgetSpacing*2);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUI2DGraph* ciUICanvas::add2DGraph(const std::string &_name, ciUIVec2f _rangeX, ciUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues, float _w, float _h, float _x, float _y) {
    ciUI2DGraph* widget = new ciUI2DGraph(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, _w, _h, _x, _y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageToggle* ciUICanvas::addImageToggle(const std::string &_name, const std::string &_path, bool *_value, float w, float h, float x, float y, int _size) {
    ciUIImageToggle *widget = new ciUIImageToggle(x, y, w, h, _value, _path, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageToggle* ciUICanvas::addImageToggle(const std::string &_name, const std::string &_path, bool _value, float w, float h, float x, float y, int _size) {
    ciUIImageToggle *widget = new ciUIImageToggle(x, y, w, h, _value, _path, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageToggle* ciUICanvas::addImageToggle(const std::string &_name, const std::string &_path, bool *_value, int _size) {
    ciUIImageToggle *widget = new ciUIImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageToggle* ciUICanvas::addImageToggle(const std::string &_name, const std::string &_path, bool _value, int _size) {
    ciUIImageToggle *widget = new ciUIImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageButton* ciUICanvas::addImageButton(const std::string &_name, const std::string &_path, bool *_value, float w, float h, float x, float y, int _size) {
    ciUIImageButton *widget = new ciUIImageButton(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageButton* ciUICanvas::addImageButton(const std::string &_name, const std::string &_path, bool _value, float w, float h, float x, float y, int _size) {
    ciUIImageButton *widget = new ciUIImageButton(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageButton* ciUICanvas::addImageButton(const std::string &_name, const std::string &_path, bool *_value, int _size) {
    ciUIImageButton *widget = new ciUIImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIImageButton* ciUICanvas::addImageButton(const std::string &_name, const std::string &_path, bool _value, int _size) {
    ciUIImageButton *widget = new ciUIImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMultiImageButton* ciUICanvas::addMultiImageButton(const std::string &_name, const std::string &_path, bool *_value, float w, float h, float x, float y, int _size) {
    ciUIMultiImageButton *widget = new ciUIMultiImageButton(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMultiImageButton* ciUICanvas::addMultiImageButton(const std::string &_name, const std::string &_path, bool _value, float w, float h, float x, float y, int _size) {
    ciUIMultiImageButton *widget = new ciUIMultiImageButton(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMultiImageButton* ciUICanvas::addMultiImageButton(const std::string &_name, const std::string &_path, bool *_value, int _size) {
    ciUIMultiImageButton *widget = new ciUIMultiImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMultiImageButton* ciUICanvas::addMultiImageButton(const std::string &_name, const std::string &_path, bool _value, int _size) {
    ciUIMultiImageButton *widget = new ciUIMultiImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

//
ciUIMultiImageToggle* ciUICanvas::addMultiImageToggle(const std::string &_name, const std::string &_path, bool *_value, float w, float h, float x, float y, int _size) {
    ciUIMultiImageToggle *widget = new ciUIMultiImageToggle(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMultiImageToggle* ciUICanvas::addMultiImageToggle(const std::string &_name, const std::string &_path, bool _value, float w, float h, float x, float y, int _size) {
    ciUIMultiImageToggle *widget = new ciUIMultiImageToggle(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMultiImageToggle* ciUICanvas::addMultiImageToggle(const std::string &_name, const std::string &_path, bool *_value, int _size) {
    ciUIMultiImageToggle *widget = new ciUIMultiImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUIMultiImageToggle* ciUICanvas::addMultiImageToggle(const std::string &_name, const std::string &_path, bool _value, int _size) {
    ciUIMultiImageToggle *widget = new ciUIMultiImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}
//

ciUITextArea* ciUICanvas::addTextArea(const std::string &_name, const std::string &_textstring, int _size) {
    ciUITextArea *widget = new ciUITextArea(_name, _textstring, rect->getWidth()-widgetSpacing*2, 0, 0, 0, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ciUISortableList* ciUICanvas::addSortableList(const std::string &_name, const std::vector<std::string> &_items, int _size, int _itemHeight) {
    if(_size == -1) {
        _size = widgetFontSize;
    }    
    ciUISortableList *widget = new ciUISortableList(_name, _items, rect->getWidth()-widgetSpacing*2, 0, 0, 0, _size, _itemHeight);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

void ciUICanvas::resetPlacer() {
    lastAddeds.clear();
}

void ciUICanvas::setPlacer(ciUIWidget *referenceWidget) {
    if (!referenceWidget) {
        return;
    }
    std::remove(lastAddeds.begin(),lastAddeds.end(),referenceWidget);
    lastAddeds.push_back(referenceWidget);
}

void ciUICanvas::setLabelFont(ciUILabel *label) {
    switch(label->getSize()) {
        case CI_UI_FONT_LARGE:
            label->setFont(font_large);
            break;
        case CI_UI_FONT_MEDIUM:
            label->setFont(font_medium);
            break;
        case CI_UI_FONT_SMALL:
            label->setFont(font_small);
            break;
    }
}

void ciUICanvas::setRetinaResolution() {
    setGlobalCanvasWidth(CI_UI_GLOBAL_CANVAS_WIDTH*2);
    setPadding(CI_UI_GLOBAL_PADDING*2);
    setWidgetSpacing(CI_UI_GLOBAL_WIDGET_SPACING*2);
    setFontSize(CI_UI_FONT_LARGE, CI_UI_FONT_LARGE_SIZE*2);
    setFontSize(CI_UI_FONT_MEDIUM, CI_UI_FONT_MEDIUM_SIZE*2);
    setFontSize(CI_UI_FONT_SMALL, CI_UI_FONT_SMALL_SIZE*2);
    setGlobalButtonDimension(CI_UI_GLOBAL_BUTTON_DIMENSION*4);
    setGlobalSliderHeight(CI_UI_GLOBAL_SLIDER_HEIGHT*4);
    setGlobalSpacerHeight(CI_UI_GLOBAL_SPACING_HEIGHT*2);
    setGlobalGraphHeight(CI_UI_GLOBAL_GRAPH_HEIGHT*2);
}

void ciUICanvas::setGlobalSliderHeight(float _globalSliderHeight) {
    globalSliderHeight = _globalSliderHeight;
}

void ciUICanvas::setGlobalGraphHeight(float _globalGraphHeight) {
    globalGraphHeight = _globalGraphHeight;
}

void ciUICanvas::setGlobalButtonDimension(float _globalButtonDimension) {
    globalButtonDimension = _globalButtonDimension;
}

void ciUICanvas::setGlobalSpacerHeight(float _globalSpacerHeight) {
    globalSpacerHeight = _globalSpacerHeight;
}

float ciUICanvas::getGlobalSliderHeight() {
    return globalSliderHeight;
}

float ciUICanvas::getGlobalGraphHeight() {
    return globalGraphHeight;
}

float ciUICanvas::getGlobalButtonDimension() {
    return globalButtonDimension;
}

float ciUICanvas::getGlobalSpacerHeight() {
    return globalSpacerHeight;
}

void ciUICanvas::setGlobalCanvasWidth(float _globalCanvasWidth) {
    globalCanvasWidth = _globalCanvasWidth;
    rect->setWidth(globalCanvasWidth);
    paddedRect->setWidth(globalCanvasWidth+padding*2);
}

float ciUICanvas::getGlobalCanvasWidth() {
    return globalCanvasWidth;
}

void ciUICanvas::setWidgetPosition(ciUIWidgetPosition _position, int _align) {
    widgetPosition = _position;
    if (_align == -1) {
        if (_position == CI_UI_WIDGET_POSITION_DOWN ||
            _position == CI_UI_WIDGET_POSITION_UP) {
            widgetAlign = CI_UI_ALIGN_LEFT;
        }
        else {
            widgetAlign = CI_UI_ALIGN_FREE;
        }
    }
    else {
        widgetAlign = (ciUIWidgetAlignment)_align;
    }
}

void ciUICanvas::setWidgetFontSize(ciUIWidgetFontType _widgetFontSize) {
    widgetFontSize = _widgetFontSize;
}

ciUIWidgetPosition ciUICanvas::getWidgetPosition() {
    return widgetPosition;
}

ciUIWidgetFontType ciUICanvas::getWidgetFontSize() {
    return widgetFontSize;
}

void ciUICanvas::triggerEvent(ciUIWidget *child) {
    checkForKeyFocus(child);
    GUIevent->widget = child;
    ofNotifyEvent(newGUIEvent,*GUIevent,this);
}

void ciUICanvas::setUIColors(ciUIColor &cb, ciUIColor &co, ciUIColor &coh, ciUIColor &cf, ciUIColor &cfh, ciUIColor &cp, ciUIColor &cpo) {
    setWidgetColor(CI_UI_WIDGET_COLOR_BACK, cb);
    setWidgetColor(CI_UI_WIDGET_COLOR_OUTLINE, co);
    setWidgetColor(CI_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT, coh);
    setWidgetColor(CI_UI_WIDGET_COLOR_FILL, cf);
    setWidgetColor(CI_UI_WIDGET_COLOR_FILL_HIGHLIGHT, cfh);
    setWidgetColor(CI_UI_WIDGET_COLOR_PADDED, cp);
    setWidgetColor(CI_UI_WIDGET_COLOR_PADDED_OUTLINE, cpo);
    
    setColorBack(cb);
    setColorOutline(co);
    setColorOutlineHighlight(coh);
    setColorFill(cf);
    setColorFillHighlight(cfh);
    setColorPadded(cp);
    setColorPaddedOutline(cpo);
}

void ciUICanvas::setTheme(int theme) {
    switch(theme) {
        case CI_UI_THEME_DEFAULT:
        {
            ciUIColor cb = CI_UI_COLOR_BACK;
            ciUIColor co = CI_UI_COLOR_OUTLINE;
            ciUIColor coh = CI_UI_COLOR_OUTLINE_HIGHLIGHT;
            ciUIColor cf = CI_UI_COLOR_FILL;
            ciUIColor cfh = CI_UI_COLOR_FILL_HIGHLIGHT;
            ciUIColor cp = CI_UI_COLOR_PADDED;
            ciUIColor cpo = CI_UI_COLOR_PADDED_OUTLINE;
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_HACKER:
        {
            ciUIColor cb = ciUIColor( 0.294118*255.0, 0*255.0, 0.0588235*255.0, 0.196078*255.0 );
            ciUIColor co = ciUIColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.392157*255.0 );
            ciUIColor coh = ciUIColor( 0.294118*255.0, 0*255.0, 0.0588235*255.0, 0.784314*255.0 );
            ciUIColor cf = ciUIColor( 0.784314*255.0, 1*255.0, 0*255.0, 0.784314*255.0 );
            ciUIColor cfh = ciUIColor( 0.980392*255.0, 0.00784314*255.0, 0.235294*255.0, 1*255.0 );
            ciUIColor cp = ciUIColor( 0.0156863*255.0, 0*255.0, 0.0156863*255.0, 0.392157*255.0 );
            ciUIColor cpo = ciUIColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
            
        case CI_UI_THEME_HIPSTER:
        {
            ciUIColor cb = ciUIColor( 0.607843*255.0, 0.6*255.0, 0.509804*255.0, 0.196078*255.0 );
            ciUIColor co = ciUIColor( 0.231373*255.0, 0.392157*255.0, 0.501961*255.0, 0.392157*255.0 );
            ciUIColor coh = ciUIColor( 0.607843*255.0, 0.6*255.0, 0.509804*255.0, 0.784314*255.0 );
            ciUIColor cf = ciUIColor( 1*255.0, 0.52549*255.0, 0.0666667*255.0, 0.784314*255.0 );
            ciUIColor cfh = ciUIColor( 0.0313725*255.0, 0.101961*255.0, 0.188235*255.0, 1*255.0 );
            ciUIColor cp = ciUIColor( 0.196078*255.0, 0.25098*255.0, 0.352941*255.0, 0.392157*255.0 );
            ciUIColor cpo = ciUIColor( 0.231373*255.0, 0.392157*255.0, 0.501961*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_DIETER:
        {
            ciUIColor cb = ciUIColor( 0.803922*255.0, 0.741176*255.0, 0.682353*255.0, 0.196078*255.0 );
            ciUIColor co = ciUIColor( 0.478431*255.0, 0.356863*255.0, 0.243137*255.0, 0.392157*255.0 );
            ciUIColor coh = ciUIColor( 0.803922*255.0, 0.741176*255.0, 0.682353*255.0, 0.784314*255.0 );
            ciUIColor cf = ciUIColor( 0.980392*255.0, 0.294118*255.0, 0*255.0, 0.784314*255.0 );
            ciUIColor cfh = ciUIColor( 0.980392*255.0, 0.980392*255.0, 0.980392*255.0, 1*255.0 );
            ciUIColor cp = ciUIColor( 0.121569*255.0, 0.121569*255.0, 0.121569*255.0, 0.392157*255.0 );
            ciUIColor cpo = ciUIColor( 0.478431*255.0, 0.356863*255.0, 0.243137*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_BARBIE:
        {
            ciUIColor cb = ciUIColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 0.196078*255.0 );
            ciUIColor co = ciUIColor( 0*255.0, 0*255.0, 0*255.0, 0.392157*255.0 );
            ciUIColor coh = ciUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
            ciUIColor cf = ciUIColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 0.784314*255.0 );
            ciUIColor cfh = ciUIColor( 1*255.0, 0.94902*255.0, 0*255.0, 1*255.0 );
            ciUIColor cp = ciUIColor( 0*255.0, 0*255.0, 0*255.0, 0.392157*255.0 );
            ciUIColor cpo = ciUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_WINDOWS:
        {
            ciUIColor cb = ciUIColor( 0.0470588*255.0, 0.0588235*255.0, 0.4*255.0, 0.196078*255.0 );
            ciUIColor co = ciUIColor( 0.0431373*255.0, 0.0627451*255.0, 0.54902*255.0, 0.392157*255.0 );
            ciUIColor coh = ciUIColor( 0.0470588*255.0, 0.0588235*255.0, 0.4*255.0, 0.784314*255.0 );
            ciUIColor cf = ciUIColor( 0.054902*255.0, 0.305882*255.0, 0.678431*255.0, 0.784314*255.0 );
            ciUIColor cfh = ciUIColor( 0.0627451*255.0, 0.498039*255.0, 0.788235*255.0, 1*255.0 );
            ciUIColor cp = ciUIColor( 0.027451*255.0, 0.0352941*255.0, 0.239216*255.0, 0.392157*255.0 );
            ciUIColor cpo = ciUIColor( 0.0431373*255.0, 0.0627451*255.0, 0.54902*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MACOSX:
        {
            ciUIColor cb = ciUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.196078*255.0 );
            ciUIColor co = ciUIColor( 1*255.0, 0.94902*255.0, 0*255.0, 0.392157*255.0 );
            ciUIColor coh = ciUIColor( 0*255.0, 0*255.0, 0*255.0, 0.784314*255.0 );
            ciUIColor cf = ciUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
            ciUIColor cfh = ciUIColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 1*255.0 );
            ciUIColor cp = ciUIColor( 1*255.0, 0.94902*255.0, 0*255.0, 0.392157*255.0 );
            ciUIColor cpo = ciUIColor( 0*255.0, 0*255.0, 0*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_ZOOLANDER:
        {
            ciUIColor cb = ciUIColor( 0.160784*255.0, 0.133333*255.0, 0.121569*255.0, 0.196078*255.0 );
            ciUIColor co = ciUIColor( 0.0745098*255.0, 0.454902*255.0, 0.490196*255.0, 0.392157*255.0 );
            ciUIColor coh = ciUIColor( 0.160784*255.0, 0.133333*255.0, 0.121569*255.0, 0.784314*255.0 );
            ciUIColor cf = ciUIColor( 0.988235*255.0, 0.207843*255.0, 0.298039*255.0, 0.784314*255.0 );
            ciUIColor cfh = ciUIColor( 0.988235*255.0, 0.968627*255.0, 0.772549*255.0, 1*255.0 );
            ciUIColor cp = ciUIColor( 0.0392157*255.0, 0.74902*255.0, 0.737255*255.0, 0.392157*255.0 );
            ciUIColor cpo = ciUIColor( 0.0745098*255.0, 0.454902*255.0, 0.490196*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_VEGAN2:
        {
            ciUIColor cb = ciUIColor( 0.745098*255.0, 0.94902*255.0, 0.00784314*255.0, 0.196078*255.0 );
            ciUIColor co = ciUIColor( 0.533333*255.0, 0.768627*255.0, 0.145098*255.0, 0.392157*255.0 );
            ciUIColor coh = ciUIColor( 0.745098*255.0, 0.94902*255.0, 0.00784314*255.0, 0.784314*255.0 );
            ciUIColor cf = ciUIColor( 0.917647*255.0, 0.992157*255.0, 0.901961*255.0, 0.784314*255.0 );
            ciUIColor cfh = ciUIColor( 0.105882*255.0, 0.403922*255.0, 0.419608*255.0, 1*255.0 );
            ciUIColor cp = ciUIColor( 0.317647*255.0, 0.584314*255.0, 0.282353*255.0, 0.392157*255.0 );
            ciUIColor cpo = ciUIColor( 0.533333*255.0, 0.768627*255.0, 0.145098*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_BERLIN:
        {
            ciUIColor cb = ciUIColor( 0.6*255.0, 0.894118*255.0, 1*255.0, 0.196078*255.0 );
            ciUIColor co = ciUIColor( 0.294118*255.0, 0.34902*255.0, 0.419608*255.0, 0.392157*255.0 );
            ciUIColor coh = ciUIColor( 0.6*255.0, 0.894118*255.0, 1*255.0, 0.784314*255.0 );
            ciUIColor cf = ciUIColor( 0.968627*255.0, 0.309804*255.0, 0.309804*255.0, 0.784314*255.0 );
            ciUIColor cfh = ciUIColor( 1*255.0, 0.231373*255.0, 0.231373*255.0, 1*255.0 );
            ciUIColor cp = ciUIColor( 0.105882*255.0, 0.12549*255.0, 0.14902*255.0, 0.392157*255.0 );
            ciUIColor cpo = ciUIColor( 0.294118*255.0, 0.34902*255.0, 0.419608*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_METALGEAR:
        {
            ciUIColor cb = ciUIColor( 51, 44, 44, 75 );
            ciUIColor co = ciUIColor( 25, 26, 36, 100 );
            ciUIColor coh = ciUIColor( 51, 44, 44, 200 );
            ciUIColor cf = ciUIColor( 250, 101, 87, 200 );
            ciUIColor cfh = ciUIColor( 255, 255, 255, 255 );
            ciUIColor cp = ciUIColor( 0, 0, 0, 100 );
            ciUIColor cpo = ciUIColor( 25, 26, 36, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_TEALLIME:
        {
            ciUIColor cb = ciUIColor( 27, 103, 107, 75 );
            ciUIColor co = ciUIColor( 234, 253, 230, 100 );
            ciUIColor coh = ciUIColor( 27, 103, 107, 200 );
            ciUIColor cf = ciUIColor( 81, 149, 72, 200 );
            ciUIColor cfh = ciUIColor( 136, 196, 37, 255 );
            ciUIColor cp = ciUIColor( 190, 242, 2, 100 );
            ciUIColor cpo = ciUIColor( 234, 253, 230, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_VEGAN:
        {
            ciUIColor cb = ciUIColor( 81, 149, 72, 75 );
            ciUIColor co = ciUIColor( 27, 103, 107, 100 );
            ciUIColor coh = ciUIColor( 81, 149, 72, 200 );
            ciUIColor cf = ciUIColor( 136, 196, 37, 200 );
            ciUIColor cfh = ciUIColor( 190, 242, 2, 255 );
            ciUIColor cp = ciUIColor( 234, 253, 230, 100 );
            ciUIColor cpo = ciUIColor( 27, 103, 107, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_RUSTIC:
        {
            ciUIColor cb = ciUIColor( 196, 182, 109, 75 );
            ciUIColor co = ciUIColor( 247, 109, 60, 100 );
            ciUIColor coh = ciUIColor( 196, 182, 109, 200 );
            ciUIColor cf = ciUIColor( 213, 39, 5, 200 );
            ciUIColor cfh = ciUIColor( 240, 211, 119, 255 );
            ciUIColor cp = ciUIColor( 243, 232, 228, 100 );
            ciUIColor cpo = ciUIColor( 247, 109, 60, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MIDNIGHT:
        {
            ciUIColor cb = ciUIColor( 11, 72, 107, 75 );
            ciUIColor co = ciUIColor( 207, 240, 158, 100 );
            ciUIColor coh = ciUIColor( 11, 72, 107, 200 );
            ciUIColor cf = ciUIColor( 59, 134, 134, 200 );
            ciUIColor cfh = ciUIColor( 121, 189, 154, 255 );
            ciUIColor cp = ciUIColor( 168, 219, 168, 100 );
            ciUIColor cpo = ciUIColor( 207, 240, 158, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MINBLUE:
        {
            ciUIColor cb = ciUIColor( 254, 249, 240, 75 );
            ciUIColor co = ciUIColor( 176, 248, 255, 100 );
            ciUIColor coh = ciUIColor( 254, 249, 240, 200 );
            ciUIColor cf = ciUIColor( 0, 188, 209, 200 );
            ciUIColor cfh = ciUIColor( 118, 211, 222, 255 );
            ciUIColor cp = ciUIColor( 174, 232, 251, 100 );
            ciUIColor cpo = ciUIColor( 176, 248, 255, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_LIMESTONE:
        {
            ciUIColor cb = ciUIColor( 108, 144, 134, 75 );
            ciUIColor co = ciUIColor( 252, 84, 99, 100 );
            ciUIColor coh = ciUIColor( 108, 144, 134, 200 );
            ciUIColor cf = ciUIColor( 169, 204, 24, 200 );
            ciUIColor cfh = ciUIColor( 207, 73, 108, 255 );
            ciUIColor cp = ciUIColor( 235, 234, 188, 100 );
            ciUIColor cpo = ciUIColor( 252, 84, 99, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_SPEARMINT:
        {
            ciUIColor cb = ciUIColor( 25, 140, 9, 75 );
            ciUIColor co = ciUIColor( 255, 197, 95, 100 );
            ciUIColor coh = ciUIColor( 25, 140, 9, 200 );
            ciUIColor cf = ciUIColor( 220, 250, 250, 200 );
            ciUIColor cfh = ciUIColor( 239, 88, 141, 255 );
            ciUIColor cp = ciUIColor( 254, 169, 18, 100 );
            ciUIColor cpo = ciUIColor( 255, 197, 95, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MINPINK:
        {
            ciUIColor cb = ciUIColor( 220, 250, 250, 75 );
            ciUIColor co = ciUIColor( 25, 140, 9, 100 );
            ciUIColor coh = ciUIColor( 220, 250, 250, 200 );
            ciUIColor cf = ciUIColor( 239, 88, 141, 200 );
            ciUIColor cfh = ciUIColor( 254, 169, 18, 255 );
            ciUIColor cp = ciUIColor( 255, 197, 95, 100 );
            ciUIColor cpo = ciUIColor( 25, 140, 9, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_PEPTOBISMOL:
        {
            ciUIColor cb = ciUIColor( 223, 21, 26, 75 );
            ciUIColor co = ciUIColor( 0, 218, 60, 100 );
            ciUIColor coh = ciUIColor( 223, 21, 26, 200 );
            ciUIColor cf = ciUIColor( 244, 243, 40, 200 );
            ciUIColor cfh = ciUIColor( 253, 134, 3, 255 );
            ciUIColor cp = ciUIColor( 0, 203, 231, 100 );
            ciUIColor cpo = ciUIColor( 0, 218, 60, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_BILEBLUE:
        {
            ciUIColor cb = ciUIColor( 253, 134, 3, 75 );
            ciUIColor co = ciUIColor( 244, 243, 40, 100 );
            ciUIColor coh = ciUIColor( 253, 134, 3, 200 );
            ciUIColor cf = ciUIColor( 0, 203, 231, 200 );
            ciUIColor cfh = ciUIColor( 0, 218, 60, 255 );
            ciUIColor cp = ciUIColor( 223, 21, 26, 100 );
            ciUIColor cpo = ciUIColor( 244, 243, 40, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_COOLCLAY:
        {
            ciUIColor cb = ciUIColor( 153, 228, 255, 75 );
            ciUIColor co = ciUIColor( 75, 89, 107, 100 );
            ciUIColor coh = ciUIColor( 153, 228, 255, 200 );
            ciUIColor cf = ciUIColor( 247, 79, 79, 200 );
            ciUIColor cfh = ciUIColor( 255, 59, 59, 255 );
            ciUIColor cp = ciUIColor( 27, 32, 38, 100 );
            ciUIColor cpo = ciUIColor( 75, 89, 107, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_BLUEBLUE:
        {
            ciUIColor cb = ciUIColor( 0, 173, 239, 75 );
            ciUIColor co = ciUIColor( 255, 242, 0, 100 );
            ciUIColor coh = ciUIColor( 0, 0, 0, 200 );
            ciUIColor cf = ciUIColor( 0, 173, 239, 200 );
            ciUIColor cfh = ciUIColor( 236, 0, 140, 255 );
            ciUIColor cp = ciUIColor( 255, 242, 0, 100 );
            ciUIColor cpo = ciUIColor( 0, 0, 0, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_PINKPANTHER:
        {
            ciUIColor cb = ciUIColor( 236, 0, 140, 75 );
            ciUIColor co = ciUIColor( 0, 0, 0, 100 );
            ciUIColor coh = ciUIColor( 0, 173, 239, 200 );
            ciUIColor cf = ciUIColor( 236, 0, 140, 200 );
            ciUIColor cfh = ciUIColor( 255, 242, 0, 255 );
            ciUIColor cp = ciUIColor( 0, 0, 0, 100 );
            ciUIColor cpo = ciUIColor( 0, 173, 239, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MAROON:
        {
            ciUIColor cb = ciUIColor( 101, 150, 158, 75 );
            ciUIColor co = ciUIColor( 219, 217, 210, 100 );
            ciUIColor coh = ciUIColor( 101, 150, 158, 200 );
            ciUIColor cf = ciUIColor( 171, 20, 44, 200 );
            ciUIColor cfh = ciUIColor( 189, 219, 222, 255 );
            ciUIColor cp = ciUIColor( 205, 212, 108, 100 );
            ciUIColor cpo = ciUIColor( 219, 217, 210, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_PINKLATTE:
        {
            ciUIColor cb = ciUIColor( 218, 216, 167, 75 );
            ciUIColor co = ciUIColor( 127, 199, 175, 100 );
            ciUIColor coh = ciUIColor( 218, 216, 167, 200 );
            ciUIColor cf = ciUIColor( 255, 61, 127, 200 );
            ciUIColor cfh = ciUIColor( 255, 158, 157, 255 );
            ciUIColor cp = ciUIColor( 63, 184, 175, 100 );
            ciUIColor cpo = ciUIColor( 127, 199, 175, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MINGREEN:
        {
            ciUIColor cb = ciUIColor( 255, 255, 255, 75 );
            ciUIColor co = ciUIColor( 242, 230, 194, 100 );
            ciUIColor coh = ciUIColor( 255, 255, 255, 200 );
            ciUIColor cf = ciUIColor( 111, 191, 162, 200 );
            ciUIColor cfh = ciUIColor( 191, 184, 174, 255 );
            ciUIColor cp = ciUIColor( 242, 199, 119, 100 );
            ciUIColor cpo = ciUIColor( 242, 230, 194, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_HELLOYELLOW:
        {
            ciUIColor cb = ciUIColor( 255, 211, 0, 75 );
            ciUIColor co = ciUIColor( 74, 186, 176, 100 );
            ciUIColor coh = ciUIColor( 152, 33, 0, 200 );
            ciUIColor cf = ciUIColor( 255, 211, 0, 200 );
            ciUIColor cfh = ciUIColor( 255, 245, 158, 255 );
            ciUIColor cp = ciUIColor( 74, 186, 176, 100 );
            ciUIColor cpo = ciUIColor( 152, 33, 0, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_TEALTEAL:
        {
            ciUIColor cb = ciUIColor( 74, 186, 176, 75 );
            ciUIColor co = ciUIColor( 255, 211, 0, 100 );
            ciUIColor coh = ciUIColor( 255, 245, 158, 200 );
            ciUIColor cf = ciUIColor( 74, 186, 176, 200 );
            ciUIColor cfh = ciUIColor( 152, 33, 0, 255 );
            ciUIColor cp = ciUIColor( 255, 211, 0, 100 );
            ciUIColor cpo = ciUIColor( 255, 245, 158, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_RUSTICORANGE:
        {
            ciUIColor cb = ciUIColor( 107, 85, 48, 75 );
            ciUIColor co = ciUIColor( 49, 48, 66, 100 );
            ciUIColor coh = ciUIColor( 107, 85, 48, 200 );
            ciUIColor cf = ciUIColor( 255, 109, 36, 200 );
            ciUIColor cfh = ciUIColor( 255, 235, 107, 255 );
            ciUIColor cp = ciUIColor( 42, 135, 50, 100 );
            ciUIColor cpo = ciUIColor( 49, 48, 66, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_TEALSALMON:
        {
            ciUIColor cb = ciUIColor( 78, 133, 136, 75 );
            ciUIColor co = ciUIColor( 56, 69, 59, 100 );
            ciUIColor coh = ciUIColor( 78, 133, 136, 200 );
            ciUIColor cf = ciUIColor( 255, 70, 84, 200 );
            ciUIColor cfh = ciUIColor( 255, 213, 106, 255 );
            ciUIColor cp = ciUIColor( 255, 254, 211, 100 );
            ciUIColor cpo = ciUIColor( 56, 69, 59, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_CITRUSBLUE:
        {
            ciUIColor cb = ciUIColor( 57, 142, 182, 75 );
            ciUIColor co = ciUIColor( 34, 104, 136, 100 );
            ciUIColor coh = ciUIColor( 57, 142, 182, 200 );
            ciUIColor cf = ciUIColor( 255, 162, 0, 200 );
            ciUIColor cfh = ciUIColor( 255, 214, 0, 255 );
            ciUIColor cp = ciUIColor( 255, 245, 0, 100 );
            ciUIColor cpo = ciUIColor( 34, 104, 136, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_LIMEPURPLE:
        {
            ciUIColor cb = ciUIColor( 87, 54, 255, 75 );
            ciUIColor co = ciUIColor( 38, 38, 38, 100 );
            ciUIColor coh = ciUIColor( 87, 54, 255, 200 );
            ciUIColor cf = ciUIColor( 231, 255, 54, 200 );
            ciUIColor cfh = ciUIColor( 255, 54, 111, 255 );
            ciUIColor cp = ciUIColor( 35, 116, 222, 100 );
            ciUIColor cpo = ciUIColor( 38, 38, 38, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_LIMESTONE2:
        {
            ciUIColor cb = ciUIColor( 101, 98, 115, 75 );
            ciUIColor co = ciUIColor( 89, 186, 169, 100 );
            ciUIColor coh = ciUIColor( 101, 98, 115, 200 );
            ciUIColor cf = ciUIColor( 216, 241, 113, 200 );
            ciUIColor cfh = ciUIColor( 252, 255, 217, 255 );
            ciUIColor cp = ciUIColor( 64, 18, 44, 100 );
            ciUIColor cpo = ciUIColor( 89, 186, 169, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_COOLPURPLE:
        {
            ciUIColor cb = ciUIColor( 38, 137, 233, 75 );
            ciUIColor co = ciUIColor( 11, 246, 147, 100 );
            ciUIColor coh = ciUIColor( 38, 137, 233, 200 );
            ciUIColor cf = ciUIColor( 233, 26, 157, 200 );
            ciUIColor cfh = ciUIColor( 246, 182, 11, 255 );
            ciUIColor cp = ciUIColor( 246, 242, 11, 100 );
            ciUIColor cpo = ciUIColor( 11, 246, 147, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_GRAYRED:
        {
            ciUIColor cb = ciUIColor( 41, 34, 31, 75 );
            ciUIColor co = ciUIColor( 19, 116, 125, 100 );
            ciUIColor coh = ciUIColor( 41, 34, 31, 200 );
            ciUIColor cf = ciUIColor( 252, 53, 76, 200 );
            ciUIColor cfh = ciUIColor( 252, 247, 197, 255 );
            ciUIColor cp = ciUIColor( 10, 191, 188, 100 );
            ciUIColor cpo = ciUIColor( 19, 116, 125, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_METALGEAR2:
        {
            ciUIColor cb = ciUIColor( 205, 189, 174, 75 );
            ciUIColor co = ciUIColor( 122, 91, 62, 100 );
            ciUIColor coh = ciUIColor( 205, 189, 174, 200 );
            ciUIColor cf = ciUIColor( 250, 75, 0, 200 );
            ciUIColor cfh = ciUIColor( 250, 250, 250, 255 );
            ciUIColor cp = ciUIColor( 31, 31, 31, 100 );
            ciUIColor cpo = ciUIColor( 122, 91, 62, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_LIGHTPINK:
        {
            ciUIColor cb = ciUIColor( 158, 30, 76, 75 );
            ciUIColor co = ciUIColor( 143, 143, 143, 100 );
            ciUIColor coh = ciUIColor( 158, 30, 76, 200 );
            ciUIColor cf = ciUIColor( 236, 236, 236, 200 );
            ciUIColor cfh = ciUIColor( 255, 17, 104, 255 );
            ciUIColor cp = ciUIColor( 37, 2, 15, 100 );
            ciUIColor cpo = ciUIColor( 143, 143, 143, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MINPINK2:
        {
            ciUIColor cb = ciUIColor( 236, 236, 236, 75 );
            ciUIColor co = ciUIColor( 158, 30, 76, 100 );
            ciUIColor coh = ciUIColor( 236, 236, 236, 200 );
            ciUIColor cf = ciUIColor( 255, 17, 104, 200 );
            ciUIColor cfh = ciUIColor( 37, 2, 15, 255 );
            ciUIColor cp = ciUIColor( 143, 143, 143, 100 );
            ciUIColor cpo = ciUIColor( 158, 30, 76, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MAXPINK:
        {
            ciUIColor cb = ciUIColor( 255, 20, 87, 75 );
            ciUIColor co = ciUIColor( 10, 10, 10, 100 );
            ciUIColor coh = ciUIColor( 227, 246, 255, 200 );
            ciUIColor cf = ciUIColor( 255, 20, 87, 200 );
            ciUIColor cfh = ciUIColor( 255, 216, 125, 255 );
            ciUIColor cp = ciUIColor( 10, 10, 10, 100 );
            ciUIColor cpo = ciUIColor( 227, 246, 255, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MINYELLOW:
        {
            ciUIColor cb = ciUIColor( 229, 228, 218, 75 );
            ciUIColor co = ciUIColor( 216, 210, 153, 100 );
            ciUIColor coh = ciUIColor( 229, 228, 218, 200 );
            ciUIColor cf = ciUIColor( 245, 224, 56, 200 );
            ciUIColor cfh = ciUIColor( 23, 22, 92, 255 );
            ciUIColor cp = ciUIColor( 190, 191, 158, 100 );
            ciUIColor cpo = ciUIColor( 216, 210, 153, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MINLIME:
        {
            ciUIColor cb = ciUIColor( 245, 225, 226, 75 );
            ciUIColor co = ciUIColor( 225, 183, 237, 100 );
            ciUIColor coh = ciUIColor( 245, 225, 226, 200 );
            ciUIColor cf = ciUIColor( 185, 222, 81, 200 );
            ciUIColor cfh = ciUIColor( 209, 227, 137, 255 );
            ciUIColor cp = ciUIColor( 224, 72, 145, 100 );
            ciUIColor cpo = ciUIColor( 225, 183, 237, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MINORANGE:
        {
            ciUIColor cb = ciUIColor( 204, 204, 204, 75 );
            ciUIColor co = ciUIColor( 111, 111, 111, 100 );
            ciUIColor coh = ciUIColor( 204, 204, 204, 200 );
            ciUIColor cf = ciUIColor( 255, 100, 0, 200 );
            ciUIColor cfh = ciUIColor( 255, 255, 255, 255 );
            ciUIColor cp = ciUIColor( 51, 51, 51, 100 );
            ciUIColor cpo = ciUIColor( 111, 111, 111, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_GRAYDAY:
        {
            ciUIColor cb = ciUIColor( 177, 198, 204, 75 );
            ciUIColor co = ciUIColor( 255, 255, 255, 100 );
            ciUIColor coh = ciUIColor( 20, 20, 20, 200 );
            ciUIColor cf = ciUIColor( 177, 198, 204, 200 );
            ciUIColor cfh = ciUIColor( 255, 239, 94, 255 );
            ciUIColor cp = ciUIColor( 255, 255, 255, 100 );
            ciUIColor cpo = ciUIColor( 20, 20, 20, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case CI_UI_THEME_MINBLACK:
        {
            ciUIColor cb = ciUIColor( 255, 255, 255, 75 );
            ciUIColor co = ciUIColor( 209, 231, 81, 100 );
            ciUIColor coh = ciUIColor( 255, 255, 255, 200 );
            ciUIColor cf = ciUIColor( 0, 0, 0, 200 );
            ciUIColor cfh = ciUIColor( 38, 173, 228, 255 );
            ciUIColor cp = ciUIColor( 77, 188, 233, 100 );
            ciUIColor cpo = ciUIColor( 209, 231, 81, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        default:
        {
            ciUIColor cb = CI_UI_COLOR_BACK;
            ciUIColor co = CI_UI_COLOR_OUTLINE;
            ciUIColor coh = CI_UI_COLOR_OUTLINE_HIGHLIGHT;
            ciUIColor cf = CI_UI_COLOR_FILL;
            ciUIColor cfh = CI_UI_COLOR_FILL_HIGHLIGHT;
            ciUIColor cp = CI_UI_COLOR_PADDED;
            ciUIColor cpo = CI_UI_COLOR_PADDED_OUTLINE;
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
    }
}

ciUIColor& ciUICanvas::getWidgetColorPadded() {
    return widget_color_padded_rect;
}

ciUIColor& ciUICanvas::getWidgetColorPaddedOutline()
{
    return widget_color_padded_rect_outline;
}

ciUIColor& ciUICanvas::getWidgetColorBack() {
    return widget_color_back;
}

ciUIColor& ciUICanvas::getWidgetColorOutline() {
    return widget_color_outline;
}

ciUIColor& ciUICanvas::getWidgetColorOutlineHighlight() {
    return widget_color_outline_highlight;
}

ciUIColor& ciUICanvas::getWidgetColorFill() {
    return widget_color_fill;
}

ciUIColor& ciUICanvas::getWidgetColorFillHighlight() {
    return widget_color_fill_highlight;
}

void ciUICanvas::setWidgetDrawingProperties(ciUIWidget *widget) {
    widget->setDrawPaddingOutline(bDrawWidgetPaddingOutline);
    widget->setDrawPadding(bDrawWidgetPadding);
}

void ciUICanvas::setWidgetColor(ciUIWidget *widget) {
    widget->setColorBack(color_back);
    widget->setColorOutline(color_outline);
    widget->setColorOutlineHighlight(color_outline_highlight);
    widget->setColorFill(color_fill);
    widget->setColorFillHighlight(color_fill_highlight);
    widget->setColorPadded(color_padded_rect);
    widget->setColorPaddedOutline(color_padded_rect_outline);
}

void ciUICanvas::setWidgetColor(int _target, ciUIColor _color) {
    switch (_target) {
        case CI_UI_WIDGET_COLOR_BACK:
        {
            widget_color_back = _color;
            for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
                (*it)->setColorBack(_color);
            }
        }
            break;
            
        case CI_UI_WIDGET_COLOR_OUTLINE:
        {
            widget_color_outline = _color;
            for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
                (*it)->setColorOutline(_color);
            }
        }
            break;
            
        case CI_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT:
        {
            widget_color_outline_highlight = _color;
            for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
                (*it)->setColorOutlineHighlight(_color);
            }
        }
            break;
            
        case CI_UI_WIDGET_COLOR_FILL:
        {
            widget_color_fill = _color;
            for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
                (*it)->setColorFill(_color);
            }
        }
            break;
            
        case CI_UI_WIDGET_COLOR_FILL_HIGHLIGHT:
        {
            widget_color_fill_highlight = _color;
            for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
                (*it)->setColorFillHighlight(_color);
            }
        }
            break;
            
        case CI_UI_WIDGET_COLOR_PADDED:
        {
            widget_color_padded_rect = _color;
            for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
                (*it)->setColorPadded(_color);
            }
        }
            break;
            
        case CI_UI_WIDGET_COLOR_PADDED_OUTLINE:
        {
            widget_color_padded_rect_outline = _color;
            for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
                (*it)->setColorPaddedOutline(_color);
            }
        }
            break;
            
        default:
            break;
    }
}

ciUIWidget *ciUICanvas::getWidget(const std::string &_name, int widgetID) {
    if(widgetID == -1) {
        std::multimap<std::string, ciUIWidget *>::iterator wit = widgets_map.find(_name);
        if(wit != widgets_map.end()) {
            return wit->second;
        }
    }
    else {
        for(std::multimap<std::string, ciUIWidget*>::iterator wit = widgets_map.equal_range(_name).first; wit != widgets_map.equal_range(_name).second; ++wit) {
            if(wit->second->getID() == widgetID) {
                return wit->second;
            }
        }
        std::multimap<std::string, ciUIWidget *>::iterator wit = widgets_map.find(_name);
        if(wit != widgets_map.end()) {
            return wit->second;
        }
    }
    return nullptr;
}

void ciUICanvas::removeWidget(const std::string &_name) {
    ciUIWidget *w = getWidget(_name);
    if(w != nullptr) {
        removeWidget(w);
    }
}

void ciUICanvas::setPosition(int x, int y) {
    rect->x = x;
    rect->y = y;
}

void ciUICanvas::setHeight(float _height) {
    setDimensions(rect->getWidth(), _height);
}

void ciUICanvas::setWidth(float _width) {
    setDimensions(_width, rect->getHeight());
}

void ciUICanvas::setDimensions(float _width, float _height) {
    rect->setWidth(_width);
    rect->setHeight(_height);
    paddedRect->width = rect->width+padding*2;
    paddedRect->height = rect->height+padding*2;
}

void ciUICanvas::setDrawPadding(bool _draw_padded_rect) {
    draw_padded_rect = _draw_padded_rect;
}

void ciUICanvas::setDrawWidgetPadding(bool _draw_padded_rect) {
    for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
        (*it)->setDrawPadding(_draw_padded_rect);
    }
    bDrawWidgetPadding = _draw_padded_rect;
}

bool ciUICanvas::getDrawWidgetPadding() {
    return bDrawWidgetPadding;
}

void ciUICanvas::setDrawPaddingOutline(bool _draw_padded_rect_outline) {
    draw_padded_rect_outline = _draw_padded_rect_outline;
}

void ciUICanvas::setDrawWidgetPaddingOutline(bool _draw_padded_rect_outline) {
    for(std::vector<ciUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
        (*it)->setDrawPaddingOutline(_draw_padded_rect_outline);
    }
    bDrawWidgetPaddingOutline = _draw_padded_rect_outline;
}

bool ciUICanvas::getDrawWidgetPaddingOutline() {
    return bDrawWidgetPaddingOutline;
}

const std::vector<ciUIWidget*> &ciUICanvas::getWidgets() const {
    return widgets;
}

std::vector<ciUIWidget*> ciUICanvas::getWidgetsOfType(ciUIWidgetType type) const {
    std::vector<ciUIWidget*> widgetToReturn;
    for(std::vector<ciUIWidget *>::const_iterator it = widgets.begin(); it != widgets.end(); ++it) {
        if((*it)->getKind() == type) {
            widgetToReturn.push_back((*it));
        }
    }
    return widgetToReturn;
}

void ciUICanvas::pushbackWidget(ciUIWidget *widget, bool addWidgetToFront) {
    widget->setID(uniqueIDs);
    uniqueIDs++;
    
    if(addWidgetToFront) {
        std::vector<ciUIWidget*>::iterator it;
        it = widgets.begin();
        it = widgets.insert (it,widget);
    }
    else {
        widgets.push_back(widget);
    }
    widgets_map.insert(std::pair<std::string,ciUIWidget *>(widget->getName(), widget));
}

bool ciUICanvas::updateFont(ciUIWidgetFontType _kind,
                            const std::string &filename,
                             int fontsize,
                             bool _bAntiAliased,
                             bool _bFullCharacterSet,
                             bool makeContours,
                             float simplifyAmt,
                             int dpi)
{
    bool success = false;
    switch(_kind) {
        case CI_UI_FONT_LARGE:
        {
            
            font_large = ci::gl::TextureFont::create(ci::Font(filename, fontsize));
            success = font_large != nullptr;
            //success = font_large->load(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
        }
            break;
            
        case CI_UI_FONT_MEDIUM:
        {
            font_medium = ci::gl::TextureFont::create(ci::Font(filename, fontsize));
            success = font_medium != nullptr;
            //success = font_medium->load(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
        }
            break;
            
        case CI_UI_FONT_SMALL:
        {
            font_small = ci::gl::TextureFont::create(ci::Font(filename, fontsize));
            success = font_small != nullptr;
            //success = font_small->load(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
        }
            break;
    }
    return success;
}

void ciUICanvas::checkForKeyFocus(ciUIWidget *child) {
    if(child->getKind() == CI_UI_WIDGET_TEXTINPUT) {
        ciUITextInput *textinput = (ciUITextInput *) child;
        if(textinput->isFocused())
        {
            hasKeyBoard = true;
            return;        
        }
    }        
    hasKeyBoard = false;
}
