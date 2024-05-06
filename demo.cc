#include "tts.hh"
#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>

using namespace std;

std::thread overlap_speak_thread(const std::string &text) {
    return std::thread([&] {
        const TTS tts;
        tts.set_rate(2);
        tts.set_priority(SPVPRI_OVER);
        tts.speak(text);
    });
}

void overlap_speak() {
    std::vector<std::thread> tasks;

    tasks.push_back(overlap_speak_thread("先帝创业未半而中道崩殂"));
    sleep(1);
    tasks.push_back(overlap_speak_thread("先帝创业未半而中道崩殂"));
    sleep(1);
    tasks.push_back(overlap_speak_thread("先帝创业未半而中道崩殂"));
    sleep(1);
    tasks.push_back(overlap_speak_thread("先帝创业未半而中道崩殂"));

    for (auto &task: tasks) {
        task.join();
    }
}

int main() {
    const TTS tts{};
    tts.set_priority(SPVPRI_OVER);
    tts.speak("A bottle of water");

    overlap_speak();
    return 0;
}
