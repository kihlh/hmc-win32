#include <string>
#include <vector>
using namespace std;

string vector2string(vector<string> strVector)
{
    string result = string("[");
    for (size_t i = 0; i < strVector.size(); i++)
    {
        string str = string();
        result.append("\"");

        for (char ch : strVector[i])
        {
            switch (ch)
            {
            case '\"':
                str.append("\\\"");
                break;
            case '\\':
                str.append("\\\\");
                break;
            case '\b':
                str.append("\\b");
                break;
            case '\f':
                str.append("\\f");
                break;
            case '\n':
                str.append("\\n");
                break;
            case '\r':
                str.append("\\r");
                break;
            case '\t':
                str.append("\\t");
                break;
            default:
                str.push_back(ch);
                break;
            }
        }

        result.append(str);
        result.append("\"");
        result.append(",");
    }
    // 如果最后一位是逗号，移除它
    if (!result.empty() && result.back() == ',')
    {
        result.pop_back();
    }
    result.append("]");
    return result;
}

string vector2string(vector<long long> dataVector)
{
    string result = string("[");
    for (size_t i = 0; i < dataVector.size(); i++)
    {
        long long data = dataVector[i];

        result.append(to_string(data));
        result.append(",");
    }

    // 如果最后一位是逗号，移除它
    if (!result.empty() && result.back() == ',')
    {
        result.pop_back();
    }
    result.append("]");
    return result;
}
