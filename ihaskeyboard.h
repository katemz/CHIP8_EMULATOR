#ifndef IHASKEYBOARD_H
#define IHASKEYBOARD_H

class IHasKeyboard
{
public:
    virtual void keyPressed(char c) = 0;
    virtual void keyReleased(char c) = 0;
};

#endif // IHASKEYBOARD_H
