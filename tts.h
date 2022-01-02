#ifndef SAPI_TTS_TTS_H
#define SAPI_TTS_TTS_H

#include "./defs.h"
#include <stdio.h>
#include "./sapi.h"
#include "./utf8.h"

struct TTS {
    ISpVoice *pVoice;
};

int tts_init(struct TTS *tts);

void tts_release(struct TTS* tts);

void tts_speak(struct TTS *tts, const char* text);

#endif //SAPI_TTS_TTS_H
