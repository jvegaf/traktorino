#include "FuncMode.h"  



FuncMode::FuncMode(ModeInput *input, OutputBase *output)
	: Func(input, output)
{
    _in = input;
	_dMode = deckMode::MODE_HOTCUE;
    _modeNote = 0;
    _modeColor = HOTCUE_MODE_COLOR;
}

void FuncMode::read() {
	boolean triggered = _in->read();
    if (triggered)
    {
        incrementMode();
        _output->setTo(getModeColor());
        _disposed = false;
    }
}

deckMode FuncMode::getMode() {
	return _dMode;
}

uint8_t FuncMode::getModeNote() {
	return _modeNote;
}

uint8_t FuncMode::getModeColor() {
	return _modeColor;
}

uint8_t FuncMode::getSelectorModeColor() {
	if (_dMode == deckMode::MODE_HOTCUE){
        return 1;
    }
    return _modeColor;
}

boolean FuncMode::isDisposed() {
	return _disposed;
}

void FuncMode::dispose() {
	_disposed = true;
}

void FuncMode::incrementMode()
{
    switch (_dMode)
    {
    case deckMode::MODE_HOTCUE:
        _dMode = deckMode::MODE_LOOP;
        _modeColor = LOOP_MODE_COLOR;
        _modeNote = 8;
        break;

    case deckMode::MODE_LOOP:
        _dMode = deckMode::MODE_FX;
        _modeColor = FX_MODE_COLOR;
        _modeNote = 16;
        break;

    case deckMode::MODE_FX:
        _dMode = deckMode::MODE_HOTCUE;
        _modeColor = HOTCUE_MODE_COLOR;
        _modeNote = 0;
        break;

    default:
        break;
    }
}

