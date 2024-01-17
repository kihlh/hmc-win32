#include <iostream>
#include <windows.h>
#include "../include/attribute.hpp"
#include "../registr.hpp"
#include "../environment.hpp"

using namespace std;
using namespace hmc_registr;
using namespace hmc_env;

int main()
{

   // 枚举所有的 系统变量的键
   for (auto &&keyUse : hmc_env::systemEnv::keySysList())
   {
      cout << keyUse << endl;
   }

   // 枚举所有的 用户变量的键
   for (auto &&keyUse : hmc_env::systemEnv::keyUseList())
   {
      cout << keyUse << endl;
   }


   // 枚举所有的 用户变量 (按照系统的环境变量分析的)
   for (auto &&globalVariable : hmc_env::systemEnv::getGlobalVariable())
   {

      cout << globalVariable.first << "         : " << globalVariable.second << endl;

   }


   // 添加用户变量
   hmc_env::systemEnv::putUse("环境名称", "值", false /*添加到尾部*/, true /*自转义变量： %变量%  */);

   // 转义环境文本带入(实时获取)
   hmc_env::systemEnv::escapeEnvVariable("%APPDATA%\\目录");

   // 获取指定变量 (按照变量实际优先级排序)
   string pEnvStr = string();
   if (hmc_env::systemEnv::get("APPDATA", pEnvStr))
   {
      cout << "获取默认的变量值 成功  值是 -> " << pEnvStr << endl;
   };


   // 获取指定变量 (按照变量实际优先级排序) [系统变量]
   string pSysEnvStr = string();
   if (hmc_env::systemEnv::getSys("APPDATA", pSysEnvStr))
   {
      cout << "获取系统的变量值 成功  值是 -> " << pSysEnvStr << endl;
   };


   hmc_env::systemEnv::removeUse("需要删除的变量名");


   // 从系统获取所有变量并写入到当前进程
   hmc_env::systemEnv::updateThis(true/*触发已删除的值移除*/,true/*触发值更新*/);


   return 0;
}
