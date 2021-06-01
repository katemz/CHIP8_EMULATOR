#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

#include <stddef.h>

class IDisplayable
{
public:
    virtual size_t getHeight() const = 0;
    virtual size_t getWidth() const = 0;
    virtual bool getPixelAt(size_t x, size_t y) const = 0;
};


#endif // IDISPLAYABLE_H
