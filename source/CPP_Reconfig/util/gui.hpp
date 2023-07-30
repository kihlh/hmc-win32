

#include <string>
#include <windows.h>
#include <functional>

using namespace std;

namespace hmc_gui
{

    typedef std::function<void(string type, string message)> onSearchBoxCallbackFunc;

    // 输入框
    string prompt(string title, string message, string defaultInput = "")
    {
    }

    // 密码框
    string password(string title, string message, string defaultPassword = "")
    {
    }

    // 密码和用户名框
    string passLogin(string title, string message, string defaultUserName = "", string defaultPassword = "")
    {
    }

    // 搜索框 像浏览器的搜索框一样的
    class SearchBox
    {
    public:
        void close() {}
        void on(onSearchBoxCallbackFunc callBack)
        {
        }
        void setInput()
        {
        }
        void getInput()
        {
        }
        int getLen()
        {
        }
        SearchBox(int len, int start = 1) {}
        SearchBox(string input, int len, int start = 1) {}
        SearchBox(string input) {}
        SearchBox()
        {
        }
    };

    // 进度条
    class progressBar
    {
    public:
        void close(){};
        int getProgress(){};
        void setProgress(int progress){};
    };
}