/*
 *  This file is part of MCU Toolkit Library.
 *
 *  Copyright (c) 2023, Aym, <aymhzy@163.com> 
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 * Describe: MCU Toolkit Component: bit and byte tool
 * Author:   Aym
 * Date:     2023-04-26
 */

#ifndef __MTK_BIT_BYTE_H__
#define __MTK_BIT_BYTE_H__

/* INCLUDE */
#include "mtk_typedefs.h"

#define mtk_set_bit(v, n)   ((v) |= (1ul << (n)))
#define mtk_clr_bit(v, n)   ((v) &= ~(1ul << (n)))
#define mtk_tog_bit(v, n)   ((v) ^= (1ul << (n)))
#define mtk_get_bit(v, n)   (((v) >> (n)) & 1u)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static inline uint8_t mtk_is_little (void)
{
    uint16_t test = 0x1234;

    return (*((uint8_t*)&test) == 0x34);
}

static inline void mtk_byte_swap (uint8_t* p1, uint8_t* p2)
{
    uint8_t temp = *p1;

    *p1 = *p2;
    *p2 = temp;
}

static inline int16_t mtk_i16_invert (int16_t v)
{
    int16_t value = v;
    uint8_t* p = (uint8_t*)&value;

    mtk_byte_swap(p, p+1);
    return value;
}

static inline uint16_t mtk_u16_invert (uint16_t v)
{
    return (v << 8) | (v >> 8);
}

static inline int32_t mtk_i32_invert (int32_t v)
{
    int32_t value = v;
    uint8_t*p = (uint8_t*)&value;

    mtk_byte_swap(p, p+3);
    mtk_byte_swap(p+1,p+2);

    return value;
}

static inline uint32_t mtk_u32_invert (uint32_t v)
{
    uint32_t value = v;
    uint8_t*p = (uint8_t*)&value;

    mtk_byte_swap(p, p+3);
    mtk_byte_swap(p+1,p+2);

    return value;
}

static inline int64_t mtk_i64_invert (int64_t v)
{
    int64_t value = v;
    uint8_t*p = (uint8_t*)&value;

    mtk_byte_swap(p, p+7);
    mtk_byte_swap(p+1,p+6);
    mtk_byte_swap(p+2,p+5);
    mtk_byte_swap(p+3,p+4);

    return value;
}

static inline uint64_t mtk_u64_invert (uint64_t v)
{
    uint64_t value = v;
    uint8_t*p = (uint8_t*)&value;

    mtk_byte_swap(p, p+7);
    mtk_byte_swap(p+1,p+6);
    mtk_byte_swap(p+2,p+5);
    mtk_byte_swap(p+3,p+4);

    return value;
}

static inline float mtk_f32_invert (float v)
{
    float value = v;
    uint8_t*p = (uint8_t*)&value;

    mtk_byte_swap(p, p+3);
    mtk_byte_swap(p+1,p+2);

    return value;
}

static inline double mtk_f64_invert (double v)
{
    double value = v;
    uint8_t*p = (uint8_t*)&value;

    mtk_byte_swap(p, p+7);
    mtk_byte_swap(p+1,p+6);
    mtk_byte_swap(p+2,p+5);
    mtk_byte_swap(p+3,p+4);

    return value;
}

/******************************************************************************************/

static inline int16_t mtk_i16_b2l (int16_t big_endian_value)
{
    return mtk_is_little() ? mtk_i16_invert(big_endian_value) : big_endian_value;
}

static inline int32_t mtk_i32_b2l (int32_t big_endian_value)
{
    return mtk_is_little() ? mtk_i32_invert(big_endian_value) : big_endian_value;
}

static inline int64_t mtk_i64_b2l (int64_t big_endian_value)
{
    return mtk_is_little() ? mtk_i64_invert(big_endian_value) : big_endian_value;
}

static inline uint16_t mtk_u16_b2l (uint16_t big_endian_value)
{
    return mtk_is_little() ? mtk_u16_invert(big_endian_value) : big_endian_value;
}

static inline uint32_t mtk_u32_b2l (uint32_t big_endian_value)
{
    return mtk_is_little() ? mtk_u32_invert(big_endian_value) : big_endian_value;
}

static inline uint64_t mtk_u64_b2l (uint64_t big_endian_value)
{
    return mtk_is_little() ? mtk_u64_invert(big_endian_value) : big_endian_value;
}

static inline float mtk_f32_b2l (float big_endian_value)
{
    return mtk_is_little() ? mtk_f32_invert(big_endian_value) : big_endian_value;
}

static inline double mtk_f64_b2l (double big_endian_value)
{
    return mtk_is_little() ? mtk_f64_invert(big_endian_value) : big_endian_value;
}

/******************************************************************************************/

static inline int16_t mtk_i16_l2b (int16_t little_endian_value)
{
    return mtk_is_little() ? mtk_i16_invert(little_endian_value) : little_endian_value;
}

static inline int32_t mtk_i32_l2b (int32_t little_endian_value)
{
    return mtk_is_little() ? mtk_i32_invert(little_endian_value) : little_endian_value;
}

static inline int64_t mtk_i64_l2b (int64_t little_endian_value)
{
    return mtk_is_little() ? mtk_i64_invert(little_endian_value) : little_endian_value;
}

static inline uint16_t mtk_u16_l2b (uint16_t little_endian_value)
{
    return mtk_is_little() ? mtk_u16_invert(little_endian_value) : little_endian_value;
}

static inline uint32_t mtk_u32_l2b (uint32_t little_endian_value)
{
    return mtk_is_little() ? mtk_u32_invert(little_endian_value) : little_endian_value;
}

static inline uint64_t mtk_u64_l2b (uint64_t little_endian_value)
{
    return mtk_is_little() ? mtk_u64_invert(little_endian_value) : little_endian_value;
}

static inline float mtk_f32_l2b (float little_endian_value)
{
    return mtk_is_little() ? mtk_f32_invert(little_endian_value) : little_endian_value;
}

static inline double mtk_f64_l2b (double little_endian_value)
{
    return mtk_is_little() ? mtk_f64_invert(little_endian_value) : little_endian_value;
}

/******************************************************************************************/

static inline uint16_t mtk_bytes_to_16B (void* bytes)
{
    uint16_t v;
    memcpy(&v, bytes, sizeof(uint16_t));
    return v;
}

static inline uint32_t mtk_bytes_to_32B (void* bytes)
{
    uint32_t v;
    memcpy(&v, bytes, sizeof(uint32_t));
    return v;
}

static inline uint64_t mtk_bytes_to_64B (void* bytes)
{
    uint64_t v;
    memcpy(&v, bytes, sizeof(uint64_t));
    return v;
}

static inline void mtk_16B_to_bytes (uint16_t value, uint8_t* bytes)
{
    uint16_t v = value;
    memcpy(bytes, &v, sizeof(uint16_t));
}

static inline void mtk_32B_to_bytes (uint32_t value, uint8_t* bytes)
{
    uint32_t v = value;
    memcpy(bytes, &v, sizeof(uint32_t));
}

static inline void mtk_64B_to_bytes (uint64_t value, uint8_t* bytes)
{
    uint64_t v = value;
    memcpy(bytes, &v, sizeof(uint64_t));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_BIT_BYTE_H__ */
