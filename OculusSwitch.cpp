// OculusSwitch.cpp : Defines the entry point for the console application.
// A program that switches the oculus service on and off

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>


int _tmain()
{
	// Handle for services
	SC_HANDLE serviceDbHandle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE serviceHandle = OpenService(serviceDbHandle, L"OVRService", SC_MANAGER_ALL_ACCESS);

	SERVICE_STATUS_PROCESS status;
	DWORD bytesNeeded;
	QueryServiceStatusEx(serviceHandle, SC_STATUS_PROCESS_INFO, (LPBYTE)&status, sizeof(SERVICE_STATUS_PROCESS), &bytesNeeded);

	if (status.dwCurrentState == SERVICE_RUNNING)
	{
		// Hey don't do that stop
		BOOL b = ControlService(serviceHandle, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&status);
		if (b)
		{
			std::cout << "Oculus service stopped." << std::endl;
		}
		else
		{
			std::cout << "Oculus service failed to stop." << std::endl;
		}
	}
	else
	{
		// Start the service again
		BOOL b = StartService(serviceHandle, NULL, NULL);
		if (b)
		{
			std::cout << "Oculus service started" << std::endl;
		}
		else
		{
			std::cout << "Oculus service failed to start" << std::endl;
		}
	}
	// Does what it says on the tin
	CloseServiceHandle(serviceHandle);
	CloseServiceHandle(serviceDbHandle);
	return 0;
}
