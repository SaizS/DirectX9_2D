#include "framework.h"

BinaryWriter::BinaryWriter(wstring filePath) : size(0)
{
	file = CreateFile(filePath.c_str(), GENERIC_WRITE,	0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

BinaryWriter::~BinaryWriter()
{
	CloseHandle(file);
}

void BinaryWriter::Int(int data)
{
	WriteFile(file, &data, sizeof(int), &size, NULL);
}

void BinaryWriter::UInt(UINT data)
{
	WriteFile(file, &data, sizeof(UINT), &size, NULL);
}

void BinaryWriter::Float(float data)
{
	WriteFile(file, &data, sizeof(float), &size, NULL);
}

void BinaryWriter::String(string data)
{
	UInt(data.size());

	const char* str = data.c_str();
	WriteFile(file, str, sizeof(char) * data.size(), &size, NULL);
}

void BinaryWriter::Byte(void* data, UINT dataSize)
{
	WriteFile(file, data, dataSize, &size, NULL);
}
