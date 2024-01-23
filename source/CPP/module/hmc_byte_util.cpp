#include "./hmc_byte_util.h"

std::vector<std::uint8_t> int16ToBytes(const std::uint16_t data)
{
	std::vector<std::uint8_t> bytes = std::vector<std::uint8_t>();
	bytes.reserve(2);
	bytes.push_back((data >> 8) & 0xFF);
	bytes.push_back(data & 0xFF);
	return bytes;
}

std::vector<std::uint8_t> int32ToBytes(const std::uint32_t data)
{
	std::vector<std::uint8_t> bytes = std::vector<std::uint8_t>();
	bytes.reserve(4);
	bytes.push_back((data >> 24) & 0xFF);
	bytes.push_back((data >> 16) & 0xFF);
	bytes.push_back((data >> 8) & 0xFF);
	bytes.push_back(data & 0xFF);
	return bytes;
}

std::vector<std::uint8_t> int64ToBytes(const std::uint64_t data)
{
	std::vector<std::uint8_t> bytes = std::vector<std::uint8_t>();
	bytes.reserve(8);

	for (int i = 0; i < 8; i++)
	{
		bytes.push_back(static_cast<std::uint8_t>(data >> (8 * (7 - i))));
	}
	return bytes;
}

std::vector<std::uint8_t> stringToBytes(std::string bytes_string)
{
	std::vector<std::uint8_t> buff = {};
	if (bytes_string.empty())
	{
		return buff;
	}
	buff.reserve(bytes_string.size());

	for (std::string::const_iterator str = bytes_string.begin(), eos = bytes_string.end(); str != eos; ++str)
	{
		std::uint8_t cuChar = static_cast<std::uint8_t>(*str);
		buff.push_back(cuChar);
	}
	return buff;
}

std::vector<std::uint8_t> stringToBytes(const char &bytes_string)
{
	std::vector<std::uint8_t> buff = {};
	buff.push_back(bytes_string);
	return buff;
}

std::vector<std::uint8_t> wstringToBytes(const std::wstring &bytes_string)
{
	std::vector<std::uint8_t> buff = {};
	size_t len = bytes_string.size();

	if (bytes_string.empty())
	{
		return {};
	}

	buff.reserve(bytes_string.size() * 2);

	const wchar_t *str = bytes_string.c_str();

	for (size_t i = 0; i < len; i++)
	{

		// utf32
		if (bytes_string[i] >= 0x10FFFF)
		{
			std::uint32_t value = static_cast<std::uint32_t>(bytes_string[i]);
			auto int32Bytes = int32ToBytes(value);

			for (size_t i = 0; i < int32Bytes.size(); i++)
			{
				buff.push_back(int32Bytes.at(i));
			}
		}
		else
		{

			// utf16
			std::uint16_t value = static_cast<std::uint16_t>(bytes_string[i]);
			std::uint8_t partA = (std::uint8_t)((value & 0xFF00) >> 8);
			std::uint8_t partB = (std::uint8_t)(value & 0x00FF);
			buff.push_back(partA);
			buff.push_back(partB);
		}
	}

	return buff;
}

std::vector<std::uint8_t> wstringToBytes(const wchar_t &bytes_string)
{
	std::vector<std::uint8_t> buff = {};

	// utf32
	if (bytes_string >= 0x10FFFF)
	{
		std::uint32_t value = static_cast<std::uint32_t>(bytes_string);
		auto int32Bytes = int32ToBytes(value);

		for (size_t i = 0; i < int32Bytes.size(); i++)
		{
			buff.push_back(int32Bytes.at(i));
		}
	}
	else
	{

		// utf16
		std::uint16_t value = static_cast<std::uint16_t>(bytes_string);
		std::uint8_t partA = (std::uint8_t)((value & 0xFF00) >> 8);
		std::uint8_t partB = (std::uint8_t)(value & 0x00FF);
		buff.push_back(partA);
		buff.push_back(partB);
	}

	return buff;
}

#if _HAS_CXX20
// 值转为二进制 非常好用 而且转出来的文本winapi能识别 但是最低要求是c++20
template <typename T>
extern std::vector<std::uint8_t> ToBytes(const T &val)
{
	struct is_wstring_type : std::disjunction<std::is_same<T, std::wstring>, std::is_same<T, wchar_t *>, std::is_same<T, const wchar_t *>>
	{
	};
	struct is_string_type : std::disjunction<std::is_same<T, std::string>, std::is_same<T, char *>, std::is_same<T, const char *>>
	{
	};

	if constexpr (is_wstring_type::value)
	{
		std::wstring_view str_view(val);
		return std::vector<std::uint8_t>(str_view.begin(), str_view.end());
	}
	else if constexpr (is_string_type::value)
	{
		std::string_view str_view(val);
		return std::vector<std::uint8_t>(str_view.begin(), str_view.end());
	}
	else if constexpr (std::is_trivially_copyable_v<T>)
	{
		auto byte_list = std::bit_cast<std::array<std::uint8_t, sizeof(T)>>(val);
		return {byte_list.begin(), byte_list.end()};
	}
	else
	{
		return {};
	}
}
#endif //_HAS_CXX20

std::uint16_t bytesToInt16(const std::vector<std::uint8_t> &bytes)
{
	std::uint16_t result = 0;

	if (bytes.size() != 2)
	{
		return result;
	}

	result += static_cast<std::uint8_t>(bytes.at(0)) << 8;
	result += static_cast<std::uint8_t>(bytes.at(1));
	return result;
}

std::uint32_t bytesToInt32(const std::vector<std::uint8_t> &bytes)
{
	std::uint32_t result = 0;

	const auto leng = bytes.size();

	if (leng == 4)
	{
		result += static_cast<std::uint8_t>(bytes.at(0)) << 24;
		result += static_cast<std::uint8_t>(bytes.at(1)) << 16;
		result += static_cast<std::uint8_t>(bytes.at(2)) << 8;
		result += static_cast<std::uint8_t>(bytes.at(3));
		return result;
	}
	if (leng == 2)
	{
		result += static_cast<std::uint8_t>(bytes.at(0)) << 8;
		result += static_cast<std::uint8_t>(bytes.at(1));
		return result;
	}
	else if (leng == 1)
	{
		return static_cast<std::uint8_t>(bytes.at(0));
	}

	return 0;
}

std::uint64_t bytesToInt64(const std::vector<std::uint8_t> &bytes)
{
	std::uint64_t result = 0;

	if (bytes.size() != 8)
	{
		return result;
	}

	for (int i = 0; i < 8; i++)
	{
		result <<= 8;
		result += static_cast<std::uint8_t>(bytes.at(i));
	}

	return result;
}

std::string bytesToString(const std::vector<uint8_t> &bytes)
{
	size_t len = bytes.size();
	const char *charPtr = reinterpret_cast<const char *>(bytes.data());
	const std::string result = std::string(charPtr, charPtr + len);

	return result;
}

std::wstring bytesToWstring(const std::vector<uint8_t> &bytes)
{
	std::wstring result = L"";

	if (bytes.empty())
		return result;

	int len = bytes.size();

	// 能被2整除 utf16
	if (len % 2 == 0)
	{

		for (int i = 0; i < len - 1; i += 2)
		{
			if (bytes[i] == 0xff && bytes[i + 1] == 0xff)
			{
				break;
			}
			if (bytes[i] == 0 && bytes[i + 1] == 0)
			{
				break;
			}

			auto temp = {bytes.at(i), bytes.at(i + 1)};

			result.push_back(static_cast<char16_t>(bytesToInt16(temp)));
		}
	}
	else
		// 能被4整除 utf32
		if (len % 4 == 0)
		{

			for (int i = 0; i < len - 1; i += 4)
			{
				// if (bytes[i] == 0xff && bytes[i + 1] == 0xff) {
				// 	break;
				// }
				// if (bytes[i] == 0 && bytes[i + 1] == 0) {
				// 	break;
				// }

				// auto temp = { bytes.at(i) ,bytes.at(i + 1) };

				// result.push_back(static_cast<char32_t>(bytesToInt32(temp)) );
			}
		}

	return result;
}
