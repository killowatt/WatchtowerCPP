#include "MemoryStream.h"
#include <cstring>
#include <cwchar>

uint8_t MemoryStream::ReadByte()
{
	if (position >= data.size()) {}
	// TODO: throw truncate msg and remove bracket
	return (uint8_t)data[position++];
}
int16_t MemoryStream::ReadShort()
{
	int16_t value = 0;
	if (position + 2 > data.size()) {}
		// TODO: throw truncate msg and remove bracket
	value |= ((int16_t)(uint8_t)data[position++]);
	value |= ((int16_t)(uint8_t)data[position++]) << 8;
	return value;
}
int32_t MemoryStream::ReadInt()
{
	int32_t value = 0;
	if (position + 4 > data.size()) {}
		// TODO: throw..
	value |= ((int32_t)(uint8_t)data[position++]);
	value |= ((int32_t)(uint8_t)data[position++]) << 8;
	value |= ((int32_t)(uint8_t)data[position++]) << 16;
	value |= ((int32_t)(uint8_t)data[position++]) << 24;
	return value;
}
int64_t MemoryStream::ReadLong()
{
	int64_t value = 0;
	if (position + 8 > data.size()) {}
		// TODO: throw..
	value |= ((int64_t)(uint8_t)data[position++]) << 8;
	value |= ((int64_t)(uint8_t)data[position++]) << 16;
	value |= ((int64_t)(uint8_t)data[position++]) << 24;
	value |= ((int64_t)(uint8_t)data[position++]) << 32;
	value |= ((int64_t)(uint8_t)data[position++]) << 40;
	value |= ((int64_t)(uint8_t)data[position++]) << 48;
	value |= ((int64_t)(uint8_t)data[position++]) << 56;
	return value;
}
int8_t MemoryStream::ReadSignedByte()
{
	if (position >= data.size()) {}
		// TODO: throw truncate msg and remove bracket
	return (int8_t)data[position++];
}
uint16_t MemoryStream::ReadUnsignedShort()
{
	uint16_t value = 0;
	if (position + 2 > data.size()) {}
		// TODO: throw truncate msg and remove bracket
	value |= ((uint16_t)(uint8_t)data[position++]);
	value |= ((uint16_t)(uint8_t)data[position++]) << 8;
	return value;
}
uint32_t MemoryStream::ReadUnsignedInt()
{
	uint32_t value = 0;
	if (position + 4 > data.size()) {}
		// TODO: throw..
	value |= ((uint32_t)(uint8_t)data[position++]);
	value |= ((uint32_t)(uint8_t)data[position++]) << 8;
	value |= ((uint32_t)(uint8_t)data[position++]) << 16;
	value |= ((uint32_t)(uint8_t)data[position++]) << 24;
	return value;
}
uint64_t MemoryStream::ReadUnsignedLong()
{
	uint64_t value = 0;
	if (position + 8 > data.size()) {}
	// TODO: throw..
	value |= ((uint64_t)(uint8_t)data[position++]);
	value |= ((uint64_t)(uint8_t)data[position++]) << 8;
	value |= ((uint64_t)(uint8_t)data[position++]) << 16;
	value |= ((uint64_t)(uint8_t)data[position++]) << 24;
	value |= ((uint64_t)(uint8_t)data[position++]) << 32;
	value |= ((uint64_t)(uint8_t)data[position++]) << 40;
	value |= ((uint64_t)(uint8_t)data[position++]) << 48;
	value |= ((uint64_t)(uint8_t)data[position++]) << 56;
	return value;
}
bool MemoryStream::ReadBool()
{
	if (position >= data.size()) {}
	// TODO: throw truncate..
	return data[position++] != 0;
}
float MemoryStream::ReadFloat()
{
	if (position + 4 > data.size()) {}
	// TODO: throw..
	float data = *reinterpret_cast<const float*>(&this->data[position]);
	position += sizeof(data);
	return data;
}
double MemoryStream::ReadDouble()
{
	if (position + 8 > data.size()) {}
	// TODO: throw..
	double data = *reinterpret_cast<const double*>(&this->data[position]);
	position += sizeof(data);
	return data;
}
char MemoryStream::ReadChar()
{
	if (position >= data.size()) {}
	// TODO: throw truncate msg and remove bracket
	return data[position++];
}
std::string MemoryStream::ReadString()
{
	uint32_t length = ReadUnsignedInt();
	std::string string;
	if (length > 0)
	{
		string.assign(&data[position], length);
		position += length;
	}
	return string;
}

void MemoryStream::Write(const void* data, std::size_t size)
{
	std::size_t start = this->data.size();
	this->data.resize(start + size);
	std::memcpy(&this->data[start], data, size);
}
void MemoryStream::Write(uint8_t value)
{
	data.push_back((char)value);
}
void MemoryStream::Write(int16_t value)
{
	data.push_back((char)value);
	data.push_back((char)(value >> 8));
}
void MemoryStream::Write(int32_t value)
{
	data.push_back((char)value);
	data.push_back((char)(value >> 8));
	data.push_back((char)(value >> 16));
	data.push_back((char)(value >> 24));
}
void MemoryStream::Write(int64_t value)
{
	data.push_back((char)value);
	data.push_back((char)(value >> 8));
	data.push_back((char)(value >> 16));
	data.push_back((char)(value >> 24));
	data.push_back((char)(value >> 32));
	data.push_back((char)(value >> 40));
	data.push_back((char)(value >> 48));
	data.push_back((char)(value >> 56));
}
void MemoryStream::Write(int8_t value)
{
	data.push_back((char)value);
}
void MemoryStream::Write(uint16_t value)
{
	data.push_back((char)value);
	data.push_back((char)(value >> 8));
}
void MemoryStream::Write(uint32_t value)
{
	data.push_back((char)value);
	data.push_back((char)(value >> 8));
	data.push_back((char)(value >> 16));
	data.push_back((char)(value >> 24));
}
void MemoryStream::Write(uint64_t value)
{
	data.push_back((char)value);
	data.push_back((char)(value >> 8));
	data.push_back((char)(value >> 16));
	data.push_back((char)(value >> 24));
	data.push_back((char)(value >> 32));
	data.push_back((char)(value >> 40));
	data.push_back((char)(value >> 48));
	data.push_back((char)(value >> 56));
}
void MemoryStream::Write(bool value)
{
	data.push_back((uint8_t)value);
}
void MemoryStream::Write(float value)
{
	Write(&value, sizeof(value));
}
void MemoryStream::Write(double value)
{
	Write(&value, sizeof(value));
}
void MemoryStream::Write(char value)
{
	data.push_back(value);
}
void MemoryStream::Write(const std::string& value)
{
	uint32_t length = static_cast<uint32_t>(value.size());
	Write(length);

	if (length > 0)
		Write(value.c_str(), length * sizeof(std::string::value_type));
}

MemoryStream::MemoryStream()
{
	position = 0;
}
MemoryStream::MemoryStream(uint8_t* data, std::size_t length)
{
	position = 0;

	this->data.resize(length);
	memcpy(this->data.data(), data, length);
}
