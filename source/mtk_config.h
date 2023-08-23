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
 * Describe: MCU Toolkit Configuration
 * Author:   Aym
 * Date:     2023-08-23
 */

#ifndef __MTK_CONFIG_H__
#define __MTK_CONFIG_H__

#define MTK_VERSION_NUMBER                  "0.1.0"

#define MTK_ENABLE_COMPONENT_BUFFER         1

#define MTK_ENABLE_COMPONENT_STACK          1

#define MTK_ENABLE_COMPONENT_TIMER          1

#define MTK_ENABLE_COMPONENT_DARRAY         1

#define MTK_ENABLE_COMPONENT_MEMPOOL        1

#define MTK_ENABLE_COMPONENT_CRC            1

#define MTK_ENABLE_COMPONENT_BUTTON         1

#define MTK_ENABLE_COMPONENT_LED            1

#define MTK_ENABLE_COMPONENT_FSM            1

#define MTK_ENABLE_COMPONENT_MENU           1

#if MTK_ENABLE_COMPONENT_STACK && !MTK_ENABLE_COMPONENT_BUFFER
#error MTK_BUFFER shall be enabled if MTK_STACK is supported
#endif

#if MTK_ENABLE_COMPONENT_DARRAY && !MTK_ENABLE_COMPONENT_MEMPOOL
#error MTK_MEMPOOL shall be enabled if MTK_DARRAY is supported
#endif

#if MTK_ENABLE_COMPONENT_LED && !MTK_ENABLE_COMPONENT_TIMER
#error MTK_TIMER shall be enabled if MTK_LED is supported
#endif

#if MTK_ENABLE_COMPONENT_MEMPOOL
#define MTK_CONFIG_MEMPOOL_SIZE             4096
#endif

#define MTK_MULTI_THREAD_SAFE               0

#if MTK_MULTI_THREAD_SAFE
#define MTK_ENTER_CRITICAL_FN               /* USER PROVIDED */
#define MTK_EXIT_CRITICAL_FN                /* USER PROVIDED */    
#endif

#endif /* __MTK_CONFIG_H__ */
