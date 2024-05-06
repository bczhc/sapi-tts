#ifndef SAPI_TTS_TTS_H
#define SAPI_TTS_TTS_H

// These two includes below are required, otherwise SAPI won't compile.
#include <windef.h>
#include <minwindef.h>
#include <sapi.h>
#include <iostream>

class TTS {
public:
    ISpVoice *pVoice;

    TTS();

    ~TTS();

    void speak(const std::string &text, DWORD flags = SPF_DEFAULT) const;

    void set_rate(LONG rate) const;

    void set_priority(SPVPRIORITY priority) const;
};

#endif //SAPI_TTS_TTS_H
