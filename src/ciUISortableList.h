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

#include <vector>
#include <string>
#include "ciUIButton.h"
class ciUIDraggableLabelButton; 

class ciUISortableList : public ciUIButton
{
public:
    ciUISortableList(const std::string &_name, const std::vector<std::string> &items, float w = 0, float h = 0, float x = 0, float y = 0, int _size = CI_UI_FONT_MEDIUM, int _itemHeight = 30);
    void init(const std::string &_name, const std::vector<std::string> &items, float w = 0, float x = 0, float y = 0, int _size = CI_UI_FONT_MEDIUM, int _itemHeight = 30);
    const std::vector<ciUIDraggableLabelButton*> &getListItems();
    void reshuffle(const std::vector<std::string> &ordering);// reshuffle based on saved ordering
    void swapListItems(int swapA, int swapB);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
protected:
    void initDragableElements(const std::vector<std::string> &items, int _size);// build draggable widgets for the sortable items
    bool isInSwapZone(ciUIDraggableLabelButton* swapCandidate);// the "swapZone" is the area that extends from adjacent elements, in which the active widget can be bumped up or down the list
    void goingUp();// what to do if the active widget is getting bumped up the list order
    void goingDown();// what to do if the active widget is getting bumped down the list order
    void refreshPositions();// if the ordering changes - reflect it visually
    ciUIDraggableLabelButton* getActiveWidget(int x, int y);

    std::vector<ciUIDraggableLabelButton*> listItems;
    bool autoSize;
    int itemHeight;
    int activeWidgetIndex;
    int saveY;
    int lastActiveY;
    ciUIDraggableLabelButton* activeWidget;
};
