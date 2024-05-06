#include "utf8.hh"
#include <cstdlib>
#include <cstring>
#include "lib.hh"
#include <vector>

u32 utf8_size(const u8 firstByte) {
    if (firstByte >> 7U == 0)
        return 1;
    if (firstByte >> 5U == 0b110)
        return 2;
    if (firstByte >> 4U == 0b1110)
        return 3;
    if (firstByte >> 3U == 0b11110)
        return 4;
    return 0;
}

SolvedUTF8Properties decode_utf8(const u8 *bytes) {
    SolvedUTF8Properties solved{};
    solved.bytesLength = utf8_size(bytes[0]);
    switch (solved.bytesLength) {
        case 1:
            solved.codepoint = static_cast<int>(bytes[0] & 0b01111111U);
            break;
        case 2:
            solved.codepoint = static_cast<int>(bytes[1] & 0b00111111U
                                                | (bytes[0] & 0b00011111U) << 6U);
            break;
        case 3:
            solved.codepoint = static_cast<int>(bytes[2] & 0b00111111U
                                                | (bytes[1] & 0b00111111U) << 6U
                                                | (bytes[0] & 0b00001111U) << 12U);
            break;
        case 4:
            solved.codepoint = static_cast<int>(bytes[3] & 0b00111111U
                                                | (bytes[2] & 0b00111111U) << 6U
                                                | (bytes[1] & 0b00111111U) << 12U
                                                | (bytes[0] & 0b00000111U) << 18U);
            break;
        default:
            break;
    }
    return solved;
}

Surrogate codepoint2surrogate(const u32 codepoint) {
    const uint16_t lead = LEAD_OFFSET + (codepoint >> 10U);
    const uint16_t trail = 0xDc00 + (codepoint & 0x3FFU);
    const Surrogate r = {.lead = lead, .trail = trail};
    return r;
}

u32 surrogate2codepoint(const u16 lead, const u16 trail) {
    return (lead << 10U) + trail + SURROGATE_OFFSET;
}

bool utf16_need_surrogate(const u32 codepoint) {
    return codepoint > 0xFFFF;
}

std::vector<u16> utf8_to_utf16(const char *s) {
    std::vector<u16> list;

    const usize strSize = strlen(s);
    usize p = 0;
    while (p < strSize) {
        const auto [bytesLength, codepoint] = decode_utf8(reinterpret_cast<const u8 *>(s + p));
        if (bytesLength == 0) {
            err_println("Invalid UTF-8");
            abort();
        }
        p += static_cast<usize>(bytesLength);

        if (utf16_need_surrogate(codepoint)) {
            const auto [lead, trail] = codepoint2surrogate(codepoint);
            list.push_back(lead);
            list.push_back(trail);
        } else {
            list.push_back(static_cast<u16>(codepoint));
        }
    }

    // append the zero-terminator
    list.push_back(0);
    return list;
}
