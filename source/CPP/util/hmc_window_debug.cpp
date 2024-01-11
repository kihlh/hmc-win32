#include <iostream>
#include "hmc_string_util.hpp"
#include "hmc_windows_util.hpp"
#include "console_wide.hpp"


using namespace std;

void console_eqok() {

	HWND hwnd = (HWND)330188;

	//?ok
	console_log(L"GetWindowTitleW", hmc_windows_util::getWindowTitle(hwnd));

	//?ok
	console_log(L"GetWindowTitleInternal", hmc_windows_util::getWindowTitleInternal(hwnd));

	//?ok
	console_log(L"GetWindowTextW", hmc_windows_util::getWindowText(hwnd, 1001));

	//?ok
	console_log(L"SetWindowTitle", hmc_windows_util::setWindowTitle(hwnd, L"你好这个世界"));

	//?ok
	console_log(L"GetAllWindows <true> ", hmc_windows_util::getAllWindows(true));

	//?ok
	console_log(L"GetAllWindows <false> ", hmc_windows_util::getAllWindows(false));

	//?ok
	console_log(L"GetClassName", hmc_windows_util::getClassName(hwnd));
	
	//?ok
	console_log(L"killWindowProcess", hmc_windows_util::killWindowProcess(hwnd));

	//?ok
	cout << "getWindowProcessID-> " << hmc_windows_util::getWindowProcessID(hwnd) << endl;
	
	//?ok !子句柄会无效 应当查找主句柄
	cout << "setWindowTop-> " << hmc_windows_util::setWindowTop(hwnd, true) << endl;

	//?ok
	cout << "setWindowEnabled-> " << hmc_windows_util::setWindowEnabled(hwnd, true) << endl;

	//?ok
	cout << "isDesktopWindow-> " << hmc_windows_util::isDesktopWindow(hwnd) << endl;

	//?ok
	cout << "isWindowTop-> " << hmc_windows_util::isWindowTop(hwnd) << endl;

	//?ok
	cout << "getPointWindow-> " << (long)hmc_windows_util::getPointWindow() << endl;

	//?ok
	console_log(L"getSubWindows-> ", hmc_windows_util::getSubWindows(hwnd));

	//?ok
	cout << "isChildWindow-> " << hmc_windows_util::isChildWindow(hwnd, (HWND)4066462) << endl;

	//?ok
	hmc_windows_util::setWindowInTaskbarVisible(hwnd, false);

}

int main()
{
	HWND hwnd = (HWND)68280;

	hmc_windows_util::setWindowIcon(hwnd, L"F:\\Root\\APortable\\SetContextMenu.exe",std::nullopt, std::nullopt);

	UpdateWindow(hwnd);


}
