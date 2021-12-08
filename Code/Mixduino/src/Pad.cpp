#include "Pad.hpp"  
#include "constans.h"
#include "np_conf.h"

namespace MD
{

  Pad::Pad(Button* padBtns, ButtonMode* mode)
    : m_padBtns{padBtns},
      m_mode{mode}
  {

  }

  void Pad::changeMode() 
  {
      switch (m_padMode)
      {
      case PadMode::HOTCUE_MODE :
        m_firstMidiNumber = kLoopModeNumber;
        setAllTo(kLoopModeColor);
        m_padMode = PadMode::LOOP_MODE;
          break;

      case PadMode::LOOP_MODE :
        m_firstMidiNumber = kFXModeNumber;
        setAllTo(kFXModeColor);
        m_padMode = PadMode::FX_MODE;
          break;
      
      case PadMode::FX_MODE :
          m_firstMidiNumber = kHotcueModeNumber;
          setHotCueColors();
          m_padMode = PadMode::HOTCUE_MODE;
          break;
      }
  }

  void Pad::read(inMidip_t p) 
  {
      m_mode->read(this);
      for (uint8_t i = 0; i < kTPadButtons; i++)
      {
        p.midiNumber = i + m_firstMidiNumber;
        m_padBtns[i].read(p);
      }
      
  }

  void Pad::setHotCueColor(uint8_t pos, uint8_t value)
  {
    m_hotcues[pos] = value;
    if (m_padMode == PadMode::HOTCUE_MODE)
    {
        setHotCueColors();
    }
  }

  void Pad::setTo(uint8_t position, uint8_t value)
  {
    m_padBtns[position].setTo(value);
  }


  void Pad::setHotCueColors() 
  {
    for (uint8_t i = 0; i < kTPadButtons; i++)
    {
        setTo(i, m_hotcues[i]);
    }
    m_mode->setTo(m_outPos[kTPadButtons], kBlueColor);
  }
    
  void Pad::setAllTo(uint8_t value)
  {
    for (auto i = 0; i < kTPadButtons; i++)
    {
        m_padBtns[i].setTo(m_outPos[i], value);
    }
    m_mode->setTo(m_outPos[kTPadButtons], value);
  }
} // namespace MD

