#include "./tts.h"

int main(int argc, char **argv) {
    if (argc == 1) {
        return 1;
    }

    struct TTS tts;
    tts_init(&tts);
    tts_set_rate(&tts, 2);
    tts_speak(&tts, argv[1]);
    tts_release(&tts);

    return 0;
}

