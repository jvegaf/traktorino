#include "FuncFactory.h"

void FuncFactory::begin(NPKit *npkit, void (*funcOn)(uint8_t, uint8_t, uint8_t), void (*funcOff)(uint8_t, uint8_t, uint8_t))
{
    _npkit = npkit;
    fOn = funcOn;
    fOff = funcOff;
    _shfLeft = new Shifter(FBL_SIG, FBL_LATCH, SRCLK, 1);
    _shfRight = new Shifter(FBR_SIG, FBR_LATCH, SRCLK, 1);
    _funcModeLeft = createLeftModeFunc();
    _funcModeRight = createRightModeFunc();

    Input** blindIns = createBlindInputs();
    FuncBase* _bFuncs = createBlindFuncs(blindIns, IN_ONLY_CH, T_MIDI_BLIND_SET);
    _blindFuncs = new FuncsBlind(_bFuncs, T_MIDI_BLIND_SET);
    
    Input** ins = createInputs();
    Output** outs = createOutputs();
    Func* _fncs = createFuncs(ins, outs, IN_OUT_CH, T_MIDI_SET);
    _funcs = new Funcs(_fncs, T_MIDI_SET);
    
    Input** leftInPads = createInputPads(MUXPIN_BUNDLE, LEFT_SWMUX_SIG, SW_PADL_BUNDLE, fOn, fOff);
    Output** leftOutPads = createOutputPads(_npkit, PIXLS_PAD_L);
    FuncPad* _leftFuncPads = createFuncPads(leftInPads, leftOutPads, PAD_DECK_A_CH, T_DECK_PADS);
    _leftPad = new Pad(_leftFuncPads);
    
    Input** rightInPads = createInputPads(MUXPIN_BUNDLE, RIGHT_SWMUX_SIG, SW_PADR_BUNDLE, fOn, fOff);
    Output** rightOutPads = createOutputPads(_npkit, PIXLS_PAD_R);
    FuncPad* _rightFuncPads = createFuncPads(rightInPads, rightOutPads, PAD_DECK_B_CH, T_DECK_PADS);
    _rightPad = new Pad(_rightFuncPads);

}

FuncMode *FuncFactory::createLeftModeFunc()
{
    Output *modeLOut = new FBPixel(_npkit, NP_MODE_L);
    return new FuncMode(MUXPIN_BUNDLE, LEFT_SWMUX_SIG, SWMODE_L, modeLOut);
}

FuncMode *FuncFactory::createRightModeFunc()
{
    Output *modeROut = new FBPixel(_npkit, NP_MODE_R);
    return new FuncMode(MUXPIN_BUNDLE, RIGHT_SWMUX_SIG, SWMODE_R, modeROut);
}

FuncBase *FuncFactory::createBlindFuncs(Input **inAggr, uint8_t midiCh, uint8_t t_funcs)
{
    FuncBase *funcSet = new FuncBase[t_funcs];
    for (uint8_t i = 0; i < t_funcs; i++)
    {
        funcSet[i] = FuncBase(inAggr[i], midiCh, i );
    }
    return funcSet;
}

Func *FuncFactory::createFuncs(Input **inAggr, Output **outAggr, uint8_t midiCh, uint8_t t_funcs)
{
    Func *funcSet = new Func[t_funcs];
    for (uint8_t i = 0; i < t_funcs; i++)
    {
        funcSet[i] = Func(inAggr[i], outAggr[i], midiCh, i );
    }
    return funcSet;
}

Input **FuncFactory::createBlindInputs()
{
    Input** res = new Input*[T_MIDI_BLIND_SET];
    res[0] = new MuxInput(MUXPIN_BUNDLE, LEFT_SWMUX_SIG, SWSHIFT);
    res[1] = new ArduInput(SW_BROWSER_L);
    res[2] = new ArduInput(SW_BROWSER_R);
    res[3] = new ArduInput(SWBR_PREVIEW);
    res[4] = new ArduInput(SWBR_BACK);
    return res;
}

Input **FuncFactory::createInputs()
{
    Input **res = new Input*[T_MIDI_SET]; 
    res[0] = new MuxInput(MUXPIN_BUNDLE, RIGHT_SWMUX_SIG, SWDECK_SEL);
    res[1] = new MuxInput(MUXPIN_BUNDLE, LEFT_SWMUX_SIG, SWSYNC_L);
    res[2] = new MuxInput(MUXPIN_BUNDLE, RIGHT_SWMUX_SIG, SWSYNC_R);
    res[3] = new MuxInput(MUXPIN_BUNDLE, LEFT_SWMUX_SIG, SWPLAY_L);
    res[4] = new MuxInput(MUXPIN_BUNDLE, LEFT_SWMUX_SIG, SWCUE_L);
    res[5] = new MuxInput(MUXPIN_BUNDLE, LEFT_SWMUX_SIG, SWLOOP_L);
    res[6] = new MuxInput(MUXPIN_BUNDLE, RIGHT_SWMUX_SIG, SWPLAY_R);
    res[7] = new MuxInput(MUXPIN_BUNDLE, RIGHT_SWMUX_SIG, SWCUE_R);
    res[8] = new MuxInput(MUXPIN_BUNDLE, RIGHT_SWMUX_SIG, SWLOOP_R);
    res[9] = new MuxInput(MUXPIN_BUNDLE, LEFT_SWMUX_SIG, SWPCUEL1);
    res[10] = new MuxInput(MUXPIN_BUNDLE, LEFT_SWMUX_SIG, SWPCUEL2);
    res[11] = new MuxInput(MUXPIN_BUNDLE, RIGHT_SWMUX_SIG, SWPCUEL3);
    res[12] = new ArduInput(SWFXL_1);
    res[13] = new ArduInput(SWFXL_2);
    res[14] = new ArduInput(SWFXL_3);
    res[15] = new ArduInput(SWFXR_1);
    res[16] = new ArduInput(SWFXR_2);
    res[17] = new ArduInput(SWFXR_3);
    return res;
}

Output **FuncFactory::createOutputs()
{
    Output** res= new Output*[T_MIDI_SET];
    res[0] = new FBPixel(_npkit, NP_DECK_SEL);
    res[1] = new FBPixel(_npkit, NP_SYNC_L);
    res[2] = new FBPixel(_npkit, NP_SYNC_R);
    res[3] = new FBLed(_shfLeft, OUT_PLAY_L);
    res[4] = new FBLed(_shfLeft, OUT_CUE_L);
    res[5] = new FBLed(_shfLeft, OUT_LOOP_L);
    res[6] = new FBLed(_shfRight, OUT_PLAY_R);
    res[7] = new FBLed(_shfRight, OUT_CUE_R);
    res[8] = new FBLed(_shfRight, OUT_LOOP_R);
    res[9] = new FBLed(_shfLeft, OUT_PCUEL1);
    res[10] = new FBLed(_shfLeft, OUT_PCUEL2);
    res[11] = new FBLed(_shfRight, OUT_PCUEL3);
    res[12] = new FBLed(_shfLeft, OUT_FX1_L);
    res[13] = new FBLed(_shfLeft, OUT_FX2_L);
    res[14] = new FBLed(_shfLeft, OUT_FX3_L);
    res[15] = new FBLed(_shfRight, OUT_FX1_R);
    res[16] = new FBLed(_shfRight, OUT_FX2_R);
    res[17] = new FBLed(_shfRight, OUT_FX3_R);
    return res;
}

Output** FuncFactory::createOutputPads(NPKit *npk, const uint8_t *positions)
{
    Output **outPads = new Output*[T_DECK_PADS];
    for (uint8_t i = 0; i < T_DECK_PADS; i++)
    {
        FBPixel *pix = new FBPixel(npk, positions[i]);
        outPads[i] = pix;
    }
    return outPads;
}

Input **FuncFactory::createInputPads(const uint8_t *mxPinBundle, uint8_t sigPin, const uint8_t *positions, void (*funcOn)(uint8_t, uint8_t, uint8_t), void (*funcOff)(uint8_t, uint8_t, uint8_t))
{
    Input **muxInPads = new Input*[T_DECK_PADS];
    for (uint8_t i = 0; i < T_DECK_PADS; i++)
    {
        Input* inp = new MuxInput(mxPinBundle, sigPin, positions[i]);
        muxInPads[i] = inp;
    }
    return muxInPads;
}

FuncPad* FuncFactory::createFuncPads(Input **inAggr, Output **outAggr, uint8_t midiCh, uint8_t t_funcs)
{
    FuncPad* funcSet = new FuncPad[t_funcs];
    for (uint8_t i = 0; i < t_funcs; i++)
    {
        funcSet[i] = FuncPad(inAggr[i], outAggr[i], midiCh, i);
    }
    return funcSet;
}