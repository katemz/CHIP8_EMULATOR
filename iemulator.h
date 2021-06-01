#ifndef IEMULATOR_H
#define IEMULATOR_H

#include "idisplayable.h"
#include "ihaskeyboard.h"
#include "ihasloadablerom.h"

class IEmulator : public IDisplayable,
        public IHasKeyboard,
        public IHasLoadableROM
{
};

#endif // IEMULATOR_H
