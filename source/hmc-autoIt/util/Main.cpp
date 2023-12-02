
#include "Main.h"

// #pragma comment(lib, "./AutoItX3/AutoItX3_DLL.lib")
// #pragma comment(lib, "./AutoItX3/AutoItX3\\AutoItX3_x64_DLL.lib")

#ifdef _MSC_VER

#ifdef _M_IX86
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_DLL.lib")

#elif defined(_M_X64) || defined(_M_AMD64)
#pragma comment(lib, "F:\\source\\CPP\\hmc-win32\\source\\hmc-autoIt\\AutoItX3\\AutoItX3_x64_DLL.lib")

#endif //_M_IX86
#endif //_MSC_VER

// HMC_CHECK_CATCH
// 在node环境
#ifdef SRC_NODE_API_H_
#define HMC_CHECK_CATCH                        \
    catch (char *err)                          \
    {                                          \
        napi_throw_type_error(env, NULL, err); \
        return NULL;                           \
    }

// 不在node环境
#else
#define HMC_CHECK_CATCH            \
    catch (char *err)              \
    {                              \
        if (HMC_IS_DEUG_COUT == 1) \
        {                          \
            cout << err << "\n";   \
        }                          \
    }
#endif // SRC_NODE_API_H_


    static napi_value nfn_AU3_Init (napi_env env, napi_callback_info info)
{
    try
    {
        fn_AU3_Init(
);
    }
    HMC_CHECK_CATCH;

    return NULL;
}




    static napi_value nfn_AU3_error (napi_env env, napi_callback_info info)
{
    try
    {
        int fn_result = fn_AU3_error(
);
return hmc_napi_util::create_value::Number(env,fn_result);
   

    }
    HMC_CHECK_CATCH;

    return NULL;
}



    
    static napi_value nfn_AU3_AutoItSetOption (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_AutoItSetOption");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_AutoItSetOption( [0] Option type:( wstring  ) \n[1] nValue type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_AutoItSetOption(
/*Option (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*nValue (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}




    static napi_value nfn_AU3_ClipGet (napi_env env, napi_callback_info info)
{
    try
    {
        wstring fn_result = fn_AU3_ClipGet(
);
return hmc_napi_util::create_value::String(env,fn_result);
   

    }
    HMC_CHECK_CATCH;

    return NULL;
}



    
    static napi_value nfn_AU3_ClipPut (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ClipPut");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ClipPut( [0] intput type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_ClipPut(
/*intput (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlClick (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 7;
    napi_value argv[7];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlClick");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:7,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlClick( [0] szTitle type:( wstring  ) \n[1] szText type:( wstring  ) \n[2] szControl type:( wstring  ) \n[3] szButton type:( wstring default:(L\"left\") ) \n[4] nNumClicks type:( int default:(1) ) \n[5] nX type:( int default:(AU3_INTDEFAULT) ) \n[6] nY type:( int default:(AU3_INTDEFAULT) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlClick(
/*szTitle (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*szText (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*szControl (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*szButton (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"left") )
 , 
/*nNumClicks (int) */ hmc_napi_util::get_value::number_int(env, argv[4],1)
 , 
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[5],AU3_INTDEFAULT)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[6],AU3_INTDEFAULT)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlClickByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 6;
    napi_value argv[6];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlClickByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:6,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlClickByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n[2] szButton type:( wstring default:(L\"left\") ) \n[3] nNumClicks type:( int default:(1) ) \n[4] nX type:( int default:(AU3_INTDEFAULT) ) \n[5] nY type:( int default:(AU3_INTDEFAULT) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_ControlClickByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
 , 
/*szButton (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"left") )
 , 
/*nNumClicks (int) */ hmc_napi_util::get_value::number_int(env, argv[3],1)
 , 
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[4],AU3_INTDEFAULT)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[5],AU3_INTDEFAULT)
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlCommand (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 5;
    napi_value argv[5];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlCommand");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  4)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:4, max:5,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlCommand( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n[3] Command type:( wstring  ) \n[4] Extra type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlCommand(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*Command (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
 , 
/*Extra (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlCommandByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 4;
    napi_value argv[4];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlCommandByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:4,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlCommandByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n[2] Command type:( wstring  ) \n[3] Extra type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlCommandByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
 , 
/*Command (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*Extra (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlListView (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 6;
    napi_value argv[6];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlListView");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  6)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:6, max:6,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlListView( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n[3] Command type:( wstring  ) \n[4] Extra1 type:( wstring  ) \n[5] Extra2 type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlListView(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*Command (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
 , 
/*Extra1 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
 , 
/*Extra2 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[5], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlListViewByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 5;
    napi_value argv[5];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlListViewByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  5)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:5, max:5,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlListViewByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n[2] Command type:( wstring  ) \n[3] Extra1 type:( wstring  ) \n[4] Extra2 type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlListViewByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
 , 
/*Command (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*Extra1 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
 , 
/*Extra2 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlDisable (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlDisable");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlDisable( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlDisable(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlDisableByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlDisableByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlDisableByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlDisableByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlEnable (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlEnable");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlEnable( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlEnable(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlEnableByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlEnableByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlEnableByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlEnableByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlFocus (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlFocus");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlFocus( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlFocus(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlFocusByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlFocusByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlFocusByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlFocusByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlGetFocus (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlGetFocus");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlGetFocus( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlGetFocus(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlGetFocusByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlGetFocusByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlGetFocusByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlGetFocusByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlGetHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlGetHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlGetHandle( [0] hWnd type:( HWND  ) \n[1] Control type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        HWND fn_result = fn_AU3_ControlGetHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlGetHandleAsText (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlGetHandleAsText");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlGetHandleAsText( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlGetHandleAsText(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlGetPos (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlGetPos");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlGetPos( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        RECT fn_result = fn_AU3_ControlGetPos(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
result = hmc_napi_util::create_value::Rect(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlGetPosByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlGetPosByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlGetPosByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        RECT fn_result = fn_AU3_ControlGetPosByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
);
result = hmc_napi_util::create_value::Rect(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlGetText (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlGetText");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlGetText( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlGetText(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlGetTextByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlGetTextByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlGetTextByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlGetTextByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlHide (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlHide");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlHide( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlHide(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlHideByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlHideByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlHideByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlHideByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlMove (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 7;
    napi_value argv[7];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlMove");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  5)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:5, max:7,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlMove( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n[3] nX type:( int  ) \n[4] nY type:( int  ) \n[5] nWidth type:( int default:(-1) ) \n[6] nHeight type:( int default:(-1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlMove(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[3],0)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[4],0)
 , 
/*nWidth (int) */ hmc_napi_util::get_value::number_int(env, argv[5],-1)
 , 
/*nHeight (int) */ hmc_napi_util::get_value::number_int(env, argv[6],-1)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlMoveByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 6;
    napi_value argv[6];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlMoveByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  4)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:4, max:6,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlMoveByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n[2] nX type:( int  ) \n[3] nY type:( int  ) \n[4] nWidth type:( int default:(-1) ) \n[5] nHeight type:( int default:(-1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlMoveByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
 , 
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[3],0)
 , 
/*nWidth (int) */ hmc_napi_util::get_value::number_int(env, argv[4],-1)
 , 
/*nHeight (int) */ hmc_napi_util::get_value::number_int(env, argv[5],-1)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlSend (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 5;
    napi_value argv[5];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlSend");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  4)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:4, max:5,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlSend( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n[3] SendText type:( wstring  ) \n[4] nMode type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlSend(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*SendText (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
 , 
/*nMode (int) */ hmc_napi_util::get_value::number_int(env, argv[4],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlSendByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 4;
    napi_value argv[4];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlSendByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:4,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlSendByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n[2] SendText type:( wstring  ) \n[3] nMode type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlSendByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
 , 
/*SendText (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*nMode (int) */ hmc_napi_util::get_value::number_int(env, argv[3],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlSetText (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 4;
    napi_value argv[4];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlSetText");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  4)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:4, max:4,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlSetText( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n[3] ControlText type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlSetText(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*ControlText (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlSetTextByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlSetTextByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlSetTextByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n[2] SendText type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlSetTextByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
 , 
/*SendText (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlShow (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlShow");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlShow( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlShow(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlShowByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlShowByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlShowByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ControlShowByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlTreeView (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 6;
    napi_value argv[6];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlTreeView");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  6)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:6, max:6,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlTreeView( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Control type:( wstring  ) \n[3] Command type:( wstring  ) \n[4] Extra1 type:( wstring  ) \n[5] Extra2 type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlTreeView(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Control (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*Command (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
 , 
/*Extra1 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
 , 
/*Extra2 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[5], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ControlTreeViewByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 5;
    napi_value argv[5];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ControlTreeViewByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  5)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:5, max:5,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ControlTreeViewByHandle( [0] hWnd type:( HWND  ) \n[1] hCtrl type:( HWND  ) \n[2] Command type:( wstring  ) \n[3] Extra1 type:( wstring  ) \n[4] Extra2 type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_ControlTreeViewByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*hCtrl (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[1])
 , 
/*Command (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*Extra1 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
 , 
/*Extra2 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_DriveMapAdd (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 5;
    napi_value argv[5];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_DriveMapAdd");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:5,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_DriveMapAdd( [0] Device type:( wstring  ) \n[1] Share type:( wstring  ) \n[2] nFlags type:( int  ) \n[3] User type:( wstring default:(L\"\") ) \n[4] Pwd type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_DriveMapAdd(
/*Device (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Share (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nFlags (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
 , 
/*User (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
 , 
/*Pwd (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_DriveMapDel (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_DriveMapDel");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_DriveMapDel( [0] Device type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_DriveMapDel(
/*Device (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_DriveMapGet (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_DriveMapGet");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_DriveMapGet( [0] Device type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_DriveMapGet(
/*Device (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}




    static napi_value nfn_AU3_IsAdmin (napi_env env, napi_callback_info info)
{
    try
    {
        bool fn_result = fn_AU3_IsAdmin(
);
return hmc_napi_util::create_value::Boolean(env,fn_result);
   

    }
    HMC_CHECK_CATCH;

    return NULL;
}



    
    static napi_value nfn_AU3_MouseClick (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 5;
    napi_value argv[5];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_MouseClick");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  0)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:0, max:5,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_MouseClick( [0] Button type:( wstring default:(L\"LEFT\") ) \n[1] nX type:( int default:(AU3_INTDEFAULT) ) \n[2] nY type:( int default:(AU3_INTDEFAULT) ) \n[3] nClicks type:( int default:(1) ) \n[4] nSpeed type:( int default:(-1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_MouseClick(
/*Button (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"LEFT") )
 , 
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[1],AU3_INTDEFAULT)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[2],AU3_INTDEFAULT)
 , 
/*nClicks (int) */ hmc_napi_util::get_value::number_int(env, argv[3],1)
 , 
/*nSpeed (int) */ hmc_napi_util::get_value::number_int(env, argv[4],-1)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_MouseClickDrag (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 6;
    napi_value argv[6];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_MouseClickDrag");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  5)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:5, max:6,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_MouseClickDrag( [0] Button type:( wstring  ) \n[1] nX1 type:( int  ) \n[2] nY1 type:( int  ) \n[3] nX2 type:( int  ) \n[4] nY2 type:( int  ) \n[5] nSpeed type:( int default:(-1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_MouseClickDrag(
/*Button (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*nX1 (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
 , 
/*nY1 (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
 , 
/*nX2 (int) */ hmc_napi_util::get_value::number_int(env, argv[3],0)
 , 
/*nY2 (int) */ hmc_napi_util::get_value::number_int(env, argv[4],0)
 , 
/*nSpeed (int) */ hmc_napi_util::get_value::number_int(env, argv[5],-1)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_MouseDown (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_MouseDown");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  0)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:0, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_MouseDown( [0] Button type:( wstring default:(L\"LEFT\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_MouseDown(
/*Button (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"LEFT") )
);
    }
    HMC_CHECK_CATCH;
    return result;
}




    static napi_value nfn_AU3_MouseGetCursor (napi_env env, napi_callback_info info)
{
    try
    {
        int fn_result = fn_AU3_MouseGetCursor(
);
return hmc_napi_util::create_value::Number(env,fn_result);
   

    }
    HMC_CHECK_CATCH;

    return NULL;
}




    static napi_value nfn_AU3_MouseGetPos (napi_env env, napi_callback_info info)
{
    try
    {
        POINT fn_result = fn_AU3_MouseGetPos(
);
return hmc_napi_util::create_value::Point(env,fn_result);
   

    }
    HMC_CHECK_CATCH;

    return NULL;
}



    
    static napi_value nfn_AU3_MouseMove (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_MouseMove");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_MouseMove( [0] nX type:( int  ) \n[1] nY type:( int  ) \n[2] nSpeed type:( int default:(-1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_MouseMove(
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[0],0)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
 , 
/*nSpeed (int) */ hmc_napi_util::get_value::number_int(env, argv[2],-1)
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_MouseUp (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_MouseUp");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  0)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:0, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_MouseUp( [0] Button type:( wstring default:(L\"LEFT\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_MouseUp(
/*Button (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"LEFT") )
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_MouseWheel (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_MouseWheel");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_MouseWheel( [0] Direction type:( wstring  ) \n[1] nClicks type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_MouseWheel(
/*Direction (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*nClicks (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_Opt (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_Opt");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_Opt( [0] Option type:( wstring  ) \n[1] nValue type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_Opt(
/*Option (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*nValue (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_PixelChecksum (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_PixelChecksum");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_PixelChecksum( [0] lpRect type:( LPRECT  ) \n[1] nStep type:( int default:(1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        unsigned int fn_result = fn_AU3_PixelChecksum(
/*lpRect (LPRECT) */ hmc_napi_util::get_value::lprect(env, argv[0]) 
 , 
/*nStep (int) */ hmc_napi_util::get_value::number_int(env, argv[1],1)
);
result = hmc_napi_util::create_value::Number(env,(int)fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_PixelGetColor (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_PixelGetColor");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_PixelGetColor( [0] nX type:( int  ) \n[1] nY type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_PixelGetColor(
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[0],0)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_PixelSearch (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 4;
    napi_value argv[4];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_PixelSearch");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:4,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_PixelSearch( [0] lpRect type:( LPRECT  ) \n[1] nCol type:( int  ) \n[2] nVar type:( int default:(0) ) \n[3] nStep type:( int default:(1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        POINT fn_result = fn_AU3_PixelSearch(
/*lpRect (LPRECT) */ hmc_napi_util::get_value::lprect(env, argv[0]) 
 , 
/*nCol (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
 , 
/*nVar (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
 , 
/*nStep (int) */ hmc_napi_util::get_value::number_int(env, argv[3],1)
);
result = hmc_napi_util::create_value::Point(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ProcessClose (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ProcessClose");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ProcessClose( [0] Process type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_ProcessClose(
/*Process (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ProcessExists (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ProcessExists");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ProcessExists( [0] Process type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ProcessExists(
/*Process (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ProcessSetPriority (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ProcessSetPriority");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ProcessSetPriority( [0] Process type:( wstring  ) \n[1] nPriority type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ProcessSetPriority(
/*Process (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*nPriority (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ProcessWait (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ProcessWait");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ProcessWait( [0] Process type:( wstring  ) \n[1] nTimeout type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ProcessWait(
/*Process (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ProcessWaitClose (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ProcessWaitClose");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ProcessWaitClose( [0] Process type:( wstring  ) \n[1] nTimeout type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_ProcessWaitClose(
/*Process (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_Run (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_Run");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_Run( [0] Program type:( wstring  ) \n[1] Dir type:( wstring default:(L\"\") ) \n[2] nShowFlag type:( int default:(SW_SHOWNORMAL) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_Run(
/*Program (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Dir (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nShowFlag (int) */ hmc_napi_util::get_value::number_int(env, argv[2],SW_SHOWNORMAL)
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_RunWait (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_RunWait");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_RunWait( [0] Program type:( wstring  ) \n[1] Dir type:( wstring default:(L\"\") ) \n[2] nShowFlag type:( int default:(SW_SHOWNORMAL) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_RunWait(
/*Program (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Dir (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nShowFlag (int) */ hmc_napi_util::get_value::number_int(env, argv[2],SW_SHOWNORMAL)
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_RunAs (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 7;
    napi_value argv[7];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_RunAs");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  5)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:5, max:7,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_RunAs( [0] User type:( wstring  ) \n[1] Domain type:( wstring  ) \n[2] Password type:( wstring  ) \n[3] nLogonFlag type:( int  ) \n[4] Program type:( wstring  ) \n[5] Dir type:( wstring default:(L\"\") ) \n[6] nShowFlag type:( int default:(SW_SHOWNORMAL) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_RunAs(
/*User (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Domain (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Password (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*nLogonFlag (int) */ hmc_napi_util::get_value::number_int(env, argv[3],0)
 , 
/*Program (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
 , 
/*Dir (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[5], wstring(L"") )
 , 
/*nShowFlag (int) */ hmc_napi_util::get_value::number_int(env, argv[6],SW_SHOWNORMAL)
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_RunAsWait (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 7;
    napi_value argv[7];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_RunAsWait");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  5)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:5, max:7,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_RunAsWait( [0] User type:( wstring  ) \n[1] Domain type:( wstring  ) \n[2] Password type:( wstring  ) \n[3] nLogonFlag type:( int  ) \n[4] Program type:( wstring  ) \n[5] Dir type:( wstring default:(L\"\") ) \n[6] nShowFlag type:( int default:(SW_SHOWNORMAL) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_RunAsWait(
/*User (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Domain (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Password (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*nLogonFlag (int) */ hmc_napi_util::get_value::number_int(env, argv[3],0)
 , 
/*Program (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
 , 
/*Dir (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[5], wstring(L"") )
 , 
/*nShowFlag (int) */ hmc_napi_util::get_value::number_int(env, argv[6],SW_SHOWNORMAL)
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_Send (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_Send");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_Send( [0] SendText type:( wstring  ) \n[1] nMode type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_Send(
/*SendText (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*nMode (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_Shutdown (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_Shutdown");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_Shutdown( [0] nFlags type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_Shutdown(
/*nFlags (int) */ hmc_napi_util::get_value::number_int(env, argv[0],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_Sleep (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_Sleep");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_Sleep( [0] nMilliseconds type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_Sleep(
/*nMilliseconds (int) */ hmc_napi_util::get_value::number_int(env, argv[0],0)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_StatusbarGetText (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_StatusbarGetText");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  0)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:0, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_StatusbarGetText( [0] Title type:( wstring default:(L\"\") ) \n[1] Text type:( wstring default:(L\"\") ) \n[2] nPart type:( int default:(1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_StatusbarGetText(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nPart (int) */ hmc_napi_util::get_value::number_int(env, argv[2],1)
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_StatusbarGetTextByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_StatusbarGetTextByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_StatusbarGetTextByHandle( [0] hWnd type:( HWND  ) \n[1] nPart type:( int default:(1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_StatusbarGetTextByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*nPart (int) */ hmc_napi_util::get_value::number_int(env, argv[1],1)
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_ToolTip (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_ToolTip");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_ToolTip( [0] Tip type:( wstring  ) \n[1] nX type:( int default:(AU3_INTDEFAULT) ) \n[2] nY type:( int default:(AU3_INTDEFAULT) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_ToolTip(
/*Tip (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[1],AU3_INTDEFAULT)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[2],AU3_INTDEFAULT)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinActivate (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinActivate");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinActivate( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinActivate(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinActivateByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinActivateByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinActivateByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinActivateByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinActive (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinActive");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinActive( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinActive(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinActiveByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinActiveByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinActiveByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinActiveByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinClose (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinClose");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinClose( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinClose(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinCloseByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinCloseByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinCloseByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinCloseByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinExists (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinExists");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinExists( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinExists(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinExistsByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinExistsByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinExistsByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinExistsByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}




    static napi_value nfn_AU3_WinGetCaretPos (napi_env env, napi_callback_info info)
{
    try
    {
        POINT fn_result = fn_AU3_WinGetCaretPos(
);
return hmc_napi_util::create_value::Point(env,fn_result);
   

    }
    HMC_CHECK_CATCH;

    return NULL;
}



    
    static napi_value nfn_AU3_WinGetClassList (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetClassList");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetClassList( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_WinGetClassList(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetClassListByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetClassListByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetClassListByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_WinGetClassListByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetClientSize (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetClientSize");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetClientSize( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        RECT fn_result = fn_AU3_WinGetClientSize(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Rect(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetClientSizeByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetClientSizeByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetClientSizeByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        RECT fn_result = fn_AU3_WinGetClientSizeByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::Rect(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetHandle( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        HWND fn_result = fn_AU3_WinGetHandle(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetHandleAsText (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetHandleAsText");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetHandleAsText( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_WinGetHandleAsText(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetPos (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetPos");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetPos( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        RECT fn_result = fn_AU3_WinGetPos(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Rect(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetPosByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetPosByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetPosByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        RECT fn_result = fn_AU3_WinGetPosByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::Rect(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetProcess (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetProcess");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetProcess( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        DWORD fn_result = fn_AU3_WinGetProcess(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);

 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetProcessByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetProcessByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetProcessByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        DWORD fn_result = fn_AU3_WinGetProcessByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);

 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetState (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetState");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetState( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_WinGetState(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetStateByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetStateByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetStateByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        int fn_result = fn_AU3_WinGetStateByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::Number(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetText (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetText");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetText( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_WinGetText(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetTextByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetTextByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetTextByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_WinGetTextByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetTitle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetTitle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetTitle( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_WinGetTitle(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinGetTitleByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinGetTitleByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinGetTitleByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        wstring fn_result = fn_AU3_WinGetTitleByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::String(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinKill (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinKill");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinKill( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinKill(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinKillByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinKillByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:1,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinKillByHandle( [0] hWnd type:( HWND  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinKillByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinMenuSelectItem (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 10;
    napi_value argv[10];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinMenuSelectItem");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  10)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:10, max:10,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinMenuSelectItem( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] Item1 type:( wstring  ) \n[3] Item2 type:( wstring  ) \n[4] Item3 type:( wstring  ) \n[5] Item4 type:( wstring  ) \n[6] Item5 type:( wstring  ) \n[7] Item6 type:( wstring  ) \n[8] Item7 type:( wstring  ) \n[9] Item8 type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinMenuSelectItem(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Item1 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*Item2 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
 , 
/*Item3 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
 , 
/*Item4 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[5], wstring(L"") )
 , 
/*Item5 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[6], wstring(L"") )
 , 
/*Item6 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[7], wstring(L"") )
 , 
/*Item7 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[8], wstring(L"") )
 , 
/*Item8 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[9], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinMenuSelectItemByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 9;
    napi_value argv[9];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinMenuSelectItemByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  9)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:9, max:9,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinMenuSelectItemByHandle( [0] hWnd type:( HWND  ) \n[1] Item1 type:( wstring  ) \n[2] Item2 type:( wstring  ) \n[3] Item3 type:( wstring  ) \n[4] Item4 type:( wstring  ) \n[5] Item5 type:( wstring  ) \n[6] Item6 type:( wstring  ) \n[7] Item7 type:( wstring  ) \n[8] Item8 type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinMenuSelectItemByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*Item1 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*Item2 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
 , 
/*Item3 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[3], wstring(L"") )
 , 
/*Item4 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[4], wstring(L"") )
 , 
/*Item5 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[5], wstring(L"") )
 , 
/*Item6 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[6], wstring(L"") )
 , 
/*Item7 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[7], wstring(L"") )
 , 
/*Item8 (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[8], wstring(L"") )
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}




    static napi_value nfn_AU3_WinMinimizeAll (napi_env env, napi_callback_info info)
{
    try
    {
        fn_AU3_WinMinimizeAll(
);
    }
    HMC_CHECK_CATCH;

    return NULL;
}




    static napi_value nfn_AU3_WinMinimizeAllUndo (napi_env env, napi_callback_info info)
{
    try
    {
        fn_AU3_WinMinimizeAllUndo(
);
    }
    HMC_CHECK_CATCH;

    return NULL;
}



    
    static napi_value nfn_AU3_WinMove (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 6;
    napi_value argv[6];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinMove");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  4)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:4, max:6,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinMove( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] nX type:( int  ) \n[3] nY type:( int  ) \n[4] nWidth type:( int default:(-1) ) \n[5] nHeight type:( int default:(-1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_WinMove(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[3],0)
 , 
/*nWidth (int) */ hmc_napi_util::get_value::number_int(env, argv[4],-1)
 , 
/*nHeight (int) */ hmc_napi_util::get_value::number_int(env, argv[5],-1)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinMoveByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 5;
    napi_value argv[5];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinMoveByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:5,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinMoveByHandle( [0] hWnd type:( HWND  ) \n[1] nX type:( int  ) \n[2] nY type:( int  ) \n[3] nWidth type:( int default:(-1) ) \n[4] nHeight type:( int default:(-1) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_WinMoveByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*nX (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
 , 
/*nY (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
 , 
/*nWidth (int) */ hmc_napi_util::get_value::number_int(env, argv[3],-1)
 , 
/*nHeight (int) */ hmc_napi_util::get_value::number_int(env, argv[4],-1)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinSetOnTop (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinSetOnTop");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinSetOnTop( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] nFlag type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_WinSetOnTop(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nFlag (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinSetOnTopByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinSetOnTopByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinSetOnTopByHandle( [0] hWnd type:( HWND  ) \n[1] nFlag type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_WinSetOnTopByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*nFlag (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinSetState (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinSetState");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinSetState( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] nFlags type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_WinSetState(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nFlags (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinSetStateByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinSetStateByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinSetStateByHandle( [0] hWnd type:( HWND  ) \n[1] nFlags type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_WinSetStateByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*nFlags (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinSetTitle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinSetTitle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  3)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:3, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinSetTitle( [0] Title type:( wstring  ) \n[1] Text type:( wstring  ) \n[2] NewTitle type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_WinSetTitle(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*NewTitle (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[2], wstring(L"") )
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinSetTitleByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinSetTitleByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinSetTitleByHandle( [0] hWnd type:( HWND  ) \n[1] NewTitle type:( wstring  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        fn_AU3_WinSetTitleByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*NewTitle (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
);
    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinSetTrans (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinSetTrans");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinSetTrans( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n[2] nTrans type:( int default:(255) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinSetTrans(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nTrans (int) */ hmc_napi_util::get_value::number_int(env, argv[2],255)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinSetTransByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinSetTransByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinSetTransByHandle( [0] hWnd type:( HWND  ) \n[1] nTrans type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinSetTransByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*nTrans (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinWait (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinWait");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinWait( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n[2] nTimeout type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinWait(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinWaitByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinWaitByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinWaitByHandle( [0] hWnd type:( HWND  ) \n[1] nTimeout type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinWaitByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinWaitActive (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinWaitActive");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinWaitActive( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n[2] nTimeout type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinWaitActive(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinWaitActiveByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinWaitActiveByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinWaitActiveByHandle( [0] hWnd type:( HWND  ) \n[1] nTimeout type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinWaitActiveByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinWaitClose (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinWaitClose");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinWaitClose( [0] Title type:( wstring  ) \n[1] Text type:( wstring default:(L\"\") ) \n[2] nTimeout type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinWaitClose(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinWaitCloseByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinWaitCloseByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  2)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:2, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinWaitCloseByHandle( [0] hWnd type:( HWND  ) \n[1] nTimeout type:( int  ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinWaitCloseByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinWaitNotActive (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 3;
    napi_value argv[3];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinWaitNotActive");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  0)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:0, max:3,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinWaitNotActive( [0] Title type:( wstring default:(L\"\") ) \n[1] Text type:( wstring default:(L\"\") ) \n[2] nTimeout type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinWaitNotActive(
/*Title (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[0], wstring(L"") )
 , 
/*Text (wstring) */ hmc_napi_util::get_value::string_utf16(env, argv[1], wstring(L"") )
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[2],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



    
    static napi_value nfn_AU3_WinWaitNotActiveByHandle (napi_env env, napi_callback_info info)
{
    napi_status status;
    size_t argc = 2;
    napi_value argv[2];
    napi_value result;
    
    if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok) 
    {                                                                       
        napi_throw_type_error(env, NULL, "fn_AU3_WinWaitNotActiveByHandle");           
        return NULL;                                                        
    }
    napi_get_undefined(env, &result);

    try
    {
        if (argc <  1)
        {
            string info_mag = "Incorrect parameters Please pay attention to the parameter format and parameters args: {min:1, max:2,the_argc:";
            info_mag.append(to_string(argc));
            info_mag.append(",target:");
            info_mag.append("fn_AU3_WinWaitNotActiveByHandle( [0] hWnd type:( HWND  ) \n[1] nTimeout type:( int default:(0) ) \n )");
            info_mag.append("}");
            napi_throw_type_error(env, NULL,info_mag.c_str());
            return NULL;
        }

        bool fn_result = fn_AU3_WinWaitNotActiveByHandle(
/*hWnd (HWND) */ hmc_napi_util::get_value::number_HWND(env, argv[0])
 , 
/*nTimeout (int) */ hmc_napi_util::get_value::number_int(env, argv[1],0)
);
result = hmc_napi_util::create_value::Boolean(env,fn_result);
 return result;  

    }
    HMC_CHECK_CATCH;
    return result;
}



static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor BIND_NAPI_METHOD[] = {DECLARE_NAPI_METHOD("Init", nfn_AU3_Init),
DECLARE_NAPI_METHOD("error", nfn_AU3_error),
DECLARE_NAPI_METHOD("AutoItSetOption", nfn_AU3_AutoItSetOption),
DECLARE_NAPI_METHOD("ClipGet", nfn_AU3_ClipGet),
DECLARE_NAPI_METHOD("ClipPut", nfn_AU3_ClipPut),
DECLARE_NAPI_METHOD("ControlClick", nfn_AU3_ControlClick),
DECLARE_NAPI_METHOD("ControlClickByHandle", nfn_AU3_ControlClickByHandle),
DECLARE_NAPI_METHOD("ControlCommand", nfn_AU3_ControlCommand),
DECLARE_NAPI_METHOD("ControlCommandByHandle", nfn_AU3_ControlCommandByHandle),
DECLARE_NAPI_METHOD("ControlListView", nfn_AU3_ControlListView),
DECLARE_NAPI_METHOD("ControlListViewByHandle", nfn_AU3_ControlListViewByHandle),
DECLARE_NAPI_METHOD("ControlDisable", nfn_AU3_ControlDisable),
DECLARE_NAPI_METHOD("ControlDisableByHandle", nfn_AU3_ControlDisableByHandle),
DECLARE_NAPI_METHOD("ControlEnable", nfn_AU3_ControlEnable),
DECLARE_NAPI_METHOD("ControlEnableByHandle", nfn_AU3_ControlEnableByHandle),
DECLARE_NAPI_METHOD("ControlFocus", nfn_AU3_ControlFocus),
DECLARE_NAPI_METHOD("ControlFocusByHandle", nfn_AU3_ControlFocusByHandle),
DECLARE_NAPI_METHOD("ControlGetFocus", nfn_AU3_ControlGetFocus),
DECLARE_NAPI_METHOD("ControlGetFocusByHandle", nfn_AU3_ControlGetFocusByHandle),
DECLARE_NAPI_METHOD("ControlGetHandle", nfn_AU3_ControlGetHandle),
DECLARE_NAPI_METHOD("ControlGetHandleAsText", nfn_AU3_ControlGetHandleAsText),
DECLARE_NAPI_METHOD("ControlGetPos", nfn_AU3_ControlGetPos),
DECLARE_NAPI_METHOD("ControlGetPosByHandle", nfn_AU3_ControlGetPosByHandle),
DECLARE_NAPI_METHOD("ControlGetText", nfn_AU3_ControlGetText),
DECLARE_NAPI_METHOD("ControlGetTextByHandle", nfn_AU3_ControlGetTextByHandle),
DECLARE_NAPI_METHOD("ControlHide", nfn_AU3_ControlHide),
DECLARE_NAPI_METHOD("ControlHideByHandle", nfn_AU3_ControlHideByHandle),
DECLARE_NAPI_METHOD("ControlMove", nfn_AU3_ControlMove),
DECLARE_NAPI_METHOD("ControlMoveByHandle", nfn_AU3_ControlMoveByHandle),
DECLARE_NAPI_METHOD("ControlSend", nfn_AU3_ControlSend),
DECLARE_NAPI_METHOD("ControlSendByHandle", nfn_AU3_ControlSendByHandle),
DECLARE_NAPI_METHOD("ControlSetText", nfn_AU3_ControlSetText),
DECLARE_NAPI_METHOD("ControlSetTextByHandle", nfn_AU3_ControlSetTextByHandle),
DECLARE_NAPI_METHOD("ControlShow", nfn_AU3_ControlShow),
DECLARE_NAPI_METHOD("ControlShowByHandle", nfn_AU3_ControlShowByHandle),
DECLARE_NAPI_METHOD("ControlTreeView", nfn_AU3_ControlTreeView),
DECLARE_NAPI_METHOD("ControlTreeViewByHandle", nfn_AU3_ControlTreeViewByHandle),
DECLARE_NAPI_METHOD("DriveMapAdd", nfn_AU3_DriveMapAdd),
DECLARE_NAPI_METHOD("DriveMapDel", nfn_AU3_DriveMapDel),
DECLARE_NAPI_METHOD("DriveMapGet", nfn_AU3_DriveMapGet),
DECLARE_NAPI_METHOD("IsAdmin", nfn_AU3_IsAdmin),
DECLARE_NAPI_METHOD("MouseClick", nfn_AU3_MouseClick),
DECLARE_NAPI_METHOD("MouseClickDrag", nfn_AU3_MouseClickDrag),
DECLARE_NAPI_METHOD("MouseDown", nfn_AU3_MouseDown),
DECLARE_NAPI_METHOD("MouseGetCursor", nfn_AU3_MouseGetCursor),
DECLARE_NAPI_METHOD("MouseGetPos", nfn_AU3_MouseGetPos),
DECLARE_NAPI_METHOD("MouseMove", nfn_AU3_MouseMove),
DECLARE_NAPI_METHOD("MouseUp", nfn_AU3_MouseUp),
DECLARE_NAPI_METHOD("MouseWheel", nfn_AU3_MouseWheel),
DECLARE_NAPI_METHOD("Opt", nfn_AU3_Opt),
DECLARE_NAPI_METHOD("PixelChecksum", nfn_AU3_PixelChecksum),
DECLARE_NAPI_METHOD("PixelGetColor", nfn_AU3_PixelGetColor),
DECLARE_NAPI_METHOD("PixelSearch", nfn_AU3_PixelSearch),
DECLARE_NAPI_METHOD("ProcessClose", nfn_AU3_ProcessClose),
DECLARE_NAPI_METHOD("ProcessExists", nfn_AU3_ProcessExists),
DECLARE_NAPI_METHOD("ProcessSetPriority", nfn_AU3_ProcessSetPriority),
DECLARE_NAPI_METHOD("ProcessWait", nfn_AU3_ProcessWait),
DECLARE_NAPI_METHOD("ProcessWaitClose", nfn_AU3_ProcessWaitClose),
DECLARE_NAPI_METHOD("Run", nfn_AU3_Run),
DECLARE_NAPI_METHOD("RunWait", nfn_AU3_RunWait),
DECLARE_NAPI_METHOD("RunAs", nfn_AU3_RunAs),
DECLARE_NAPI_METHOD("RunAsWait", nfn_AU3_RunAsWait),
DECLARE_NAPI_METHOD("Send", nfn_AU3_Send),
DECLARE_NAPI_METHOD("Shutdown", nfn_AU3_Shutdown),
DECLARE_NAPI_METHOD("Sleep", nfn_AU3_Sleep),
DECLARE_NAPI_METHOD("StatusbarGetText", nfn_AU3_StatusbarGetText),
DECLARE_NAPI_METHOD("StatusbarGetTextByHandle", nfn_AU3_StatusbarGetTextByHandle),
DECLARE_NAPI_METHOD("ToolTip", nfn_AU3_ToolTip),
DECLARE_NAPI_METHOD("WinActivate", nfn_AU3_WinActivate),
DECLARE_NAPI_METHOD("WinActivateByHandle", nfn_AU3_WinActivateByHandle),
DECLARE_NAPI_METHOD("WinActive", nfn_AU3_WinActive),
DECLARE_NAPI_METHOD("WinActiveByHandle", nfn_AU3_WinActiveByHandle),
DECLARE_NAPI_METHOD("WinClose", nfn_AU3_WinClose),
DECLARE_NAPI_METHOD("WinCloseByHandle", nfn_AU3_WinCloseByHandle),
DECLARE_NAPI_METHOD("WinExists", nfn_AU3_WinExists),
DECLARE_NAPI_METHOD("WinExistsByHandle", nfn_AU3_WinExistsByHandle),
DECLARE_NAPI_METHOD("WinGetCaretPos", nfn_AU3_WinGetCaretPos),
DECLARE_NAPI_METHOD("WinGetClassList", nfn_AU3_WinGetClassList),
DECLARE_NAPI_METHOD("WinGetClassListByHandle", nfn_AU3_WinGetClassListByHandle),
DECLARE_NAPI_METHOD("WinGetClientSize", nfn_AU3_WinGetClientSize),
DECLARE_NAPI_METHOD("WinGetClientSizeByHandle", nfn_AU3_WinGetClientSizeByHandle),
DECLARE_NAPI_METHOD("WinGetHandle", nfn_AU3_WinGetHandle),
DECLARE_NAPI_METHOD("WinGetHandleAsText", nfn_AU3_WinGetHandleAsText),
DECLARE_NAPI_METHOD("WinGetPos", nfn_AU3_WinGetPos),
DECLARE_NAPI_METHOD("WinGetPosByHandle", nfn_AU3_WinGetPosByHandle),
DECLARE_NAPI_METHOD("WinGetProcess", nfn_AU3_WinGetProcess),
DECLARE_NAPI_METHOD("WinGetProcessByHandle", nfn_AU3_WinGetProcessByHandle),
DECLARE_NAPI_METHOD("WinGetState", nfn_AU3_WinGetState),
DECLARE_NAPI_METHOD("WinGetStateByHandle", nfn_AU3_WinGetStateByHandle),
DECLARE_NAPI_METHOD("WinGetText", nfn_AU3_WinGetText),
DECLARE_NAPI_METHOD("WinGetTextByHandle", nfn_AU3_WinGetTextByHandle),
DECLARE_NAPI_METHOD("WinGetTitle", nfn_AU3_WinGetTitle),
DECLARE_NAPI_METHOD("WinGetTitleByHandle", nfn_AU3_WinGetTitleByHandle),
DECLARE_NAPI_METHOD("WinKill", nfn_AU3_WinKill),
DECLARE_NAPI_METHOD("WinKillByHandle", nfn_AU3_WinKillByHandle),
DECLARE_NAPI_METHOD("WinMenuSelectItem", nfn_AU3_WinMenuSelectItem),
DECLARE_NAPI_METHOD("WinMenuSelectItemByHandle", nfn_AU3_WinMenuSelectItemByHandle),
DECLARE_NAPI_METHOD("WinMinimizeAll", nfn_AU3_WinMinimizeAll),
DECLARE_NAPI_METHOD("WinMinimizeAllUndo", nfn_AU3_WinMinimizeAllUndo),
DECLARE_NAPI_METHOD("WinMove", nfn_AU3_WinMove),
DECLARE_NAPI_METHOD("WinMoveByHandle", nfn_AU3_WinMoveByHandle),
DECLARE_NAPI_METHOD("WinSetOnTop", nfn_AU3_WinSetOnTop),
DECLARE_NAPI_METHOD("WinSetOnTopByHandle", nfn_AU3_WinSetOnTopByHandle),
DECLARE_NAPI_METHOD("WinSetState", nfn_AU3_WinSetState),
DECLARE_NAPI_METHOD("WinSetStateByHandle", nfn_AU3_WinSetStateByHandle),
DECLARE_NAPI_METHOD("WinSetTitle", nfn_AU3_WinSetTitle),
DECLARE_NAPI_METHOD("WinSetTitleByHandle", nfn_AU3_WinSetTitleByHandle),
DECLARE_NAPI_METHOD("WinSetTrans", nfn_AU3_WinSetTrans),
DECLARE_NAPI_METHOD("WinSetTransByHandle", nfn_AU3_WinSetTransByHandle),
DECLARE_NAPI_METHOD("WinWait", nfn_AU3_WinWait),
DECLARE_NAPI_METHOD("WinWaitByHandle", nfn_AU3_WinWaitByHandle),
DECLARE_NAPI_METHOD("WinWaitActive", nfn_AU3_WinWaitActive),
DECLARE_NAPI_METHOD("WinWaitActiveByHandle", nfn_AU3_WinWaitActiveByHandle),
DECLARE_NAPI_METHOD("WinWaitClose", nfn_AU3_WinWaitClose),
DECLARE_NAPI_METHOD("WinWaitCloseByHandle", nfn_AU3_WinWaitCloseByHandle),
DECLARE_NAPI_METHOD("WinWaitNotActive", nfn_AU3_WinWaitNotActive),
DECLARE_NAPI_METHOD("WinWaitNotActiveByHandle", nfn_AU3_WinWaitNotActiveByHandle),
};
    napi_define_properties(env, exports, sizeof(BIND_NAPI_METHOD) / sizeof(BIND_NAPI_METHOD[0]), BIND_NAPI_METHOD);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);

