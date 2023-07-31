#include <windows.h>
#include <iostream>
#include "../tray.hpp"

using namespace std;

int main()
{
    // 启动
    hmc_tray::start();
    // 设置图标
    hmc_tray::setTrayIcon("C:\\Windows\\explorer.exe");

    // 设置主按钮
    hmc_tray::addMenuItem(hmc_tray::Menu::menu("显示窗口", "btn::show_window"));
    hmc_tray::addMenuItem(hmc_tray::Menu::check("自动同步", "btn::auto_sync", true));
    hmc_tray::addMenuItem(hmc_tray::Menu::separator("btn::separator::01"));
    hmc_tray::addMenuItem(hmc_tray::Menu::menu("马上同步", "btn::show_start"));
    hmc_tray::addMenuItem(hmc_tray::Menu::check("自动启动", "btn::auto_start_app", true));
    hmc_tray::addMenuItem(hmc_tray::Menu::menu("退出程序", "btn::quit_app"));

    // 子键创建方式 演示
    hmc_tray::addMenuItem(hmc_tray::Menu::menu("同步方式", "sub::type_sync", true));

    hmc_tray::addMenuItem(hmc_tray::Menu::check("立刻同步", "sub::at_once_sync", true));
    // 分割线
    hmc_tray::addMenuItem(hmc_tray::Menu::separator("sub::separator::02"));

    hmc_tray::addMenuItem(hmc_tray::Menu::check("停止同步", "sub::check_stop_sync", true));
    hmc_tray::addMenuItem(hmc_tray::Menu::check("每分钟制", "sub::check_min", true));
    hmc_tray::addMenuItem(hmc_tray::Menu::check("每小时制", "sub::check_hourly", true));

    // hmc_tray::on<id>
    /**
     * 他还支持
     * - middleClick
     * - move
     * - click
     * - mouseMove
     * - leftButtonDoubleClick
     * - dblclick
     * - leftButtonUp
     * - leftButtonDown
     * - rightButtonUp
     * - rightButtonDown
     */

    hmc_tray::on("move", ([]()
                          { cout << "move->"
                                 << "" << endl; }));

    // 按下了 停止同步 后 其他选择都取消
    hmc_tray::on("sub::check_stop_sync", ([]()
                                          {
											  cout << "click->"
												   << "sub::check_stop_sync" << endl;
											  hmc_tray::setMenuItmeSelect("sub::check_min", false);
											  hmc_tray::setMenuItmeSelect("sub::check_hourly", false);
											  hmc_tray::setMenuItmeSelect("sub::at_once_sync", false);

											  // 如果未选中就选中
											  if (hmc_tray::getMenuItme("sub::check_stop_sync").select)
											  {
												  hmc_tray::setMenuItmeSelect("sub::check_stop_sync", true);
											  }
											  else
											  {
												  hmc_tray::setMenuItmeSelect("sub::check_stop_sync", false);
											  } }));

    // 将这些按钮添加到XXX按钮中
    hmc_tray::setMenuItmetoSubMenu(
        // 主按钮是此ID
        "sub::type_sync",
        // 子按钮是这些
        "sub::at_once_sync", "sub::separator::02", "sub::check_stop_sync", "sub::check_min", "sub::check_hourly");

    Sleep(3000);
    hmc_tray::setTrayInfo("时间已经过去了三秒");

    // 禁用此id的按钮：
    hmc_tray::setMenuItmeEnable("sub::check_min", true);

    // 隐藏此id的按钮：
    hmc_tray::setMenuItmeVisible("btn::quit_app", false);

    Sleep(5000);
    // 设置此按钮的名称为：
    hmc_tray::setMenuItmeName("btn::auto_sync", "取消同步");
    hmc_tray::setTrayInfo("正在同步中....");
    Sleep(9000);

    hmc_tray::setMenuItmeName("btn::auto_sync", "自动同步");
    hmc_tray::setTrayInfo("上传一次更新为9秒前\n共更新了9999条数据");

    while (true)
    {
    }

    hmc_tray::close();

    return 0;
}
