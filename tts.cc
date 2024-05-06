#include "tts.hh"
#include "lib.hh"
#include "utf8.hh"

// I don't know but I must manually define these two fields, to make it compile
static constexpr GUID CLSID_SpVoice_ = {0x96749377, 0x3391, 0x11d2, 0x9e, 0xe3, 0x00, 0xc0, 0x4f, 0x79, 0x73, 0x96};
static constexpr GUID IID_ISpVoice_ = {0x6c44df74, 0x72b9, 0x4992, 0xa1, 0xec, 0xef, 0x99, 0x6e, 0x04, 0x22, 0xd4};

TTS::TTS() {
    if (FAILED(CoInitialize(nullptr))) {
        err_println("CoInitialize(...) failed");
        abort();
    }

    pVoice = nullptr;

    if (const HRESULT hr = CoCreateInstance(CLSID_SpVoice_, nullptr, CLSCTX_ALL, IID_ISpVoice_,
                                            reinterpret_cast<LPVOID *>(&pVoice)); FAILED(hr)) {
        err_println("CoCreateInstance(...) failed");
        abort();
    }
}

TTS::~TTS() {
    pVoice->Release();
    CoUninitialize();
}

void TTS::speak(const std::string &text, const DWORD flags) const {
    const auto utf16 = utf8_to_utf16(text.c_str());
    (void) pVoice->Speak(reinterpret_cast<LPCWSTR>(utf16.data()), flags, nullptr);
}

void TTS::set_rate(const LONG rate) const {
    (void) pVoice->SetRate(rate);
}

void TTS::set_priority(const SPVPRIORITY priority) const {
    (void) pVoice->SetPriority(priority);
}


