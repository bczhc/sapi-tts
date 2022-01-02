#include "tts.h"
#include "./lib.h"

int tts_init(struct TTS *tts) {
    if (FAILED(CoInitialize(NULL))) {
        err_println("CoInitialize(...) failed");
        return 1;
    }

    tts->pVoice = NULL;

    HRESULT hr = CoCreateInstance(&CLSID_SpVoice, NULL, CLSCTX_ALL, &IID_ISpVoice, (void **) &tts->pVoice);
    if (FAILED(hr)) {
        err_println("CoCreateInstance(...) failed");
        return 1;
    }

    return 0;
}

void tts_release(struct TTS *tts) {
    tts->pVoice->lpVtbl->Release(tts->pVoice);
    CoUninitialize();
}

void tts_speak(struct TTS *tts, const char *text) {
    struct UTF16String utf16String = utf8_to_utf16(text);
    enum SPEAKFLAGS speakFlags = SPF_DEFAULT;

    ISpVoice *pVoice = tts->pVoice;
    pVoice->lpVtbl->Speak(pVoice, utf16String.data, speakFlags, NULL);

    utf16_release(&utf16String);
}

