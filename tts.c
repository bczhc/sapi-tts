#include "tts.h"
#include "./lib.h"
#include <pthread.h>

void tts_init(struct TTS *tts) {
    if (FAILED(CoInitialize(NULL))) {
        err_println("CoInitialize(...) failed");
        abort();
    }

    tts->pVoice = NULL;

    HRESULT hr = CoCreateInstance(&CLSID_SpVoice, NULL, CLSCTX_ALL, &IID_ISpVoice, (void **) &tts->pVoice);
    if (FAILED(hr)) {
        err_println("CoCreateInstance(...) failed");
        abort();
    }
}

void tts_release(struct TTS *tts) {
    tts->pVoice->lpVtbl->Release(tts->pVoice);
    CoUninitialize();
}

void tts_speak(struct TTS *tts, const char *text) {
    struct UTF16String utf16String = utf8_to_utf16(text);

    ISpVoice *pVoice = tts->pVoice;
    struct ISpVoiceVtbl *tbl = pVoice->lpVtbl;
    tbl->Speak(pVoice, utf16String.data, SPF_DEFAULT, NULL);

    utf16_release(&utf16String);
}

void tts_set_rate(struct TTS *tts, u32 rate) {
    tts->pVoice->lpVtbl->SetRate(tts->pVoice, (long) rate);
}

ISpVoice *tts_get_handler(struct TTS *tts) {
    return tts->pVoice;
}
