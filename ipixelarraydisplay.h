#ifndef __IPIXELARRAYDISPLAY_H__
#define __IPIXELARRAYDISPLAY_H__

#include <stddef.h>

class IPixelArrayDisplay
{
public:
    virtual size_t getHeight() const = 0;
    virtual size_t getWidth() const = 0;
    virtual bool getPixelAt(size_t x, size_t y) const = 0;
};


#endif // __IPIXELARRAYDISPLAY_H__
