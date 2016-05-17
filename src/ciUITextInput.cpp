
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

#include "ciUITextInput.h"
#include "ciUI.h"

ciUITextInput::ciUITextInput(const std::string &_name, const std::string &_textstring, float w, float h, float x, float y, int _size) : ciUIWidgetWithLabel()
{
    init(_name, _textstring, w, h, x, y, _size);
}

void ciUITextInput::init(const std::string &_name, const std::string &_textstring, float w, float h, float x, float y, int _size)
{
    initRect(x,y,w,h);
    name = _name;
    kind = CI_UI_WIDGET_TEXTINPUT;
    textstring = _textstring;
    defaultstring = _textstring;
    displaystring = _textstring;
    
    clicked = false;                                            //the widget's value
    autoclear = true;
    triggerOnClick = true;
    label = new ciUILabel(w-padding*2.0, (name+" LABEL"), _size);
    addEmbeddedWidget(label);
    
    inputTriggerType = CI_UI_TEXTINPUT_ON_FOCUS;
    cursorWidth = 0; spaceOffset = 0;
    theta = 0;
    autoUnfocus = true;
    onlyNumericInput = false;
    cursorPosition = 0;
    firstVisibleCharacterIndex = 0;
}

void ciUITextInput::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ciUITextInput::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ciUITextInput::drawFill()
{
    if(draw_fill)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill);
        rect->draw(true);
    }
    if(clicked)
    {
        //ofNoFill();
        {
            ci::gl::ScopedColor scopedColor(color_outline_highlight);
            rect->draw(false);
        }
        float h = label->getRect()->getHeight();
        
        float ph = rect->getHeight();
        label->getRect()->setY(ph/2.0 - h/2.0);
        
        //ciUIFill();
        {
            ciUIColor color(label->getColorFillHighlight());
            color.a = 255.0f * std::fabs(cos(theta));
            ci::gl::ScopedColor scopedColor(color);
            theta +=0.05;
            
            int displayCursorPosition = cursorPosition - firstVisibleCharacterIndex;
            std::string displayStringBeforeCursor = displaystring.substr(0, displayCursorPosition);
            spaceOffset = label->getStringWidth(displayStringBeforeCursor);
            
            float x = label->getRect()->getX()+spaceOffset;
            float y = label->getRect()->getY()-padding;
            float t = label->getRect()->getHeight()+padding*2.0;
            ciUIDrawCorneredRect(x, y, cursorWidth, t, true);
        }
    }
    
    if(textstring.size() == 0 && !clicked)
    {
        //ciUIFill();
        ci::gl::ScopedColor scopedColor(color_fill);
        label->drawString(rect->getX()+defaultX, rect->getY()+defaultY, defaultstring);
    }
}

void ciUITextInput::mouseMoved(int x, int y )
{
    if(rect->inside(x, y))
    {
        state = CI_UI_STATE_OVER;
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUITextInput::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = CI_UI_STATE_DOWN;
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    stateChange();
}

void ciUITextInput::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        if(state == CI_UI_STATE_OVER)
        {
            clicked = true;
            theta = 0;
            hit = true;
        }
#ifdef CI_UI_TARGET_TOUCH
        clicked = true;
        theta = 0;
        hit = true;
#endif
        cursorPosition = label->getLabel().length();
        
        state = CI_UI_STATE_DOWN;
        inputTriggerType = CI_UI_TEXTINPUT_ON_FOCUS;
        
        if(triggerOnClick)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
        if(clicked)
        {
            unClick();
        }
    }
    stateChange();
}

void ciUITextInput::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef CI_UI_TARGET_TOUCH
        state = CI_UI_STATE_NORMAL;
#else
        state = CI_UI_STATE_OVER;
#endif
        //			inputTriggerType = CI_UI_TEXTINPUT_ON_UNFOCUS;
        //			triggerEvent(this);
    }
    else
    {
        state = CI_UI_STATE_NORMAL;
    }
    hit = false;
    stateChange();
}

void ciUITextInput::keyPressed(int key)
{
    if(clicked)
    {
        switch (key)
        {
            case ci::app::KeyEvent::KEY_BACKSPACE:
                if (textstring.size() > 0 && cursorPosition > 0)
                {
                    cursorPosition--;
                    textstring.erase(cursorPosition, 1);
                    
                    // when we're deleting the first visible character, shift the string to the right
                    if(firstVisibleCharacterIndex == cursorPosition)
                        firstVisibleCharacterIndex = 0;
                    recalculateDisplayString();
                }
                break;
                
            case ci::app::KeyEvent::KEY_DELETE:
                if (textstring.size() > 0 && cursorPosition < textstring.length())
                {
                    textstring.erase(cursorPosition, 1);
                    recalculateDisplayString();
                }
                break;
                
            case ci::app::KeyEvent::KEY_RETURN:
                
                inputTriggerType = CI_UI_TEXTINPUT_ON_ENTER;
                if(autoUnfocus)
                {
                    clicked = false;
                }

                triggerEvent(this);
                if(autoclear)
                {
                    cursorPosition = 0;
                    textstring.clear();
                    recalculateDisplayString();
                }
                break;
                
            case ci::app::KeyEvent::KEY_RIGHT:
            case ci::app::KeyEvent::KEY_DOWN:
                if(cursorPosition < textstring.length())
                {
                    cursorPosition++;
                    recalculateDisplayString();
                }
                break;
                
            case ci::app::KeyEvent::KEY_LEFT:
            case ci::app::KeyEvent::KEY_UP:
                if(cursorPosition > 0)
                {
                    cursorPosition--;
                    recalculateDisplayString();
                }
                break;
                
#if (OF_VERSION_MINOR > 7)
            case ci::app::KeyEvent::KEY_TAB:
            case ci::app::KeyEvent::KEY_COMMAND:
            case ci::app::KeyEvent::KEY_CONTROL:
            case ci::app::KeyEvent::KEY_LSHIFT:
            case ci::app::KeyEvent::KEY_RSHIFT:
            case ci::app::KeyEvent::KEY_LEFT_CONTROL:
            case ci::app::KeyEvent::KEY_RIGHT_CONTROL:
            case ci::app::KeyEvent::KEY_LEFT_ALT:
            case ci::app::KeyEvent::KEY_RIGHT_ALT:
            case ci::app::KeyEvent::KEY_LEFT_SUPER:
            case ci::app::KeyEvent::KEY_RIGHT_SUPER:
#endif
            case ci::app::KeyEvent::KEY_F1:
            case ci::app::KeyEvent::KEY_F2:
            case ci::app::KeyEvent::KEY_F3:
            case ci::app::KeyEvent::KEY_F4:
            case ci::app::KeyEvent::KEY_F5:
            case ci::app::KeyEvent::KEY_F6:
            case ci::app::KeyEvent::KEY_F7:
            case ci::app::KeyEvent::KEY_F8:
            case ci::app::KeyEvent::KEY_F9:
            case ci::app::KeyEvent::KEY_F10:
            case ci::app::KeyEvent::KEY_F11:
            case ci::app::KeyEvent::KEY_F12:
            //case ci::app::KeyEvent::KEY_PAGE_UP:
            //case ci::app::KeyEvent::KEY_PAGE_DOWN:
            case ci::app::KeyEvent::KEY_HOME:
            case ci::app::KeyEvent::KEY_END:
            case ci::app::KeyEvent::KEY_INSERT:
            case ci::app::KeyEvent::KEY_LALT:
            case ci::app::KeyEvent::KEY_RALT:
            case ci::app::KeyEvent::KEY_LSHIFT:
            case ci::app::KeyEvent::KEY_RSHIFT:
                break;
                
            default:
            {
                if (onlyNumericInput)
                {
                    if((!isdigit(key) && key != 46  && key != 45) || (key == 45 && cursorPosition != 0))
                    {
                        // The key pressed is not numeric (0-9) or the '.' character.
                        // Or the '-' character at the beginning of the string.
                        break;
                    }
                }
                
                textstring.insert(cursorPosition, 1, key);
                cursorPosition++;
                recalculateDisplayString();
            }
                break;
        }
    }
}

void ciUITextInput::unClick()
{
    if(clicked)
    {
        clicked = false;
        inputTriggerType = CI_UI_TEXTINPUT_ON_UNFOCUS;
        triggerEvent(this);
    }
}
void ciUITextInput::stateChange()
{
    switch (state) {
        case CI_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case CI_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case CI_UI_STATE_DOWN:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case CI_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        default:
            break;
    }
}

bool ciUITextInput::isClicked()
{
    return clicked;
}

const std::string &ciUITextInput::getTextString()
{
    return textstring;
}

int ciUITextInput::getIntValue()
{
    if (!onlyNumericInput)
        return  0;
        
    return atoi(textstring.c_str());
}

float ciUITextInput::getFloatValue()
{
    if (!onlyNumericInput)
        return  0;
    
    return atof(textstring.c_str());
}

void ciUITextInput::setInputTriggerType(int _triggerType)
{
    inputTriggerType = _triggerType;
}

int ciUITextInput::getInputTriggerType()
{
    return inputTriggerType;
}

void ciUITextInput::setTextString(const std::string &s)
{
    textstring = "";
    std::string temp = "";
    
    int length = s.length();
    
    if(length > 0)
    {
        for(int i = 0; i < length; i++)
        {
            temp+=s.at(i);
            float newWidth = label->getStringWidth(temp);
            
            if(newWidth < rect->getWidth()-padding*2.0)
            {
                textstring+=s.at(i);
                label->setLabel(textstring);
            }
        }
    }
    else
    {
        textstring = s;
        label->setLabel(textstring);
    }
    displaystring = textstring;
    cursorPosition = textstring.length();
}

void ciUITextInput::setParent(ciUIWidget *_parent)
{
    parent = _parent;
    if(rect->getHeight() == 0 || rect->getHeight() < label->getPaddingRect()->getHeight()+padding*2.0)
    {
        rect->setHeight(label->getPaddingRect()->getHeight()+padding*2.0);
    }
    label->setLabel(textstring);
    ciUIRectangle *labelrect = label->getRect();
    float h = labelrect->getHeight();
    float ph = rect->getHeight();
    
    labelrect->setY(ph/2.0 - h/2.0);
    labelrect->setX(padding*2.0);
    defaultY = labelrect->getY(false)+labelrect->getHeight();
    defaultX = labelrect->getX(false);
    
    cursorWidth = label->getStringWidth(".");
    while(label->getStringWidth(textstring) > rect->getWidth()-padding*2.0)
    {
        std::string::iterator it;
        it=textstring.begin();
        textstring.erase (it);
    }
    
    defaultstring = textstring;
    displaystring = textstring;
    setTextString(textstring);
    calculatePaddingRect();
}

void ciUITextInput::setAutoClear(bool _autoclear)
{
    autoclear = _autoclear;
}

void ciUITextInput::setFocus(bool _focus)
{
    if(_focus)
    {
        cursorPosition = 0;
        state = CI_UI_STATE_DOWN;
        inputTriggerType = CI_UI_TEXTINPUT_ON_FOCUS;
        clicked = true;
        stateChange();
        triggerEvent(this);
    }
    else
    {
        cursorPosition = textstring.length();
        stateChange();
        unClick();
    }
}

bool ciUITextInput::isFocused()
{
    return isClicked();
}

void ciUITextInput::setAutoUnfocus(bool _autoUnfocus)
{
    autoUnfocus = _autoUnfocus;
}

void ciUITextInput::setOnlyNumericInput(bool _onlyNumericInput)
{
    onlyNumericInput = _onlyNumericInput;
}

void ciUITextInput::setTriggerOnClick(bool _triggerOnClick)
{
    triggerOnClick = _triggerOnClick;
}

void ciUITextInput::recalculateDisplayString()
{
    // the maximum width of the displaystring
    float maxWidth = rect->getWidth()-padding*2.0;
    
    displaystring = textstring;
    std::string stringBeforeCursor = displaystring.substr(0, cursorPosition);
    std::string stringBeforeLabel =  displaystring.substr(0, firstVisibleCharacterIndex);
    
    // if the cursoroffset - length of the (invisible) string before the label < 0, we have to shift our string to the left to get our cursor in the label
    while(label->getStringWidth(stringBeforeCursor) - label->getStringWidth(stringBeforeLabel) < 0){
        firstVisibleCharacterIndex --;
        stringBeforeLabel =  displaystring.substr(0, firstVisibleCharacterIndex);
    }
    
    // if the cursoroffset - length of the (invisible) string before the label is > maximum width, we have to shift to the right
    while(label->getStringWidth(stringBeforeCursor) - label->getStringWidth(stringBeforeLabel) > maxWidth){
        firstVisibleCharacterIndex ++;
        stringBeforeLabel =  displaystring.substr(0, firstVisibleCharacterIndex);
    }
    
    // we now know how long the string before the label should be, so trim it off
    displaystring = displaystring.substr(std::min<size_t>(firstVisibleCharacterIndex, displaystring.length()));
    
    // trim off the end of the string until it fits
    while(label->getStringWidth(displaystring) > maxWidth && displaystring.length() > 0)
    {
        displaystring = displaystring.substr(0, displaystring.size()-1);
    }
    
    label->setLabel(displaystring);
}

#ifndef CI_UI_NO_XML

void ciUITextInput::saveState(ofxXmlSettings *XML)
{
    XML->setValue("Value", getTextString(), 0);    
}

void ciUITextInput::loadState(ofxXmlSettings *XML)
{
    setTextString(XML->getValue("Value", getTextString(), 0));
    setInputTriggerType(CI_UI_TEXTINPUT_ON_LOAD);
}

#endif
