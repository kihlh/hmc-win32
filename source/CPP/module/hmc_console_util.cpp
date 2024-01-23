#include "hmc_console_util.h"

namespace hmc_console_util
{
    // utf8
    int hmc_console_util::set_type = 0x20000;
    // not
    int hmc_console_util::oid_type = 0x4000;

    void hmc_console_util::set_to_utf8()
    {
        set_type = 0x40000;
    }

    void hmc_console_util::set_to_utf16()
    {
        set_type = 0x20000;
    }

    /**
     * @brief 结束宽字符打印
     *
     * @param _stdout 输出流
     * @param _stdin 输入流
     * @param _stderr 错误流
     */
    void hmc_console_util::stop(bool _stdout = true, bool _stdin = true, bool _stderr = false)
    {
        // 避免警告
        int temp = 0;
        // 设置控制台为宽字符 I/O 模式
        if (_stdout)
            temp = _setmode(_fileno(stdin), oid_type);
        if (_stdin)
            temp = _setmode(_fileno(stdout), oid_type);
        if (_stderr)
            temp = _setmode(_fileno(stderr), oid_type);
    }
    /**
     * @brief 启动宽字符打印
     *
     * @param _stdout 输出流
     * @param _stdin 输入流
     * @param _stderr 错误流
     */
    void hmc_console_util::start(bool _stdout = true, bool _stdin = true, bool _stderr = false)
    {
        // 避免警告
        int temp = 0;
        // 设置控制台为宽字符 I/O 模式
        if (_stdout)
            temp = _setmode(_fileno(stdin), set_type);
        if (_stdin)
            temp = _setmode(_fileno(stdout), set_type);
        if (_stderr)
            temp = _setmode(_fileno(stderr), set_type);
    }

    AutoRelease::AutoRelease(bool _stdout, bool _stdin , bool _stderr)
    {
        __stdout = _stdout;
        __stdin = _stdin;
        __stderr = _stderr;
        start(__stdout, __stdin, __stderr);
    }

    AutoRelease:: ~AutoRelease()
    {
        stop(__stdout, __stdin, __stderr);
    }
}
