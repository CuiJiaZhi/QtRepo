// C/C++计时器，适用平台：Windows、linux

#ifdef _WIN32
    #ifdef _WIN64                       // Window平台
        #ifdef __cplusplus
            #include <iostream>
            #include <chrono>
            // 基于作用域的CPU计时器
            class CPUTimer
            {
            private:
                const char* _Name;          // 名称
                static float time;          // 时间

                std::chrono::steady_clock::time_point _startTimePoint;
                std::chrono::steady_clock::time_point _endTimePoint;
            public:
                CPUTimer(const char* name)           // 构造函数
                    : _Name(name) {
                    _startTimePoint = std::chrono::high_resolution_clock::now();
                }

                ~CPUTimer() {                        // 析构函数
                    _endTimePoint = std::chrono::high_resolution_clock::now();
                    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(_startTimePoint).time_since_epoch().count();
                    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(_endTimePoint).time_since_epoch().count();

                    time = 1.0f * (end - start);

                    std::cout << "\033[32m" << "--" << _Name << ": " << "\033[33m" << time << "us(" << time / 1000.0 << "ms)" << "\033[0m" << "\n";
                }

                static float GetTime() {
                    return time;
                }
            };
        #else
            #include <Windows.h>
            typedef struct WinAPITimer {        // 结构体
                LARGE_INTEGER StartTime;        // 开始时间计时器的滴答数
                LARGE_INTEGER EndTime;          // 结束时间计时器的滴答数
                LARGE_INTEGER Frequency;        // 计时器的频率，即每秒钟的滴答数
                float time;                     // 计时结果，单位:us
            }WAT; WAT wat;
            // 开始计时
            #define TIMERSTART \
            do { \
                QueryPerformanceFrequency(&wat.Frequency); \
                QueryPerformanceCounter(&wat.StartTime); \
            } while(0)
            // 结束计时
            #define TIMEREND \
            do { \
                QueryPerformanceCounter(&wat.EndTime); \
                wat.time = (float)((wat.EndTime.QuadPart - wat.StartTime.QuadPart) * 1000000) / wat.Frequency.QuadPart;/* 获取微妙 */ \
            } while(0)
        #endif
    #else
    #endif
#elif __linux__                         // linux平台
    #if 1                               // 微秒级
        #include <sys/time.h>
        typedef struct LinuxAPITimer {      // 结构体
            struct timeval StartTime;       // 时间结构体
            struct timeval StartTime;
            unsigned long time;             // 计时结果，单位:us
        }LAT; LAT lat;
        // 开始计时
        #define TIMERSTART \
        do { \
            gettimeofday(&lat.start, NULL); \
        } while(0)
        // 结束计时
        #define TIMEEND \
        do { \
            gettimeofday(&lat.end, NULL); \
            lat.time = 1000000 * (lat.end.tv_sec - lat.start.tv_sec) + lat.end.tv_usec - lat.start.tv_usec; \
        } while(0)
    #else                               // 纳秒级
        #include <time.h>
        typedef struct LinuxAPITimer {      // 结构体
            struct timespec StartTime;      // 时间结构体
            struct timespec EndTime;
            unsigned long time;             // 计时结果，单位ns
        }LAT; LAT lat;
        // 开始计时
        #define TIMERSTART \
        do { \
            clock_gettime(CLOCK_REALTIME, &lat.StartTime); \
        } while(0)
        // 结束计时
        #define TIMEREND \
        do { \
            clock_gettime(CLOCK_REALTIME, &lat.EndTime); \
            lat.time = lat.EndTime.tv_nsec - lat.StartTime.tv_nsec; \
        } while(0)
    #endif
#endif
