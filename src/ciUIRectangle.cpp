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

#include "ciUIRectangle.h"

ciUIRectangle::ciUIRectangle()
{
    x = y = width = height = halfheight = halfwidth = 0.0f;
    setParent(nullptr);
}

ciUIRectangle::ciUIRectangle(float _x, float _y, float _w, float _h)
{
    x = _x;
    y = _y;
    width = _w;
    halfwidth = width*.5;
    height = _h;
    halfheight = height*.5;
    setParent(nullptr);
}

ciUIRectangle::ciUIRectangle(ciUIRectangle const & r)
{
    x = r.x;
    y = r.y;
    width = r.width;
    halfwidth = width*.5;
    height = r.height;
    halfheight = height*.5;
    setParent(nullptr);
}

void ciUIRectangle::set(float px, float py, float w, float h)
{
    x		= px;
    y		= py;
    width	= w;
    height	= h;
    halfwidth = width*.5;
    halfheight = height*.5;
}

void ciUIRectangle::setX(float px)
{
    x = px;
}

void ciUIRectangle::setY(float py)
{
    y = py;
}

void ciUIRectangle::setParent(ciUIRectangle *_parent)
{
    parent = _parent;
}

void ciUIRectangle::setHeight(float _height)
{
    height = _height;
    halfheight = height*.5;
}

void ciUIRectangle::setWidth(float _width)
{
    width = _width;
    halfwidth = width*.5;
}

float ciUIRectangle::getMinX() const
{
    return std::min(x, x + width);  // - width
}

float ciUIRectangle::getMaxX() const
{
    return std::max(x, x + width);  // - width
}

float ciUIRectangle::getMinY() const
{
    return std::min(y, y + height);  // - height
}

float ciUIRectangle::getMaxY() const
{
    return std::max(y, y + height);  // - height
}

bool ciUIRectangle::inside(const ci::vec2 &p)
{
    if(parent != nullptr)
    {
        return insideParent(p.x, p.y);
    }
    else
    {
        return insideChild(p.x, p.y);
    }
}

bool ciUIRectangle::inside(float px, float py)
{
    if(parent != nullptr)
    {
        return insideParent(px,py);
    }
    else
    {
        return insideChild(px,py);
    }
}

bool ciUIRectangle::insideChild(float px, float py)
{
    if( px > x && py > y && px < x + width && py < y + height ){
        return true;
    }
    return false;
    
}

bool ciUIRectangle::insideParent(float px, float py)
{
    if( px > (x+parent->getX()) && py > (y+parent->getY()) && px < (x+parent->getX()) + width && py < (y+parent->getY()) + height )
    {
        return true;
    }
    return false;
}

ciUIVec2f ciUIRectangle::percentInside(float px, float py)				//Assumes your already inside rect
{
    if(parent != nullptr)
    {
        return percentInsideParent(px,py);
    }
    else
    {
        return percentInsideChild(px,py);
    }
}

ciUIVec2f ciUIRectangle::percentInsideChild(float px, float py)
{
    return ciUIVec2f((px-x)/(width), (py-y)/(height));
}

ciUIVec2f ciUIRectangle::percentInsideParent(float px, float py)
{
    return ciUIVec2f((px-(x+parent->getX()))/(width), (py-(y+parent->getY()))/(height));
}

void ciUIRectangle::draw(bool doFill)
{
    ci::Rectf rect;
    if(parent != nullptr)
    {
        float x1 = parent->getX() + x;
        float y1 = parent->getY() + y;
        rect.set(x1, y1, x1 + width, y1 + height);
    }
    else
    {
        rect.set(x, y, x + width, y + height);
    }
    if(doFill)
    {
        ci::gl::drawStrokedRect(rect);
    }
    else
    {
        ci::gl::drawSolidRect(rect);
    }
}

float ciUIRectangle::getX(bool recursive)
{
    if(parent != nullptr && recursive)
    {
        return (x+parent->getX());
    }
    else
    {
        return x;
    }
}

float ciUIRectangle::getY(bool recursive)
{
    if(parent != nullptr && recursive)
    {
        return (y+parent->getY());
    }
    else
    {
        return y;
    }
}

float ciUIRectangle::getWidth()
{
    return width;
}

float ciUIRectangle::getHeight()
{
    return height;
}

float ciUIRectangle::getHalfWidth()
{
    return halfwidth;
}

float ciUIRectangle::getHalfHeight()
{
    return halfheight;
}

float ciUIRectangle::getRelativeMinX()
{
    return std::min(getX(), getX() + getWidth());    // - width
}

float ciUIRectangle::getRelativeMinY()
{
    return std::min(getY(), getY() + getHeight());   // - height
}

float ciUIRectangle::getRelativeMaxX()
{
    return std::max(getX(), getX() + getWidth());    // - width
}

float ciUIRectangle::getRelativeMaxY()
{
    return std::max(getY(), getY() + getHeight());   // - height
}

bool ciUIRectangle::rIntersects(const ciUIRectangle& rect)
{
    return (getRelativeMinX() < rect.getMaxX() && getRelativeMaxX() > rect.getMinX() &&
            getRelativeMinY() < rect.getMaxY() && getRelativeMaxY() > rect.getMinY());
}

bool ciUIRectangle::rInside(const ciUIRectangle& rect)
{
    return (getRelativeMinX() > rect.getMinX() && getRelativeMaxX() < rect.getMaxX() &&
            getRelativeMinY() > rect.getMinY() && getRelativeMaxY() < rect.getMaxY());
}

ci::Rectf ciUIRectangle::getRectf() const
{
    return ci::Rectf(x, y, x + width, y + height);
}
