#ifndef IEMULATOR_H
#define IEMULATOR_H

#include "idisplayable.h"
#include "ihaskeyboard.h"
#include "ihasloadablerom.h"

class IEmulator : public IDisplayable,
        public IHasKeyboard,
        public IHasLoadableROM
{
public:
    virtual void cycle() = 0;
};

#endif // IEMULATOR_H
