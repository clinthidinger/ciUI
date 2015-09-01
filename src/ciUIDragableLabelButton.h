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
#include "ciUILabelButton.h"

class ciUIDraggableLabelButton : public ciUILabelButton
{
public:
    ciUIDraggableLabelButton(const std::string &_name, bool _value, float w = 0, float h = 0, float x = 0, float y = 0, int _size = CI_UI_FONT_MEDIUM, bool _justifyLeft = false);
    ciUIDraggableLabelButton(const std::string &_name, bool *_value, float w = 0, float h = 0, float x = 0, float y = 0, int _size = CI_UI_FONT_MEDIUM, bool _justifyLeft = false);
    void init(const std::string &_name, bool *_value, float w, float h, float x = 0, float y = 0, int _size = CI_UI_FONT_MEDIUM, bool _justifyLeft = false);
    bool isDraggable();
    void setPos(int x , int y);// TODO easing
    int getMidY();//TODO this method mainly exists for the ofxSortableList class, not sure it belongs here
    void setSortID(const std::string &a_id);//TODO again, this is mainly for the ofxSortableList, maybe the ids should be modeled internally in ofxSortableList
    const std::string &getSortID();
    int getY();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    int saveX;
    int saveY;
    int posX;
    int posY;
    bool onPressed;
    bool isDraggedOut;
    std::string id;
};
