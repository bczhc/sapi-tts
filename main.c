#include <pthread.h>

#include "./tts.h"
#include <unistd.h>

struct TTS tts;

void overlap_speak(const char *text) {
    tts_set_rate(&tts, 2);
    tts_set_priority(&tts, SPVPRI_OVER);

    tts_speak_async(&tts, text);
    // TODO: leak
    // tts_release(&tts);
}

int main(int argc, char **argv) {
    tts_init(&tts);

    overlap_speak("先帝创业未半而中道崩殂");
    sleep(1);
    overlap_speak("先帝创业未半而中道崩殂");
    sleep(1);
    overlap_speak("先帝创业未半而中道崩殂");
    sleep(1);
    overlap_speak("先帝创业未半而中道崩殂");
    sleep(10000);
    return 0;
}

