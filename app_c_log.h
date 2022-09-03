/*    Copyright 2022 邹涛

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */

#ifndef _APP_C_LOG_H_
#define _APP_C_LOG_H_

#include <stdio.h>
#include <string.h>

enum LOG_LEVEL {
	log_level_error = 0,
	log_level_warn,
	log_level_info,
	log_level_debug,
	log_level_trace
};
// log 级别
enum LOG_LEVEL log_level = log_level_trace;
// 是否开启log
#define LOG_OPEN 1
// 是否支持RTOS
#define LOG_RTOS 0

#if LOG_OPEN && LOG_RTOS
// RTOS
#define log_rtos_mutex myMutex01Handle
// RTOS 获取互斥量
#define log_rtos_mutex_acquire osMutexAcquire(log_rtos_mutex, osWaitForever);
// RTOS 释放互斥量
#define log_rtos_mutex_release osMutexRelease(log_rtos_mutex);
#else
#define log_rtos_mutex_acquire
#define log_rtos_mutex_release
#endif


#ifdef WIN32
#define TrimFilePath(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#else
#define TrimFilePath(x) strrchr(x,'/')?strrchr(x,'/')+1:x
#endif

#if LOG_OPEN

#define tlogerror(format, ...) \
    if(log_level_error <= log_level){ \
        log_rtos_mutex_acquire; \
        printf("ERROR[%s:%d] - "format"\r\n", TrimFilePath(__FILE__), __LINE__, ##__VA_ARGS__); \
        log_rtos_mutex_release;}

#define tlogwarn(format, ...) \
    if(log_level_warn <= log_level){ \
        log_rtos_mutex_acquire; \
        printf("WARN [%s:%d] - "format"\r\n", TrimFilePath(__FILE__), __LINE__, ##__VA_ARGS__); \
        log_rtos_mutex_release;}

#define tloginfo(format, ...) \
    if(log_level_info <= log_level){ \
        log_rtos_mutex_acquire; \
        printf("INFO [%s:%d] - "format"\r\n", TrimFilePath(__FILE__), __LINE__, ##__VA_ARGS__); \
        log_rtos_mutex_release;}

#define tlogdebug(format, ...) \
    if(log_level_debug <= log_level){ \
	    log_rtos_mutex_acquire; \
        printf("DEBUG[%s:%d] - "format"\r\n", TrimFilePath(__FILE__), __LINE__, ##__VA_ARGS__); \
        log_rtos_mutex_release;}

#define tlogtrace(format, ...) \
    if(log_level_trace <= log_level){ \
    	log_rtos_mutex_acquire; \
        printf("TRACE[%s:%d] - "format"\r\n", TrimFilePath(__FILE__), __LINE__, ##__VA_ARGS__); \
        log_rtos_mutex_release;}

#else
#define tlogerror(format, ...)
#define tlogwarring(format, ...)
#define tloginfo(format, ...)
#define tlogdebug(format, ...)
#define tlogtrace(format, ...)
#endif

#endif /* INC_APP_C_LOG_H_ */
