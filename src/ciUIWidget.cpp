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

#include "ciUI.h"
#include "ciUIWidget.h"

ciUIWidget::ciUIWidget()
: parent(nullptr),
rect(nullptr),
paddedRect(nullptr),
font(nullptr),
name("base"),
kind(CI_UI_WIDGET_BASE),
ID(-1),
hit(false),
visible(true),
state(CI_UI_STATE_NORMAL),
draw_back(true),
draw_outline(false),
draw_fill(false),
draw_fill_highlight(false),
draw_outline_highlight(false),
padding(CI_UI_GLOBAL_PADDING),
draw_padded_rect(CI_UI_DRAW_PADDING),
draw_padded_rect_outline(CI_UI_DRAW_PADDING_OUTLINE),
color_back(CI_UI_COLOR_BACK),
color_outline(CI_UI_COLOR_OUTLINE),
color_outline_highlight(CI_UI_COLOR_OUTLINE_HIGHLIGHT),
color_fill(CI_UI_COLOR_FILL),
color_fill_highlight(CI_UI_COLOR_FILL_HIGHLIGHT),
color_padded_rect(CI_UI_COLOR_PADDED),
color_padded_rect_outline(CI_UI_COLOR_PADDED_OUTLINE),
embedded(false),
modal(false),
bKeyHit(false),
triggerType(CI_UI_TRIGGER_ALL)
{
#ifdef CI_UI_TARGET_TOUCH
    touchId = -1;
#endif
}

ciUIWidget::~ciUIWidget()
{
    if(rect != nullptr)
    {
        delete rect;
    }
    if(paddedRect != nullptr)
    {
        delete paddedRect;
    }
    keyBindings.clear();
}

// Mitchell Nordine - custom copy constructor for heap allocation handling.
ciUIWidget::ciUIWidget(const ciUIWidget &other)
: parent(nullptr),
rect(nullptr),
paddedRect(nullptr),
//font(nullptr),
font(other.font),
name(other.name),
kind(other.kind),
ID(other.ID),
hit(other.hit),
visible(other.visible),
state(other.state),
draw_back(other.draw_back),
draw_outline(other.draw_outline),
draw_outline_highlight(other.draw_outline_highlight),
draw_fill(other.draw_fill),
draw_fill_highlight(other.draw_fill_highlight),
padding(other.padding),
draw_padded_rect(other.draw_padded_rect),
draw_padded_rect_outline(other.draw_padded_rect_outline),
color_back(other.color_back),
color_outline(other.color_outline),
color_outline_highlight(other.color_outline_highlight),
color_fill(other.color_fill),
color_fill_highlight(other.color_fill_highlight),
color_padded_rect(other.color_padded_rect),
color_padded_rect_outline(other.color_padded_rect_outline),
embedded(other.embedded),                               
modal(other.modal),
bKeyHit(other.bKeyHit),
keyBindings(other.keyBindings),
triggerType(CI_UI_TRIGGER_ALL)
{
    if (other.rect) {
        initRect(other.rect->getX(), other.rect->getY(), other.rect->getWidth(), other.rect->getHeight());
    }
    else {
        initRect();
    }
}

// Mitchell Nordine - custom assignment operator for heap allocation handling.
ciUIWidget& ciUIWidget::operator=(const ciUIWidget &other)
{
    name = other.name;
    kind = other.kind;
    visible = other.visible;
    ID = other.ID;
    hit = other.hit;
    state = other.state;
    embedded = other.embedded;
    modal = other.modal;
    draw_back = other.draw_back;
    draw_outline = other.draw_outline;
    draw_outline_highlight = other.draw_outline_highlight;
    draw_fill = other.draw_fill;
    draw_fill_highlight = other.draw_fill_highlight;
    color_back = other.color_back;
    color_outline = other.color_outline;
    color_outline_highlight = other.color_outline_highlight;
    color_fill = other.color_fill;
    color_fill_highlight = other.color_fill_highlight;
    padding = other.padding;
    draw_padded_rect = other.draw_padded_rect;
    draw_padded_rect_outline = other.draw_padded_rect_outline;
    triggerType = other.triggerType;
    bKeyHit = other.bKeyHit;
    if (other.rect) {
        initRect(other.rect->getX(), other.rect->getY(), other.rect->getWidth(), other.rect->getHeight());
    }
    else {
        initRect();
    }
    return *this;
}

void ciUIWidget::initRect(float x, float y, float w, float h)
{
    if(rect != nullptr)
    {
        delete rect;
    }
    rect = new ciUIRectangle(x,y,w,h);
    initPaddingRect();
}

void ciUIWidget::initPaddingRect()
{
    if(paddedRect != nullptr)
    {
        delete paddedRect;
    }
    paddedRect = new ciUIRectangle(-padding, -padding, rect->getWidth()+padding*2.0, rect->getHeight()+padding*2.0);
    paddedRect->setParent(rect);
    calculatePaddingRect();
}

void ciUIWidget::calculatePaddingRect()
{
    float xMax = rect->getWidth();
    float yMax = rect->getHeight();
    std::vector<ciUIWidget *>::iterator it = embeddedWidgets.begin();
    std::vector<ciUIWidget *>::iterator eit = embeddedWidgets.end();
    for(; it != eit; ++it) {
        if((*it)->isVisible()) {
            ciUIRectangle *r = (*it)->getRect();
            if(r->getMaxX() > xMax) {
                xMax = r->getMaxX();
            }
            if(r->getMaxY() > yMax) {
                yMax = r->getMaxY();
            }
        }
    }
    paddedRect->set(-padding, -padding, xMax+padding*2.0, yMax+padding*2.0);
}

void ciUIWidget::setup()
{
    //Custom Setup for Widgets
}

void ciUIWidget::update()
{

}

void ciUIWidget::draw() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    drawPadded();
    drawPaddedOutline();
    drawBack();
    drawOutline();
    drawOutlineHighlight();
    drawFill();
    drawFillHighlight();
}

void ciUIWidget::drawBack()
{
    if(draw_back) {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_back);
        rect->draw(true);
    }
}

void ciUIWidget::drawOutline()
{
    if(draw_outline) {
        //ciUINoFill();
        ci::gl::ScopedColor scopedColor(color_outline);
        rect->draw(false);
    }
}

void ciUIWidget::drawOutlineHighlight()
{
    if(draw_outline_highlight) {
        //ciUINoFill();
        ci::gl::ScopedColor scopedColor(color_outline_highlight);
        rect->draw(false);
    }
}

void ciUIWidget::drawFill() {
    if(draw_fill) {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill);
        rect->draw(true);
    }
}

void ciUIWidget::drawFillHighlight() {
    if(draw_fill_highlight) {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill_highlight);
        rect->draw(true);
    }
}

void ciUIWidget::drawPadded() {
    if(draw_padded_rect && !embedded) {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_padded_rect);
        paddedRect->draw(true);
    }
}

void ciUIWidget::drawPaddedOutline() {
    if(draw_padded_rect_outline && !embedded) {
        //ciUINoFill();
        ci::gl::ScopedColor scopedColor(color_padded_rect_outline);
        paddedRect->draw(false);
    }
}

#ifdef CI_UI_TARGET_TOUCH          //iOS Mode
void ciUIWidget::touchDown(float x, float y, int id) {
    if(touchId == -1) {
        this->mousePressed(x, y, 0);
        if(hit) {
            touchId = id;
        }
    }
}

void ciUIWidget::touchMoved(float x, float y, int id) {
    if(touchId == id) {
        this->mouseDragged(x, y, 0);
    }
}

void ciUIWidget::touchUp(float x, float y, int id) {
    if(touchId == id) {
        this->mouseReleased(x, y, 0);
        touchId = -1;
    }
}

void ciUIWidget::touchCancelled(float x, float y, int id) {
    if(touchId == id) {
        this->mouseReleased(x, y, 0);
        touchId = -1;
    }
}
#endif

ciUIWidget* ciUIWidget::setTriggerType(ciUITriggerType _triggerType)
{
    triggerType = _triggerType;
    return this; 
}

ciUITriggerType ciUIWidget::getTriggerType()
{
    return triggerType;
}

void ciUIWidget::setParent(ciUIWidget *_parent)
{
    parent = _parent;
}

void ciUIWidget::setRectParent(ciUIRectangle *_prect)
{
    rect->setParent(_prect);
}

ciUIWidget *ciUIWidget::getParent()
{
    return parent;
}

ciUIRectangle* ciUIWidget::getRect()
{
    return rect;
}

void ciUIWidget::setName(const std::string &_name)
{
    name = _name;
}

void ciUIWidget::setState(int _state)
{
    state = _state;
}

int ciUIWidget::getState()
{
    return state;
}

void ciUIWidget::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
}

void ciUIWidget::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
}

void ciUIWidget::setDrawBack(bool _draw_back)
{
    draw_back = _draw_back;
}

void ciUIWidget::setDrawOutline(bool _draw_outline)
{
    draw_outline = _draw_outline;
}

void ciUIWidget::setDrawFill(bool _draw_fill)
{
    draw_fill = _draw_fill;
}

void ciUIWidget::setDrawFillHighLight(bool _draw_fill_highlight)
{
    draw_fill_highlight = _draw_fill_highlight;
}

void ciUIWidget::setDrawOutlineHighLight(bool _draw_outline_hightlight)
{
    draw_outline_highlight = _draw_outline_hightlight;
}

bool ciUIWidget::getDrawPadding()
{
    return draw_padded_rect;
}

bool ciUIWidget::getDrawPaddingOutline() {
    return draw_padded_rect_outline;
}

bool ciUIWidget::getDrawBack() {
    return draw_back;
}

bool ciUIWidget::getDrawOutline() {
    return draw_outline;
}

bool ciUIWidget::getDrawFill() {
    return draw_fill;
}

bool ciUIWidget::getDrawFillHighLight() {
    return draw_fill_highlight;
}

bool ciUIWidget::getDrawOutlineHighLight() {
    return draw_outline_highlight;
}

void ciUIWidget::setColorBack(ciUIColor _color_back) {
    color_back = _color_back;
}

void ciUIWidget::setColorOutline(ciUIColor _color_outline) {
    color_outline = _color_outline;
}

void ciUIWidget::setColorOutlineHighlight(ciUIColor _color_outline_highlight) {
    color_outline_highlight = _color_outline_highlight;
}

void ciUIWidget::setColorFill(ciUIColor _color_fill) {
    color_fill = _color_fill;
}

void ciUIWidget::setColorFillHighlight(ciUIColor _color_fill_highlight) {
    color_fill_highlight = _color_fill_highlight;
}

void ciUIWidget::setColorPadded(ciUIColor _color_padded_rect) {
    color_padded_rect = _color_padded_rect;
}

void ciUIWidget::setColorPaddedOutline(ciUIColor _color_padded_rect_outline) {
    color_padded_rect_outline = _color_padded_rect_outline;
}

ciUIColor& ciUIWidget::getColorPadded() {
    return color_padded_rect;
}

ciUIColor& ciUIWidget::getColorPaddedOutline() {
    return color_padded_rect_outline;
}

ciUIColor& ciUIWidget::getColorBack() {
    return color_back;
}

ciUIColor& ciUIWidget::getColorOutline() {
    return color_outline;
}

ciUIColor& ciUIWidget::getColorOutlineHighlight() {
    return color_outline_highlight;
}

ciUIColor& ciUIWidget::getColorFill() {
    return color_fill;
}

ciUIColor& ciUIWidget::getColorFillHighlight() {
    return color_fill_highlight;
}

void ciUIWidget::setKind(ciUIWidgetType _kind) {
    kind = _kind;
}

ciUIWidgetType ciUIWidget::getKind() {
    return kind;
}

void ciUIWidget::setFont(ci::gl::TextureFontRef _font) {
    font = _font;
}

void ciUIWidget::setVisible(bool _visible) {
    visible = _visible;
}

bool ciUIWidget::isVisible() {
    return visible;
}

void ciUIWidget::toggleVisible() {
    visible =! visible;
}

bool ciUIWidget::isHit(float x, float y) {
    if(visible) {
        return rect->inside(x, y);
    }
    else {
        return false;
    }
}

std::string& ciUIWidget::getName() {
    return name;
}

void ciUIWidget::triggerEvent(ciUIWidget *child) {
    if(parent != nullptr) {
        parent->triggerEvent(child);
    }
}

void ciUIWidget::triggerSelf() {
    if(parent != nullptr) {
        parent->triggerEvent(this);
    }
}

void ciUIWidget::setPadding(float _padding) {
    padding = _padding;
    calculatePaddingRect();
}

float ciUIWidget::getPadding() {
    return padding;
}

ciUIRectangle * ciUIWidget::getPaddingRect() {
    return paddedRect;
}

void ciUIWidget::stateChange() {
    
}

bool ciUIWidget::isDraggable() {
    return false;
}

bool ciUIWidget::isEmbedded() {
    return embedded;
}

void ciUIWidget::setEmbedded(bool _embedded) {
    embedded = _embedded;
}

void ciUIWidget::setID(int _id) {
    ID = _id;
}

int ciUIWidget::getID() {
    return ID;
}

//void ciUIWidget::positionWidget(ciUIWidget *widget)
//{
//    widget->getRect()->setX(0);
//    widget->getRect()->setY(0);
//    calculatePaddingRect();
//}
//
//void ciUIWidget::positionWidgetDown(ciUIWidget *widget)
//{
//    widget->getRect()->setX(0);
//    widget->getRect()->setY(rect->getHeight()+padding);
//    calculatePaddingRect();
//}
//
//void ciUIWidget::positionWidgetUp(ciUIWidget *widget)
//{
//    widget->getRect()->setX(0);
//    widget->getRect()->setY(-widget->getRect()->getHeight()-padding);
//    calculatePaddingRect();
//}
//
//void ciUIWidget::positionWidgetLeft(ciUIWidget *widget)
//{
//    widget->getRect()->setX(-widget->getRect()->getWidth()-padding);
//    widget->getRect()->setY(0);
//    calculatePaddingRect();
//}
//
//void ciUIWidget::positionWidgetRight(ciUIWidget *widget)
//{
//    widget->getRect()->setX(rect->getWidth()+padding);
//    widget->getRect()->setY(0);
//    calculatePaddingRect();
//}

void ciUIWidget::addWidget(ciUIWidget *widget) {

}

void ciUIWidget::removeWidget(ciUIWidget *widget) {
    
}

bool ciUIWidget::hasLabel() {
    return false;
}

bool ciUIWidget::isModal() {
    return modal;
}

void ciUIWidget::setModal(bool _modal) {
    modal = _modal;
    if(parent != nullptr) {
        if(modal) {
            parent->addModalWidget(this);
        }
        else {
            parent->removeModalWidget(this);
        }
    }
}

void ciUIWidget::addModalWidget(ciUIWidget *widget) {
    if(parent != nullptr) {
        parent->addModalWidget(widget);
    }
}

void ciUIWidget::removeModalWidget(ciUIWidget *widget) {
    if(parent != nullptr) {
        parent->removeModalWidget(widget);
    }
}

void ciUIWidget::addEmbeddedWidget(ciUIWidget *widget) {
    widget->setEmbedded(true);
    embeddedWidgets.push_back(widget);
}

int ciUIWidget::getEmbeddedWidgetsSize() {
    return embeddedWidgets.size();
}

ciUIWidget *ciUIWidget::getEmbeddedWidget(int index) {
    return embeddedWidgets[index%embeddedWidgets.size()];
}

void ciUIWidget::clearEmbeddedWidgets() {
    embeddedWidgets.clear();        //does not deallocate widgets, just deletes the pointers and sets the size to zero
}

ciUIWidget *ciUIWidget::getCanvasParent() {
    bool notFoundParentCanvas = true;
    ciUIWidget *parent = this->getParent();
    if(parent != nullptr) {
        while (notFoundParentCanvas) {
            int _kind = parent->getKind();
            if( _kind == CI_UI_WIDGET_CANVAS || _kind == CI_UI_WIDGET_SCROLLABLECANVAS || _kind == CI_UI_WIDGET_SUPERCANVAS || _kind  ==CI_UI_WIDGET_TABBAR) {
                notFoundParentCanvas = false;
                return parent;
            }
            else {
                parent = parent->getParent();
                if(parent == nullptr) {
                    return nullptr; 
                }
            }
        }
    }
    else
    {
        int _kind = getKind();
        if( _kind == CI_UI_WIDGET_CANVAS || _kind == CI_UI_WIDGET_SCROLLABLECANVAS || _kind == CI_UI_WIDGET_SUPERCANVAS || _kind == CI_UI_WIDGET_TABBAR) {
            return this;
        }
    }
    return nullptr;
}

bool ciUIWidget::hasState()
{
    return false;
}

bool ciUIWidget::getIsBindedToKey(int key)
{
    std::map<int,bool>::iterator it = keyBindings.find(key);
    if(it != keyBindings.end() && it->second)
    {
        return true;
    }
    return false;
}

ciUIWidget* ciUIWidget::bindToKey(int key)
{
    keyBindings[key] = true;
    return this; 
}

ciUIWidget* ciUIWidget::unbindToKey(int key)
{
    keyBindings[key] = false;
    return this;
}

ciUIWidget* ciUIWidget::unbindAllKeys()
{
    keyBindings.clear();
    return this; 
}

#ifndef CI_UI_NO_XML

void ciUIWidget::saveState(ofxXmlSettings *XML)
{
    
}

void ciUIWidget::loadState(ofxXmlSettings *XML)
{
    
}

#endif
