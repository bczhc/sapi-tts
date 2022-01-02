#include "./tts.h"

int main() {
    struct TTS tts;
    tts_init(&tts);

    ISpVoice *pVoice = tts_get_handler(&tts);
    pVoice->lpVtbl->SetPriority(pVoice, SPVPRI_OVER);

    tts_speak(&tts, "a bottle of water");
    return 0;
}