#include "framework.h"

BinaryReader::BinaryReader(wstring filePath) : size(0)
{
	file = CreateFile(filePath.c_str(), GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

BinaryReader::~BinaryReader()
{
	CloseHandle(file);
}

int BinaryReader::Int()
{
	int temp;
	ReadFile(file, &temp, sizeof(int), &size, NULL);
	return temp;
}

UINT BinaryReader::UInt()
{
	UINT temp;
	ReadFile(file, &temp, sizeof(UINT), &size, NULL);
	return temp;	
}

float BinaryReader::Float()
{
	float temp;
	ReadFile(file, &temp, sizeof(float), &size, NULL);
	return temp;	
}

string BinaryReader::String()
{
	UINT size = UInt();

	char* temp = new char[size + 1];
	ReadFile(file, temp, sizeof(char) * size, &this->size, NULL);
	temp[size] = '\0';

	return temp;
}

void BinaryReader::Byte(void** data, UINT dataSize)
{
	ReadFile(file, *data, dataSize, &size, NULL);
}

bool BinaryReader::IsExistFile(wstring path)
{
	DWORD fileValue = GetFileAttributes(path.c_str());
	return fileValue < 0xffffffff;
}
