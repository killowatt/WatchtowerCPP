#pragma once
#include <vector>
#include <string>
#include <enet/enet.h>

namespace Watchtower
{
	class ByteStream
	{
	private:
		std::vector<char> data;
		std::size_t position;

	public:
		const char* const GetData();
		std::size_t GetSize() const;
		ENetPacket* const ToPacket() const;

		uint8_t ReadByte();
		int16_t ReadShort();
		int32_t ReadInt();
		int64_t ReadLong();
		int8_t ReadSignedByte();
		uint16_t ReadUnsignedShort();
		uint32_t ReadUnsignedInt();
		uint64_t ReadUnsignedLong();
		bool ReadBool();
		float ReadFloat();
		double ReadDouble();
		char ReadChar();
		std::string ReadString();

		void Write(const void* data, std::size_t size);
		void Write(uint8_t value);
		void Write(int16_t value);
		void Write(int32_t value);
		void Write(int64_t value);
		void Write(int8_t value);
		void Write(uint16_t value);
		void Write(uint32_t value);
		void Write(uint64_t value);
		void Write(bool value);
		void Write(float value);
		void Write(double value);
		void Write(char value);
		void Write(const std::string& value);

		ByteStream();
		ByteStream(uint8_t* data, std::size_t length);
	};
}