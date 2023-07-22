#include <iostream>
#include <windows.h>
#include <Psapi.h>

// 时间格式转换
__int64 FileTimeToInt64(const FILETIME &time)
{
	ULARGE_INTEGER tt;
	tt.LowPart = time.dwLowDateTime;
	tt.HighPart = time.dwHighDateTime;
	return (tt.QuadPart);
}

DWORD GetProcessMemoryInfo(DWORD ProcessID)
{
	PROCESS_MEMORY_COUNTERS pmc;
	DWORD memoryInK = 0;
	HANDLE hProcess = NULL;

	hProcess = OpenProcess(
		PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
		FALSE, ProcessID);

	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		// memoryInK = pmc.WorkingSetSize/1024;		//单位为k
		memoryInK = pmc.WorkingSetSize;
	}

	CloseHandle(hProcess);
	return memoryInK;
}


int GetCPUCount() // 获取CPU核心数
{
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    return static_cast<int>(system_info.dwNumberOfProcessors);
}

double GetProcessCpuUsage(DWORD process_id) // 获取指定进程CPU使用率
{
    static int processor_count_ = -1;   // cpu核心数
    static __int64 last_system_time_ = 0;  // 上一次的系统时间
    static __int64 last_time_ = 0;  // 上一次的时间

    FILETIME now;
    FILETIME creation_time;
    FILETIME exit_time;
    FILETIME kernel_time;
    FILETIME user_time;

    __int64 system_time;
    __int64 time;

    double cpu_usage = -1;

    if (processor_count_ == -1)
    {
        processor_count_ = GetCPUCount();
    }

    GetSystemTimeAsFileTime(&now);

    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION |
            PROCESS_VM_READ,
        FALSE, process_id);

    if (!hProcess)
    {
        return -1;
    }

    if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }

    system_time = (FileTimeToInt64(kernel_time) + FileTimeToInt64(user_time)) / processor_count_; // CPU使用时间
    time = FileTimeToInt64(now); // 现在的时间

    last_system_time_ = system_time;
    last_time_ = time;

    CloseHandle(hProcess);

    Sleep(1000); // 睡眠1s

    hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION |
            PROCESS_VM_READ,
        FALSE, process_id);

    if (!hProcess)
    {
        return -1;
    }

    if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }

    GetSystemTimeAsFileTime(&now);
    system_time = (FileTimeToInt64(kernel_time) + FileTimeToInt64(user_time)) / processor_count_; // CPU使用时间
    time = FileTimeToInt64(now);  // 现在的时间

    CloseHandle(hProcess);

    cpu_usage = ((static_cast<double>(system_time - last_system_time_)) / (static_cast<double>(time - last_time_))) * 100;
    return cpu_usage;
}

int main()
{
	while (true)
	{
		Sleep(1000);
		DWORD process_id = 8160;
		std::cout << "cpu->" << GetProcessCpuUsage(process_id) << std::endl;
		std::cout << "memory->" << GetProcessMemoryInfo(process_id)/1024/1024 << std::endl;
	};
}
