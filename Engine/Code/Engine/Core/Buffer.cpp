#include "Buffer.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"

unsigned char* BufferWriter::AppendUnitializedByte()
{
	return nullptr;
}

void BufferWriter::AppendByte(unsigned char b)
{

}

void BufferWriter::AppendChar(char c)
{

}

void BufferWriter::AppendUShort(unsigned short u)
{

}

void BufferWriter::AppendShort(short s)
{

}

void BufferWriter::AppendUInt(unsigned int u)
{

}

void BufferWriter::AppendInt(int i)
{

}

void BufferWriter::AppendUInt64(uint64_t u)
{

}

void BufferWriter::AppendInt64(int64_t i)
{

}

void BufferWriter::AppendFloat(float f)
{
	float* addressOfFloat = &f;
	unsigned char* addressOfFloatInByteArray = reinterpret_cast<unsigned char*>(addressOfFloat);
	if (m_isOppositeEndianessFromNative)
	{
		Reverse4BytesInPlace(addressOfFloatInByteArray);
	}

	AppendByte(addressOfFloatInByteArray[0]);
	AppendByte(addressOfFloatInByteArray[1]);
	AppendByte(addressOfFloatInByteArray[2]);
	AppendByte(addressOfFloatInByteArray[3]);
}

void BufferWriter::AppendDouble(double d)
{

}

void BufferWriter::AppendString(const char* c)
{

}

void BufferWriter::AppendString(unsigned int length, const char* c)
{

}

void BufferWriter::AppendVec2(Vec2 v)
{

}

void BufferWriter::AppendVec3(Vec3 v)
{

}

void BufferWriter::AppendVec4(Vec4 v)
{

}

void BufferWriter::AppendIntVec2(IntVec2 iv)
{

}

void BufferWriter::AppendIntVec3(IntVec3 iv)
{

}

void BufferWriter::AppendRgba8(Rgba8 color)
{

}

void BufferWriter::AppendRgb8(Rgba8 color)
{

}

void BufferWriter::AppendAABB2(AABB2 box)
{

}

void BufferWriter::AppendAABB3(AABB3 box)
{

}

void BufferWriter::AppendOBB2(OBB2 box)
{

}

void BufferWriter::AppendOBB3(OBB3 box)
{

}

void BufferWriter::AppendPlane2(Plane2 box)
{

}

void BufferWriter::AppendPlane3(Plane3 box)
{

}

void BufferWriter::AppendVertexPCU(Vertex_PCU box)
{

}

void BufferWriter::AppendVertexPCUTBN(Vertex_PCUTBN box)
{

}

void BufferParser::SetEndianMode(eBufferEndian endianModeSub)
{
	eBufferEndian platformEndian = GetPlatformNativeEndian();
	//m_endianMode = endianModeSub
}

eBufferEndian BufferParser::GetPlatformNativeEndian() const
{
	unsigned int endianTest = 0x12345678;
	unsigned char* asByteArray = reinterpret_cast<unsigned char*>(&endianTest);
	if (asByteArray[0] == 0x12)
	{
		return eBufferEndian::LITTLE;
	}
	else if (asByteArray[0] == 0x78)
	{
		return eBufferEndian::BIG;
	}
	else
	{
		ERROR_AND_DIE("SOMETHING WRONG");
	}
}

float BufferParser::ParseFloat()
{
	float finalValue = 0;
	return finalValue;
}


