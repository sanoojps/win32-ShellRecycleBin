// win32-ShellRecycleBin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winerror.h>
#include <Windows.h>
#include <iostream>
#include  <strsafe.h> //for StringCchPrintf
#include <shellapi.h>

using namespace std;



void getCurrentDir()
{
	/*
	DWORD WINAPI GetCurrentDirectory(
  _In_   DWORD nBufferLength,
  _Out_  LPTSTR lpBuffer
);
*/

	DWORD numberOFCharacters;
	DWORD lastError;

	TCHAR buffer[MAX_PATH];//LPTSTR

	numberOFCharacters = GetCurrentDirectoryW(sizeof(buffer),buffer);
	lastError = GetLastError();

	if(lastError != 0)
	{
		cout << "Call to GetCurrentDirectoryW function failed \n" ;  
	}
	else
	{
	wcout << "numberOFCharacters : " << numberOFCharacters << "\n";
	wcout << "CurrentDirectory : " << buffer << "\n";
	wcout << "Error : " << lastError << "\n";
	}
}



void ErrorExit(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}


//typedef struct {
//  DWORD   cbSize;
//  __int64 i64Size;
//  __int64 i64NumItems;
//} SHQUERYRBINFO, *LPSHQUERYRBINFO;

SHQUERYRBINFO pSHQueryRBInfo;

int _tmain(int argc, _TCHAR* argv[])
{



	/*getCurrentDir();
	ErrorExit(TEXT("getCurrentDir"));*/

	pSHQueryRBInfo.cbSize = sizeof(SHQUERYRBINFO);
	LPCWSTR pszRootPath = L"C:\\";
	
	 HRESULT nu;
		nu  = SHQueryRecycleBin(
			_In_opt_  NULL,
			_Inout_   &pSHQueryRBInfo
			);  
	
		wcout << "pSHQueryRBInfo.i64NumItems : " << pSHQueryRBInfo.i64NumItems<< "\n";
		wcout << "pSHQueryRBInfo.i64Size : " << pSHQueryRBInfo.i64Size<< "\n" ;
		wcout << "HRESULT Return Code : " << nu << "\n" ;

	int a;
	wcin >> a ;
	return 0;
}

