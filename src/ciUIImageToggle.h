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
#include "cinder/ImageIo.h"
#include "ciUIToggle.h"
#include "ciUIDefines.h"

class ciUIImageToggle : public ciUIToggle
{
public:
    ciUIImageToggle(float x, float y, float w, float h, bool _value, const std::string &_pathURL, const std::string &_name, int _size = CI_UI_FONT_MEDIUM);
    ciUIImageToggle(float w, float h, bool _value, const std::string &_pathURL, const std::string &_name, int _size = CI_UI_FONT_MEDIUM);
    ciUIImageToggle(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size = CI_UI_FONT_MEDIUM);
    ciUIImageToggle(float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size = CI_UI_FONT_MEDIUM);
    void init(float x, float y, float w, float h, bool *_value, const std::string &_pathURL, const std::string &_name, int _size = CI_UI_FONT_SMALL);
    virtual ~ciUIImageToggle();
    virtual void drawBack() override;
    virtual void drawFill() override;
    virtual void drawFillHighlight() override;
    virtual void drawOutlineHighlight() override;
    virtual const ci::SurfaceRef &getImage() const;
    virtual void setImage(const ci::SurfaceRef &_img);
                     
protected:
    ci::SurfaceRef img;
    ci::gl::Texture2dRef tex;
    bool bChangedImage;
}; 
