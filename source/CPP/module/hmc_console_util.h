#include <io.h>
#include <fcntl.h>
#include <stdio.h>

namespace hmc_console_util
{
    // utf8
    extern int set_type;
    // not
    extern int oid_type;

    extern void set_to_utf8();

    extern void set_to_utf16();

    /**
     * @brief 结束宽字符打印
     *
     * @param _stdout 输出流
     * @param _stdin 输入流
     * @param _stderr 错误流
     */
    extern void stop(bool _stdout, bool _stdin, bool _stderr);

    /**
     * @brief 启动宽字符打印
     *
     * @param _stdout 输出流
     * @param _stdin 输入流
     * @param _stderr 错误流
     */
    extern void start(bool _stdout, bool _stdin, bool _stderr);

    class AutoRelease
    {
    public:
        AutoRelease(bool _stdout = true, bool _stdin = false, bool _stderr = false);
        ~AutoRelease();

    private:
        bool __stdout = true;
        bool __stdin = false;
        bool __stderr = false;
    };
}
