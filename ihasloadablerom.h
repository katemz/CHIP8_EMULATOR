#ifndef IHASLOADABLEROM_H
#define IHASLOADABLEROM_H

#include <string>

class IHasLoadableROM
{
public:
    virtual void loadROM(const std::string& filePath) = 0;
};

#endif // IHASLOADABLEROM_H
