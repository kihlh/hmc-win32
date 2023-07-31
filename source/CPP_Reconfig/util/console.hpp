#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <chrono>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <any>
#include <unordered_map>
#include <set>
using namespace std;

#define MALLOC(variable) HeapAlloc(GetProcessHeap(), 0, (variable))
#define FREE(variable) HeapFree(GetProcessHeap(), 0, (variable))

namespace hmc_console
{
    // ::-------^_^--------::
    /*设置优先级 error > warn > debug > info ,  all = true */
    namespace level
    {
        typedef enum
        {
            error = 8009,
            warn = 8008,
            debug = 8007,
            info = 8000,
            all = 0,
            stop = 99999
        } level;
    }

    // 红色
    const int COLOR_RED = 12;
    // 绿色
    const int COLOR_GREEN = 10;
    // 蓝色
    const int COLOR_BLUE = 9;
    // 默认
    const int COLOR_DEFAULT = 7;

    // ::-------^_^--------::
    bool _is_tofile = false;
    bool _is_cout = false;
    int _file_level = 0;
    int _cout_level = 0;

    // 用来技术执行用时的
    unordered_map<string, chrono::high_resolution_clock::time_point> _startTimeList;

    string _tofilePath = "hmc_debug.log";
    ofstream logFile;
    string escapeJson(const string &input)
    {
        string output;
        for (char ch : input)
        {
            switch (ch)
            {
            case '\"':
                output.append("\\\"");
                break;
            case '\\':
                output.append("\\\\");
                break;
            case '\b':
                output.append("\\b");
                break;
            case '\f':
                output.append("\\f");
                break;
            case '\n':
                output.append("\\n");
                break;
            case '\r':
                output.append("\\r");
                break;
            case '\t':
                output.append("\\t");
                break;
            default:
                output.push_back(ch);
                break;
            }
        }
        return output;
    }

    /**
     * @brief 获取时间戳
     *
     * @return string
     */
    string get_time()
    {

        auto now = chrono::system_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;

        time_t now_time_t = chrono::system_clock::to_time_t(now);
        tm tm_time;
#ifdef _WIN32
        localtime_s(&tm_time, &now_time_t);
#else
        localtime_r(&now_time_t, &tm_time);
#endif

        char buffer[30];
        strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S", &tm_time);

        // 添加毫秒部分，保证显示三位数并在前面补零
        string msStr = to_string(ms.count());
        msStr = string(3 - msStr.length(), '0') + msStr;
        string timestampWithMilliseconds = buffer + string(".") + msStr + "]";

        return timestampWithMilliseconds;
    }

    /**
     * @brief 判断是否打印内容到控制台
     *
     * @param level
     * @return true
     * @return false
     */
    bool _is_cout_log(level::level level)
    {
        if (!_is_cout)
            return false;
        if (level != 0 && _cout_level != 0 && level < _cout_level)
            return false;
        return true;
    }

    /**
     * @brief 判断是否运行将日志输出到文件
     *
     * @param level
     * @return true
     * @return false
     */
    bool _is_file_log(level::level level)
    {
        if (!_is_tofile)
            return false;
        if (level != 0 && _file_level != 0 && level < _file_level)
            return false;

        return true;
    }

    /**
     * @brief 打印到控制台中
     *
     * @param level
     * @param locaName
     * @param message
     */
    void _coutLine(level::level level, string locaName, string message)
    {

        if (!_is_cout_log(level))
            return;
        try
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            try
            {

                // [2023-06-17 01:21:11.245] [info]   [Main]   message
                string messageLine = get_time();
                messageLine.append(" ");

                switch (level)
                {
                    // error = 8005,
                    // warn = 8006,
                    // info = 8008,
                    // debug = 8001,
                case level::error:
                {
                    messageLine.append("[ERROR]  ");
                    SetConsoleTextAttribute(hConsole, COLOR_RED);
                    break;
                }
                case level::warn:
                {
                    messageLine.append("[WARN]   ");
                    SetConsoleTextAttribute(hConsole, COLOR_GREEN);
                    break;
                }
                case level::debug:
                {
                    messageLine.append("[DEBUG]  ");
                    SetConsoleTextAttribute(hConsole, COLOR_BLUE);
                    break;
                }
                default:
                {
                    messageLine.append("[INFO]   ");
                    break;
                }
                }
                messageLine.append("[");
                messageLine.append(locaName);
                messageLine.append("]   ");
                messageLine.append(message);
                cout << messageLine << endl;
                SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
            }
            catch (char *e)
            {
            }
        }
        catch (char *e)
        {
        }
    }

    /**
     * @brief 写入日志到指定的文本中
     *
     * @param level
     * @param locaName
     * @param message
     */
    void _writeLine(level::level level, string locaName, string message)
    {
        if (!_is_file_log(level))
            return;
        try
        {
            if (!logFile.is_open())
            {
                logFile.open(_tofilePath, ios_base::app);
                if (!logFile.is_open())
                    return;
            }

            // [2023-06-17 01:21:11.245] [info]   [Main]   message
            string messageLine = get_time();
            messageLine.append(" ");

            switch (level)
            {
                // error = 8005,
                // warn = 8006,
                // info = 8008,
                // debug = 8001,
            case level::error:
            {
                messageLine.append("[ERROR]  ");
                break;
            }
            case level::warn:
            {
                messageLine.append("[WARN]    ");
                break;
            }
            case level::debug:
            {
                messageLine.append("[DEBUG]  ");
                break;
            }
            default:
            {
                messageLine.append("[INFO]   ");
                break;
            }
            }
            messageLine.append("[");
            messageLine.append(locaName);
            messageLine.append("]   ");
            messageLine.append(message);
            messageLine.append("\n");
            logFile << messageLine;
        }
        catch (char *e)
        {
        }
    }

    /**
     * @brief 分割线
     *
     */
    void separator()
    {

        try
        {
            string messageLine = get_time();
            messageLine.append(" ");
            for (size_t i = 0; i < 60; i++)
                messageLine.append("---");

            messageLine.append("\n");

            if (_is_file_log(level::info))
            {

                if (!logFile.is_open())
                {
                    logFile.open(_tofilePath, ios_base::app);
                    if (!logFile.is_open())
                        return;
                }

                logFile << messageLine;
            }

            if (_is_cout_log(level::info))
            {
                cout << messageLine;
            }
        }
        catch (char *e)
        {
        }
    }

    /**
     * @brief 设置是否启用控制台打印(node控制台 而不是Chrome控制台)
     *
     * @param level
     * @return level
     */
    bool setLogToCout(bool is_open)
    {
        _is_cout = is_open;
        return _is_cout;
    }

    /**
     * @brief 设置是否启用打印到日志文件
     *
     * @param is_open
     * @return true
     * @return false
     */
    bool setLogToFile(bool is_open)
    {
        _is_tofile = is_open;
        return _is_tofile;
    }

    /**
     * @brief 日志存储设置路径
     *
     * @param tofilePath
     */
    void setLogFilePath(string tofilePath)
    {
        _tofilePath = tofilePath;
    }

    /**
     * @brief 设置所有启用的报告等级 默认 All
     *
     * @param level
     * @return level
     */
    void setLevel(int level)
    {
        _is_cout = true;
        _is_tofile = true;
        _file_level = level;
        _cout_level = level;
    }

    /**
     * @brief 设置日志文件的打印等级
     *
     * @param level
     * @return level
     */
    int setFileLevel(level::level level)
    {
        _file_level = level;
        _is_tofile = true;
        return _file_level;
    }

    /**
     * @brief 设置控制台打印等级
     *
     * @param level
     * @return level
     */
    int setCoutLevel(int level)
    {
        _cout_level = level;
        _is_cout = true;
        return _cout_level;
    }

    /**
     * @brief 打印单条文本日志
     *
     * @param locaName
     * @param message
     */
    template <typename... Args>
    void _hmc_send_string(level::level level, string locaName, const string &first, const Args &...args)
    {
        string temp[] = {first, args...};
        size_t length = sizeof(temp) / sizeof(temp[0]);
        string messageAll = string();
        string message = string();

        if (!length)
        {
            messageAll.append(locaName);
            locaName.clear();
            locaName.append("any");
            temp[0] = locaName;
            length = 1;
        }

        message.append("< string[");
        message.append(to_string(length));
        message.append(",");

        for (size_t i = 0; i < length; i++)
        {
            string data = temp[i];
            messageAll.append(data);
            if (i != length - 1)
                messageAll.append("\t,\t");
        }

        message.append(to_string(messageAll.size()));
        message.append("] >");

        message.append("   ");
        message.append(messageAll);
        messageAll.clear();

        _coutLine(level, locaName, message);
        _writeLine(level, locaName, message);
    }
    void _hmc_send_anyStr(level::level level, string locaName, const string &data, const string &type)
    {

        string message = string();

        message.append("< ");
        message.append(type);
        message.append(" >");

        message.append("   ");
        message.append(data);

        _coutLine(level, locaName, message);
        _writeLine(level, locaName, message);
    }
    void _hmc_send_number(level::level level, string locaName, const string &num, const string &type)
    {
        string message = string();
        message.append("< number[");
        message.append(type);
        message.append("] >");
         message.append("   ");
        message.append(num);
        _coutLine(level, locaName, message);
        _writeLine(level, locaName, message);
    }

    /**
     * @brief 常规打印
     *
     * @tparam Args
     * @param locaName
     * @param first
     * @param args
     */
    template <typename... Args>
    void info(string locaName, const string &first, const Args &...args)
    {
        _hmc_send_string(level::info, locaName, first, args...);
    }

    /**
     * @brief 打印错误的文本
     *
     * @tparam Args
     * @param locaName
     * @param first
     * @param args
     */
    template <typename... Args>
    void error(string locaName, const string &first, const Args &...args)
    {
        _hmc_send_string(level::error, locaName, first, args...);
    }

    /**
     * @brief 打印警告的文本
     *
     * @tparam Args
     * @param locaName
     * @param first
     * @param args
     */
    template <typename... Args>
    void warn(string locaName, const string &first, const Args &...args)
    {
        _hmc_send_string(level::warn, locaName, first, args...);
    }

    /**
     * @brief 打印debug变量 (这个是可以支持多类型打印的)
     *
     * @tparam Args
     * @param locaName
     * @param first
     * @param args
     */
    template <typename... Args>
    void debug(string locaName, const string &first, const Args &...args)
    {
        _hmc_send_string(level::debug, locaName, first, args...);
    }

    // debug ->  处理数字类型
    void debug(string locaName, long long data)
    {
        _hmc_send_number(level::debug, locaName, to_string(data), "long long");
    }
    
    void debug(string locaName, nullptr_t data)
    {
        _hmc_send_number(level::debug, locaName,string("NULL"), "NULL");
    }
    void debug(string locaName, bool data)
    {
        _hmc_send_number(level::debug, locaName,string(data? "true":"false"), "bool");
    }
    void debug(string locaName, int data)
    {
        _hmc_send_number(level::debug, locaName, to_string(data), "int");
    }
    void debug(string locaName, long data)
    {
        _hmc_send_number(level::debug, locaName, to_string(data), "long");
    }
    void debug(string locaName, DWORD data)
    {
        _hmc_send_string(level::debug, locaName, to_string(data), "DWORD");
    }
    void debug(string locaName, double data)
    {
        _hmc_send_number(level::debug, locaName, to_string(data), "double");
    }
    void debug(string locaName, unsigned long long data)
    {
        _hmc_send_number(level::debug, locaName, to_string(data), "unsigned long long");
    }
    void debug(string locaName, unsigned int data)
    {
        _hmc_send_number(level::debug, locaName, to_string(data), "unsigned int");
    }
    void debug(string locaName, long double data)
    {
        _hmc_send_number(level::debug, locaName, to_string(data), "long double");
    }
    void debug(string locaName, float data)
    {
        _hmc_send_number(level::debug, locaName, to_string(data), "float");
    }
    void debug(string locaName, HWND data)
    {
        _hmc_send_number(level::debug, locaName, to_string((long long)data), "HWND");
    }
    void debug()
    {
        separator();
    }
    /**
     * @brief 处理数组类型
     *
     * @param locaName
     * @param data
     * @param type
     */
    void debug(string locaName, vector<HWND> data, string type = "vector<HWND> [")
    {
        string message = "[";
        type.append(to_string(data.size()));
        type.append("]");

        for (size_t i = 0; i < data.size(); i++)
        {
            HWND hwnd = data[i];
            message.append(to_string((long long)hwnd));
            if (i != data.size() - 1)
                message.append(",");
        }
        message.append("]");
        _hmc_send_anyStr(level::debug, locaName, message, type);
    }
    void debug(string locaName, vector<long> data, string type = "vector<long> [")
    {
        string message = "[";
        type.append(to_string(data.size()));
        type.append("]");

        for (size_t i = 0; i < data.size(); i++)
        {
            long indata = data[i];
            message.append(to_string((long long)indata));
            if (i != data.size() - 1)
                message.append(",");
        }
        message.append("]");
        _hmc_send_anyStr(level::debug, locaName, message, type);
    }
    void debug(string locaName, vector<int> data, string type = "vector<int> [")
    {
        string message = "[";
        type.append(to_string(data.size()));
        type.append("]");

        for (size_t i = 0; i < data.size(); i++)
        {
            int indata = data[i];
            message.append(to_string((int)indata));
            if (i != data.size() - 1)
                message.append(",");
        }
        message.append("]");
        _hmc_send_anyStr(level::debug, locaName, message, type);
    }
    void debug(string locaName, vector<DWORD> data, string type = "vector<DWORD> [")
    {
        string message = "[";
        type.append(to_string(data.size()));
        type.append("]");

        for (size_t i = 0; i < data.size(); i++)
        {
            DWORD indata = data[i];
            message.append(to_string((DWORD)indata));
            if (i != data.size() - 1)
                message.append(",");
        }
        message.append("]");
        _hmc_send_anyStr(level::debug, locaName, message, type);
    }
    void debug(string locaName, vector<double> data, string type = "vector<double> [")
    {
        string message = "[";
        type.append(to_string(data.size()));
        type.append("]");

        for (size_t i = 0; i < data.size(); i++)
        {
            double indata = data[i];
            message.append(to_string((double)indata));
            if (i != data.size() - 1)
                message.append(",");
        }
        message.append("]");
        _hmc_send_anyStr(level::debug, locaName, message, type);
    }
    void debug(string locaName, vector<string> data, string type = "vector<string> [")
    {
        string message = "[";
        type.append(to_string(data.size()));
        type.append("]");

        for (size_t i = 0; i < data.size(); i++)
        {
            string newdata = "\"";
            newdata.append(escapeJson(data[i]));
            newdata.append("\"");

            message.append(newdata);
            if (i != data.size() - 1)
                message.append(",");
        }
        message.append("]");
        _hmc_send_anyStr(level::debug, locaName, message, type);
    }

    /**
     * @brief 处理set类型
     *
     * @param locaName
     * @param data
     */
    void debug(string locaName, set<HWND> data)
    {
        vector<HWND> new_data;
        for (auto it = data.rbegin(); it != data.rend(); ++it)
        {
            new_data.push_back(*it);
        }
        debug(locaName, new_data, "set<HWND> [");
    }
    void debug(string locaName, set<long> data)
    {
        vector<long> new_data;
        for (auto it = data.rbegin(); it != data.rend(); ++it)
        {
            new_data.push_back(*it);
        }
        debug(locaName, new_data, "set<long> [");
    }
    void debug(string locaName, set<int> data)
    {
        vector<int> new_data;
        for (auto it = data.rbegin(); it != data.rend(); ++it)
        {
            new_data.push_back(*it);
        }
        debug(locaName, new_data, "set<int> [");
    }
    void debug(string locaName, set<double> data)
    {
        vector<double> new_data;
        for (auto it = data.rbegin(); it != data.rend(); ++it)
        {
            new_data.push_back(*it);
        }
        debug(locaName, new_data, "set<double> [");
    }
    void debug(string locaName, set<DWORD> data)
    {
        vector<DWORD> new_data;
        for (auto it = data.rbegin(); it != data.rend(); ++it)
        {
            new_data.push_back(*it);
        }
        debug(locaName, new_data, "set<DWORD> [");
    }
    void debug(string locaName, set<string> data)
    {
        vector<string> new_data;
        for (auto it = data.rbegin(); it != data.rend(); ++it)
        {
            new_data.push_back(*it);
        }
        debug(locaName, new_data, "set<string> [");
    }

    /**
     * @brief 处理map
     *
     * @param locaName
     * @param data
     */
    void debug(string locaName, map<string, string> data)
    {
        string type = "map<string, string>";
        string message = "{";
        int size = 0;
        for (const auto &entry : data)
        {
            size++;
            message.append("\"");
            string eqjsonKeyText;
            eqjsonKeyText.append(escapeJson(entry.first));

            message.append("\" : \"");
            string eqjsonText;
            eqjsonText.append(escapeJson(entry.second));
            message.append(eqjsonText);
            message.append("\"");
            if(size>=15){
                message.append("...");
                break;
            }
            message.append(",");
        }
        // 如果最后一位是逗号，移除它
        if (!message.empty() && message.back() == ',')
        {
            message.pop_back();
        }
        message.append("}");

        _hmc_send_anyStr(level::debug, locaName, message, type);
    }
    void debug(string locaName, map<double, string> data)
    {
        string type = "map<double, string>";
        string message = "{";
        for (const auto &entry : data)
        {
            message.append("\"");
            string eqjsonKeyText;
            eqjsonKeyText.append(to_string(entry.first));

            message.append("\" : \"");
            string eqjsonText;
            eqjsonText.append(escapeJson(entry.second));
            message.append(eqjsonText);
            message.append("\"");
            message.append(",");
        }
        // 如果最后一位是逗号，移除它
        if (!message.empty() && message.back() == ',')
        {
            message.pop_back();
        }
        message.append("}");

        _hmc_send_anyStr(level::debug, locaName, message, type);
    }
    void debug(string locaName, map<DWORD, string> data)
    {
        string type = "map<DWORD, string>";
        string message = "{";
        for (const auto &entry : data)
        {
            string eqjsonKeyText;
            eqjsonKeyText.append(to_string(entry.first));
            message.append(" : \"");
            string eqjsonText;
            eqjsonText.append(escapeJson(entry.second));
            message.append(eqjsonText);
            message.append("\"");
            message.append(",");
        }
        // 如果最后一位是逗号，移除它
        if (!message.empty() && message.back() == ',')
        {
            message.pop_back();
        }
        message.append("}");

        _hmc_send_anyStr(level::debug, locaName, message, type);
    }

    // --------------------------------
    void debug(string locaName, map<string, double> data)
    {
        string type = "map<string, double>";
        string message = "{";
        for (const auto &entry : data)
        {
            message.append("\"");
            string eqjsonKeyText;
            eqjsonKeyText.append(escapeJson(entry.first));
            message.append("\" : \"");
            string eqjsonText;
            eqjsonText.append(escapeJson(to_string(entry.second)));
            message.append(eqjsonText);
            message.append("\"");
            message.append(",");
        }
        // 如果最后一位是逗号，移除它
        if (!message.empty() && message.back() == ',')
        {
            message.pop_back();
        }
        message.append("}");

        _hmc_send_anyStr(level::debug, locaName, message, type);
    }
    void debug(string locaName, map<string, DWORD> data)
    {
        string type = "map<string, DWORD>";
        string message = "{";
        for (const auto &entry : data)
        {
            string eqjsonKeyText;
            eqjsonKeyText.append(escapeJson(entry.first));
            message.append(" : \"");
            string eqjsonText;
            eqjsonText.append(escapeJson(to_string(entry.second)));
            message.append(eqjsonText);
            message.append("\"");
            message.append(",");
        }
        // 如果最后一位是逗号，移除它
        if (!message.empty() && message.back() == ',')
        {
            message.pop_back();
        }
        message.append("}");

        _hmc_send_anyStr(level::debug, locaName, message, type);
    }

    // void debug(string locaName, json data)
    // {
    //     string message;
    //     data.get_to(message);
    //     _hmc_send_anyStr(level::debug, locaName, message, "json<cpp>");
    // }

    /**
     * @brief 模拟js的计时器(相对时间 误差 +-15ms ) 这是因为全程同步 打印啥的都是需要时间的
     *
     * @param label
     */
    void time(string label = "default")
    {
        // 已经存在
        if (_startTimeList.find(label) != _startTimeList.end())
        {
            warn("Timer", label, "already exists");
            return;
        }
        _startTimeList[label] = chrono::high_resolution_clock::now();
    }

    /**
     * @brief 结束模拟js的计时器(相对时间 误差 +-15ms ) 这是因为全程同步 打印啥的都是需要时间的
     *
     * @param label
     */
    void timeEnd(string label = "default")
    {
        // 不存在
        if (_startTimeList.find(label) == _startTimeList.end())
        {
            warn("Timer", label, "does not exist");
            return;
        }
        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(endTime - _startTimeList[label]).count();
        // 将微秒转换为浮点数毫秒
        double milliseconds = static_cast<double>(duration) / 1000.0;
        _startTimeList.erase(label);
        _hmc_send_anyStr(level::debug, string("Timer"), "", string(label).append(": ").append(to_string(milliseconds).append(" ms")));
    }
}

/**

 int main()
{
    hmc_console::setCoutLevel(hmc_console::level::all);

    for (int i = 0; i <= 500; i++)
    {
        hmc_console::time();

        Sleep(100);
        // 结束计时
        hmc_console::timeEnd();

    }
    return 0;
}

 *
 */