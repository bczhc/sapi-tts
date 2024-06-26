#ifndef SAPI_TTS_UTF8_H
#define SAPI_TTS_UTF8_H

#include "defs.h"
#include <vector>

struct SolvedUTF8Properties {
    u32 bytesLength;
    u32 codepoint;
};

struct Surrogate {
    uint16_t lead;
    uint16_t trail;
};

u32 utf8_size(u8 firstByte);

SolvedUTF8Properties decode_utf8(const u8 *bytes);

static constexpr uint32_t LEAD_OFFSET = 0xd800 - (0x10000U >> 10U);
static constexpr uint32_t SURROGATE_OFFSET = 0x10000 - (0xD800U << 10U) - 0xDc00;

Surrogate codepoint2surrogate(u32 codepoint);

u32 surrogate2codepoint(u16 lead, u16 trail);

bool utf16_need_surrogate(u32 codepoint);

std::vector<u16> utf8_to_utf16(const char *s);

#endif //SAPI_TTS_UTF8_H
