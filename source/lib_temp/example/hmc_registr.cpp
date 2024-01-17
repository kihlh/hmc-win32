#include "../include/attribute.hpp"
#include "../registr.hpp"

using namespace std;

int main()
{
	// 设置注册表值
	hmc_registr::setRegistrValue(HKEY_CURRENT_USER, "hmc", "hello", string("Hello HMC API Tool"), REG_SZ);

	// 32 bit munber
	hmc_registr::setRegistrValue(HKEY_CURRENT_USER, "hmc", "hmc_munber", (DWORD)566554);

	// 64 bit munber
	hmc_registr::setRegistrValue(HKEY_CURRENT_USER, "hmc", "hmc_munber_long",(DWORD64) 56650000005004);

	hmc_registr::setRegistrValue(HKEY_CURRENT_USER, "hmc", "AutoStr", (string)"Auto Detect Type");

	// GET
	string str_AutoStr = hmc_registr::getRegistrValue<string>(HKEY_CURRENT_USER, "hmc", "AutoStr");
	cout << "str_AutoStr ->  " << str_AutoStr << endl;

	DWORD DW_hmc_munber = hmc_registr::getRegistrValue<DWORD>(HKEY_CURRENT_USER, "hmc", "hmc_munber");
	cout << "str_AutoStr ->  " << DW_hmc_munber << endl;

	cout << "long long  ->  " << hmc_registr::getRegistrValue<long long>(HKEY_CURRENT_USER, "hmc", "hmc_munber_long") << endl;

	cout << "has data"<<(hmc_registr::hasRegistrKey(HKEY_CURRENT_USER, "hmc","hmc_munber_long")?"true":"false")<<endl;

	cout << "has dir"<<(hmc_registr::hasRegistrDir(HKEY_CURRENT_USER, "hmc")?"true":"false")<<endl;



	// 枚举

	auto walkRegistrDir = hmc_registr::walkRegistrDir(HKEY_CURRENT_USER, "hmc", /* 获取数据-> */ false, /* 过滤-> */ REG_SZ);

	for (auto &&data : walkRegistrDir)
	{
		cout << "-----------------------------------" << endl;
		cout << "dirPath       :  " << data.dirPath << endl;
		cout << "is_value      :  " << data.is_value << endl;
		cout << "isDir         :  " << data.isDir << endl;
		cout << "root          :  " << hmc_registr::getHive(data.root) << endl;
		cout << "size          :  " << data.size << endl;
		cout << "time          :  " << data.time << endl;
		cout << "type          :  " << data.type << endl;
		cout << "vkey          :  " << data.vkey << endl;
		cout << "dirPath       :  " << data.dirPath << endl;
		cout << "value[size]   :  " << data.value.size() << endl;
	}


	// 删除单个值
	hmc_registr::removeRegistrValue(HKEY_CURRENT_USER, "hmc", "hmc_munber_long");

	hmc_registr::copyRegistrDir(HKEY_CURRENT_USER, "hmc","hmc2copy");

	hmc_registr::removeRegistrTree(HKEY_CURRENT_USER, "hmc","hmc");

	hmc_registr::removeRegistrDir(HKEY_CURRENT_USER, "hmc");


	return 0;
}
