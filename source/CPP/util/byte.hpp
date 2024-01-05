#ifndef HMC_IMPORT_HMC_BYTE_UTIL_H
#define HMC_IMPORT_HMC_BYTE_UTIL_H 1

#include <vector>
#include <string>

#if _HAS_CXX20 // to_buffer(const T &val)
#include <bit>
#endif //_HAS_CXX20



#if _HAS_CXX20
// 值转为二进制 非常好用 而且转出来的文本winapi能识别 但是最低要求是c++20
template <typename T>
extern std::vector<std::uint8_t> ToBytes(const T& val);
#endif //_HAS_CXX20


extern std::vector<std::uint8_t> int16ToBytes(std::uint16_t data);

extern std::vector<std::uint8_t> int32ToBytes(std::uint32_t data);

extern std::vector<std::uint8_t> int64ToBytes(std::uint64_t data);

extern std::vector<std::uint8_t> stringToBytes(std::string bytes_string);

extern std::vector<std::uint8_t> wstringToBytes(const std::wstring& bytes_string);



extern std::uint16_t bytesToInt16(const std::vector<std::uint8_t>& bytes);

extern std::uint32_t bytesToInt32(const std::vector<std::uint8_t>& bytes);

extern std::uint64_t bytesToInt64(const std::vector<std::uint8_t>& bytes);

extern std::string bytesToString(const std::vector<uint8_t>& bytes);

extern std::wstring bytesToWstring(const std::vector<uint8_t>& bytes);


#endif // HMC_IMPORT_HMC_BYTE_UTIL_H
