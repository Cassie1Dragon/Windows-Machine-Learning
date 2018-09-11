#include <Windows.h>
#include <processthreadsapi.h>
#include "WinMLRunnerTest.h"
#include <winnt.h>
#include <Winbase.h>
#include "Filehelper.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

static DWORD RunProc(LPWSTR commandLine)
{
    STARTUPINFO SI = { 0 };
    PROCESS_INFORMATION PI = { 0 };
    DWORD CreationFlags = 0;
    SI.cb = sizeof(SI);
    VERIFY_IS_TRUE(
        0 != CreateProcess(
            nullptr, commandLine, nullptr, nullptr, FALSE, CreationFlags, nullptr, nullptr, &SI, &PI));
    VERIFY_ARE_EQUAL(WAIT_OBJECT_0, WaitForSingleObject(PI.hProcess, INFINITE));
    DWORD exitCode;
    VERIFY_IS_TRUE(0 != GetExitCodeProcess(PI.hProcess, &exitCode));
    CloseHandle(PI.hThread);
    CloseHandle(PI.hProcess);
    return exitCode;
}

void WinMLRunnerTest::TestPrintUsage()
{
    auto const curPath = FileHelper::GetModulePath();
    std::wstring command = curPath +
        L"./WinMLRunner";
    RunProc((wchar_t *)command.c_str());
}