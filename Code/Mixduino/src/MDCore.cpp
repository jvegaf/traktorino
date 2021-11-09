#include "MDCore.h"


void MDCore::initPins()
{
    for(uint8_t i=0;i < T_MUXPIN_BUNDLE;i++) {
        pinMode(MUXPIN_BUNDLE[i], OUTPUT);
    }
    for (uint8_t i = 0; i < T_ARD_SW_BUNDLE; i++)
    {
        pinMode(ARD_SW_BUNDLE[i], INPUT_PULLUP);
    }
}

void MDCore::vuChange(uint8_t number, uint8_t value)
{
    _vuSet[number].setLevel(value);
}

void MDCore::readDecksMode()
{
    _leftFuncMode->read();
    _rightFuncMode->read();
    checkDeckMode(_leftFuncMode, _leftPad);
    checkDeckMode(_rightFuncMode, _rightPad);
}

void MDCore::checkDeckMode(FuncMode *fm, Pad *p)
{
    if (!fm->isDisposed())
    {
        p->setNote(fm->getModeNote());
        p->setTo(fm->getModeColor());
        fm->dispose();
    }
}

void MDCore::handlePadNoteChange(State nState, FuncMode *deckMD, Pad *pad, uint8_t number, uint8_t value)
{
    if (deckMD->getMode() != deckMode::MODE_HOTCUE)
    {
        return;
    }

    if (nState == State::STATE_OFF)
    {
        pad->setTo(number, 0);
        return;
    }

    pad->setTo(number, value);
}
