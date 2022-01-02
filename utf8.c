#include "utf8.h"
#include "./lib.h"

u32 utf8_size(u8 firstByte) {
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

struct SolvedUTF8Properties decode_utf8(const u8 *bytes) {
    struct SolvedUTF8Properties solved;
    solved.bytesLength = utf8_size(bytes[0]);
    switch (solved.bytesLength) {
        case 1:
            solved.codepoint = (int) (bytes[0] & 0b01111111U);
            break;
        case 2:
            solved.codepoint = (int) ((bytes[1] & 0b00111111U)
                                      | ((bytes[0] & 0b00011111U) << 6U));
            break;
        case 3:
            solved.codepoint = (int) ((bytes[2] & 0b00111111U)
                                      | ((bytes[1] & 0b00111111U) << 6U)
                                      | ((bytes[0] & 0b00001111U) << 12U));
            break;
        case 4:
            solved.codepoint = (int) ((bytes[3] & 0b00111111U)
                                      | ((bytes[2] & 0b00111111U) << 6U)
                                      | ((bytes[1] & 0b00111111U) << 12U)
                                      | ((bytes[0] & 0b00000111U) << 18U));
            break;
        default:
            break;
    }
    return solved;
}

struct Surrogate codepoint2surrogate(u32 codepoint) {
    uint16_t lead = LEAD_OFFSET + (codepoint >> 10U);
    uint16_t trail = 0xDc00 + (codepoint & 0x3FFU);
    struct Surrogate r = {.lead = lead, .trail = trail};
    return r;
}

u32 surrogate2codepoint(u16 lead, u16 trail) {
    return (lead << 10U) + trail + SURROGATE_OFFSET;
}

bool utf16_need_surrogate(u32 codepoint) {
    return codepoint > 0xFFFF;
}

struct UTF16String utf8_to_utf16(const char *s) {
    struct List list;
    list_init(&list);

    usize strSize = strlen(s);
    usize p = 0;
    while (p < strSize) {
        struct SolvedUTF8Properties solved = decode_utf8(((u8 *) s + p));
        if (solved.bytesLength == 0) {
            err_println("Invalid UTF-8");
            abort();
        }
        p += (usize) solved.bytesLength;

        if (utf16_need_surrogate(solved.codepoint)) {
            struct Surrogate surrogate = codepoint2surrogate(solved.codepoint);
            list_put(&list, surrogate.lead);
            list_put(&list, surrogate.trail);
        } else {
            list_put(&list, (u16) solved.codepoint);
        }
    }

    // append the zero-terminator
    list_put(&list, 0);

    usize size = list_length(&list) * sizeof(u16);
    LIST_T *data = list_take_data(&list);
    struct UTF16String r = {.data = data, .size = size};
    return r;
}

void utf16_release(struct UTF16String *utf16) {
    free(utf16->data);
}
