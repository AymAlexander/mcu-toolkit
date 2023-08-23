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
 * Describe: MCU Toolkit Component: Memory Pool
 * Author:   Aym
 * Date:     2023-04-27
 */

#include "mtk_mempool.h"

#if MTK_ENABLE_COMPONENT_MEMPOOL

#define ALIGN_BYTE  4
#define ALIGN_MASK  0x00000003

static uint8_t mtk_heap[MTK_CONFIG_MEMPOOL_SIZE];

typedef struct _mtk_mb_list {
    struct _mtk_mb_list* next;
    uint32_t             size;
} mtk_mb_list_t;

#define MIN_BLOCKSIZE   (sizeof(mtk_mb_list_t) + ALIGN_BYTE)

typedef struct _mtk_mp_info {
    uint32_t    size;
    uint32_t    max_usage;
    uint32_t    free_bytes;
} mtk_mp_info_t;

static mtk_mp_info_t  mtk_mp_info = {0};
static mtk_mb_list_t  mtk_mb_head;
static mtk_mb_list_t* mtk_mb_tail = NULL;

static void __mem_recycle (mtk_mb_list_t* block);

void mtk_mempool_init (void)
{
    mtk_mb_list_t*   first_block;
    uint32_t         addr;
    uint32_t         heap_size = MTK_CONFIG_MEMPOOL_SIZE;
    uint8_t*         heap;

    addr = (uint32_t)mtk_heap;
    if( (addr & ALIGN_MASK) != 0 ) {
        addr += (ALIGN_BYTE - 1);
        addr &= ~(ALIGN_MASK);
        heap_size -= (addr - (uint32_t)mtk_heap);
    }

    heap = (uint8_t*)addr;

    mtk_mb_head.next = (void*)heap;
    mtk_mb_head.size = 0;

    addr +=  heap_size;
    addr -= sizeof(mtk_mb_list_t);
    addr &= ~(ALIGN_MASK);

    mtk_mb_tail = (mtk_mb_list_t*)addr;
    mtk_mb_tail->next = NULL;
    mtk_mb_tail->size = 0;

    first_block = (mtk_mb_list_t*)heap;
    first_block->next = mtk_mb_tail;
    first_block->size = addr - (uint32_t)first_block;

    mtk_mp_info.free_bytes = first_block->size;
    mtk_mp_info.max_usage = MTK_CONFIG_MEMPOOL_SIZE - first_block->size;
    mtk_mp_info.size = first_block->size;
}

void* mtk_malloc (uint32_t size)
{
    void* ret = NULL;
    mtk_mb_list_t* block;
    mtk_mb_list_t* prevBlock;
    mtk_mb_list_t* newBlock;

#if MTK_MULTI_THREAD_SAFE
    MTK_ENTER_CRITICAL_FN;
#endif
    mtk_goto_error_if_fail(mtk_mb_tail != NULL);
    mtk_goto_error_if_fail(size != 0);

    size = sizeof(mtk_mb_list_t) + size;

    if (size % ALIGN_BYTE) {
        size += ALIGN_BYTE - (size % ALIGN_BYTE);
    }

    mtk_goto_error_if_fail(size != 0);
    mtk_goto_error_if_fail(size < mtk_mp_info.free_bytes);

    prevBlock = &mtk_mb_head;
    block = mtk_mb_head.next;

    while (( block->size < size ) && (block->next != NULL)) {
        prevBlock = block;
        block = block->next;
    }
    mtk_goto_error_if_fail(block != mtk_mb_tail);

    ret = (void*)((uint8_t*)block + sizeof(mtk_mb_list_t));

    prevBlock->next = block->next;

    if ((block->size - size) >= MIN_BLOCKSIZE ) {
        newBlock = (void*)(((uint8_t*)block) + size);
        newBlock->size = block->size - size;
        block->size = size;

        __mem_recycle(newBlock);
    }

    mtk_mp_info.free_bytes -= block->size;

    if (mtk_mp_info.free_bytes < mtk_mp_info.size - mtk_mp_info.max_usage) {
        mtk_mp_info.max_usage = mtk_mp_info.size - mtk_mp_info.free_bytes;
    }

error:
#if MTK_MULTI_THREAD_SAFE
    MTK_EXIT_CRITICAL_FN
#endif
    return ret;
}

void mtk_free (void* addr)
{
    uint8_t* temp = (uint8_t*)addr;
    mtk_mb_list_t* block;

    mtk_return_if_fail(addr != NULL);

    temp -= sizeof(mtk_mb_list_t);
    block = (void*)temp;

#if MTK_MULTI_THREAD_SAFE
    MTK_ENTER_CRITICAL_FN;
#endif

    mtk_mp_info.free_bytes += block->size;
    __mem_recycle(block);

#if MTK_MULTI_THREAD_SAFE
    MTK_EXIT_CRITICAL_FN
#endif
}

void* mtk_calloc(uint32_t num, uint32_t size)
{
    void* ret = NULL;

    ret = mtk_malloc(num * size);
    mtk_return_value_if_fail(ret != NULL, NULL);
    
    memset(ret, 0, num * size);

    return ret;
}

void* mtk_realloc (void* addr, uint32_t size)
{
    void* ret = NULL;
    uint8_t* block_info = addr;

    ret = mtk_malloc(size);
    mtk_return_value_if_fail(ret != NULL, NULL);

    block_info -= sizeof(mtk_mb_list_t);
    memcpy(ret, addr, ((mtk_mb_list_t*)block_info)->size - sizeof(mtk_mb_list_t));
    mtk_free(addr);

    return ret;
}

static void __mem_recycle (mtk_mb_list_t* block)
{
    mtk_mb_list_t* itor;
    uint8_t* addr;

    itor = &mtk_mb_head;

    while (itor->next < block) {
        itor = itor->next;
    }

    addr = (uint8_t*)itor;

    if ((addr + itor->size) == (uint8_t*)block) {
        itor->size += block->size;
        block = itor;
    }

    addr = (uint8_t*)block;

    if ((addr + block->size) == (uint8_t*)itor->next) {
        if( itor->next != mtk_mb_tail) {
            block->size += itor->next->size;
            block->next = itor->next->next;
        } else {
            block->next = mtk_mb_tail;
        }
    } else {
        block->next = itor->next;
    }

    if( itor != block ) {
        itor->next = block;
    }
}

uint32_t mtk_mempool_size_get (void)
{
    return mtk_mp_info.size;
}

uint32_t mtk_mempool_max_usage_get (void)
{
    return mtk_mp_info.max_usage;
}

uint32_t mtk_mempool_free_bytes_get (void)
{
    return mtk_mp_info.free_bytes;
}

#endif /* MTK_ENABLE_COMPONENT_MEMPOOL */
