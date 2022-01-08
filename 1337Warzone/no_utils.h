#pragma once

namespace No_Utils 
{
	int GetProcessId(const char* pname) 
	{
		PROCESSENTRY32 proc_info;
		proc_info.dwSize = sizeof(proc_info);
		HANDLE proc_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (proc_snapshot == INVALID_HANDLE_VALUE)
			return NULL;
		Process32First(proc_snapshot, &proc_info);
		if (!strcmp((const char*)proc_info.szExeFile, pname))
		{
			CloseHandle(proc_snapshot);
			return proc_info.th32ProcessID;
		}
		while (Process32Next(proc_snapshot, &proc_info))
		{
			if (!strcmp(proc_info.szExeFile, pname))
			{
				CloseHandle(proc_snapshot);
				return proc_info.th32ProcessID;
				break;
			}
		}
		CloseHandle(proc_snapshot);
		return NULL;
	}
}