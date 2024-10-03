import util = require('util/types');
const { isPromise } = util;
import hmc = require("../../index");
const native = hmc.Native.native;


export async function main() {

    let temp = null;


    // :: ................................................................................................................................................................................................................................................................

    console.log("[RegistrStringList]");


    temp = hmc.Registr.setRegistrStringList2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_P1', "牛不吟，\n马不叫\0小小牛马\0收到\0收到\0\0");
    console.log(`[setRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);

    temp = hmc.Registr.setRegistrStringList2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_P2', ["牛不吟，\n马不叫", "小小牛马", "收到", "收到"]);
    console.log(`[setRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);


    temp = hmc.Registr.setRegistrStringList2Sync("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_S1', "牛不吟，\n马不叫\0小小牛马\0收到\0收到\0\0");
    console.log(`[setRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${temp} ]`);

    temp = hmc.Registr.setRegistrStringList2Sync("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_S2', ["牛不吟，\n马不叫", "小小牛马", "收到", "收到"]);
    console.log(`[setRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${temp} ]`);


    temp = hmc.Registr.setRegistrStringList2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_P2', "123");
    console.log(`[setRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);


    temp = hmc.Registr.setRegistrStringList2Sync("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_S2', "123");
    console.log(`[setRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${temp} ]`);


    // get->>

    temp = hmc.Registr.getRegistrStringList2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_P1');
    console.log(`[getRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> `, await temp);

    temp = hmc.Registr.getRegistrStringList2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_P2');
    console.log(`[getRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> `, await temp);


    temp = hmc.Registr.getRegistrStringList2Sync("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_S1');
    console.log(`[getRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> `, temp);

    temp = hmc.Registr.getRegistrStringList2Sync("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", 'STRING_LIST_S2');
    console.log(`[getRegistrStringList2] isPromise-> [ ${isPromise(temp)} ] data-> `, temp);

    console.log("......................................................................................................................................................");

    // :: ................................................................................................................................................................................................................................................................


    temp = hmc.Registr.setRegistrString2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", "title(expand)", process.title, true);
    console.log(`[setRegistrString2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);

    temp = hmc.Registr.setRegistrString2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", "title", process.title, false);
    console.log(`[setRegistrString2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);


    temp = hmc.Registr.setRegistrString2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", "", process.title, false);
    console.log(`[setRegistrString2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);


    temp = hmc.Registr.getRegistrString2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", "", true);
    console.log(`[getRegistrString2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);


    temp = hmc.Registr.setRegistrString2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", "", process.title, true);
    console.log(`[setRegistrString2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);


    temp = hmc.Registr.getRegistrString2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", "title(expand)", true);
    console.log(`[getRegistrString2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);

    temp = hmc.Registr.getRegistrString2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", "title", false);
    console.log(`[getRegistrString2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);


    temp = hmc.Registr.getRegistrString2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", "", false);
    console.log(`[getRegistrString2] isPromise-> [ ${isPromise(temp)} ] data-> [ ${await temp} ]`);


    console.log("......................................................................................................................................................");

    // :: ................................................................................................................................................................................................................................................................


    const DWORD_LIST = {
        "max_DWORD": 0xffffffff,
        "min_DWORD": 0,
        "negative_DWORD": -5000,
        "overflow_DWORD": 0xffffffff + 1,
        "BigInt_DWORD": BigInt(500),
        "string_DWORD": "15611446313",
        "float_DWORD": 15215123.52415,
        // "max_DWORD2": 0,
    };

    const QWORD_LIST = {
        "max_QWORD": 0xffffffffffffffff - 1,
        "min_QWORD": 0,
        "negative_QWORD": -5000,
        "overflow_QWORD": 0xffffffffffffffff + 1,
        "BigInt_QWORD": BigInt(500),
        "string_QWORD": "15611446313",
        "float_QWORD": 15215123.52415,
        // "max_QWORD2": 0,
    };

    for (let index = 0; index < Object.keys(DWORD_LIST).length; index++) {
        const key = Object.keys(DWORD_LIST)[index];
        const data = DWORD_LIST[key as keyof typeof DWORD_LIST];

        // @ts-ignore
        temp = hmc.Registr.setRegistrDword2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", key, data);

        console.log(`[setRegistrDword2] isPromise-> [ ${isPromise(temp)} ] key[${key}]-> ${data} data-> [ ${await temp} ]`);

        const data_c = hmc.Registr.getRegistrDword2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", key);

        console.log(`[getRegistrDword2] isPromise-> [ ${isPromise(data_c)} ] ( input:: key[${key}]-> ${data} ) getdata-> [ ${await data_c} ]`);

        await hmc.Registr.copyRegistrValue2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", key, "SOFTWARE\\HMC_COPYKEY", key);

    }

    for (let index = 0; index < Object.keys(QWORD_LIST).length; index++) {
        const key = Object.keys(QWORD_LIST)[index];
        const data = QWORD_LIST[key as keyof typeof QWORD_LIST];

        // @ts-ignore
        temp = hmc.Registr.setRegistrQword2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", key, data);

        console.log(`[setRegistrQword2] isPromise-> [ ${isPromise(temp)} ] key[${key}]-> ${data} data-> [ ${await temp} ]`);

        const data_c = hmc.Registr.getRegistrQword2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", key);

        console.log(`[getRegistrQword2] isPromise-> [ ${isPromise(data_c)} ] ( input:: key[${key}]-> ${data} ) getdata-> [ ${await data_c} ]`);

        await hmc.Registr.copyRegistrValue2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", key, "SOFTWARE\\HMC_COPYKEY", key);

    }

    console.log("......................................................................................................................................................");

    // :: ................................................................................................................................................................................................................................................................

    await hmc.Registr.copyRegistrFolder2("HKEY_LOCAL_MACHINE", "SOFTWARE\\HMC", "SOFTWARE\\HMC_COPYKEY");




}