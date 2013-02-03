#include "bytestream.h"

#include <fstream>
#include <stdexcept>

namespace kq{

	ByteStream::ByteStream()
	{
	}

	ByteStream::ByteStream(ByteStream &&other) : _data(std::move(other._data))
	{
	}

	ByteStream::ByteStream(const char *str):_data(str)
	{
	}

	ByteStream::ByteStream(const ByteStream &other) : _data(other._data)
	{
	}

	ByteStream::ByteStream(std::size_t reservedSize)
	{
		this->reserve(reservedSize);
	}

	ByteStream::ByteStream(const void * data, std::size_t len)
	{
		_data = std::string((const char*)(data),len);
	}

	ByteStream::ByteStream(const std::basic_string<char> &str) : _data(str)
	{
	}

	void ByteStream::pushBYTE(const BYTE data)
	{
		//_data.insert(_data.size(),1,data);
		this->insertBYTE(data,this->size());
	}

	void ByteStream::pushWORD(const WORD data)
	{
		//_data.insert(_data.size(),(char*)&data,2);
		this->insertWORD(data,this->size());
	}

	void ByteStream::pushDWORD(const DWORD data)
	{
		//_data.insert(_data.size(),(char*)&data,4);
		this->insertDWORD(data,this->size());
	}

	void ByteStream::pushQWORD(const QWORD data)
	{
		//_data.insert(_data.size(),(char*)&data,8);
		this->insertQWORD(data,this->size());
	}

	void ByteStream::pushSTREAM(const ByteStream &data)
	{
		_data += data.toString();
	}

	void ByteStream::pushSTREAM(const void * data, std::size_t len)
	{
		_data.append(reinterpret_cast<const char*>(data),len);
	}

	BYTE ByteStream::popBYTE()
	{
		BYTE ret = *_data.data();
		_data.erase(0,1);
		return ret;
	}

	WORD ByteStream::popWORD()
	{
		WORD ret;
		memcpy(&ret,_data.data(),sizeof(WORD));
		_data.erase(0,sizeof(WORD));
		return ret;
	}

	DWORD ByteStream::popDWORD()
	{
		DWORD ret;
		memcpy(&ret,_data.data(),sizeof(DWORD));
		_data.erase(0,sizeof(DWORD));
		return ret;
	}

	QWORD ByteStream::popQWORD()
	{
		QWORD ret;
		memcpy(&ret,_data.data(),sizeof(QWORD));
		_data.erase(0,sizeof(QWORD));
		return ret;
	}

	ByteStream ByteStream::popSTREAM(std::size_t len)
	{
		ByteStream ret = readSTREAM(0,len);
		_data.erase(0,ret.size());
		return ret;
	}

	BYTE ByteStream::readBYTE(std::size_t pos) const
	{
		BYTE ret = *(_data.data()+pos);
		return ret;
	}

	WORD ByteStream::readWORD(std::size_t pos) const
	{
		WORD ret;
		memcpy(&ret,_data.data()+pos,sizeof(WORD));
		return ret;
	}

	DWORD ByteStream::readDWORD(std::size_t pos) const
	{
		DWORD ret;
		memcpy(&ret,_data.data()+pos,sizeof(DWORD));

		return ret;
	}

	QWORD ByteStream::readQWORD(std::size_t pos) const
	{
		QWORD ret;
		memcpy(&ret,_data.data()+pos,sizeof(QWORD));
		return ret;
	}

	ByteStream ByteStream::readSTREAM(std::size_t pos, std::size_t len) const
	{
		if(len) return std::string(_data.data()+pos,len > _data.size() ? _data.size() : len);
		else return std::string(_data.data()+pos);
	}

	void ByteStream::insertBYTE(const BYTE data, std::size_t n)
	{
		_data.insert(n,(char const*)&data,1);
	}

	void ByteStream::insertWORD(const WORD data, std::size_t n)
	{
		_data.insert(n,(char const*)&data,2);
	}

	void ByteStream::insertDWORD(const DWORD data, std::size_t n)
	{
		_data.insert(n,(char const*)&data,4);
	}

	void ByteStream::insertQWORD(const QWORD data, std::size_t n)
	{
		_data.insert(n,(char const*)&data,8);
	}

	void ByteStream::insertSTREAM(const ByteStream& data, std::size_t n)
	{
		_data.insert(n,data.toString());
	}

	void ByteStream::saveToFile(const std::string& filename) const
	{
		std::ofstream file(filename.c_str(),std::ios::out | std::ios::binary | std::ios::trunc);
		if(!file.is_open()) throw std::runtime_error("failed to open file " + filename);

		file.write(this->data(),this->size());
		file.close();
	}

	void ByteStream::setBYTE(const BYTE data, std::size_t n)
	{
		_data.replace(n,1,(const char*)&data,1);
	}

	void ByteStream::setWORD(const WORD data, std::size_t n)
	{
		_data.replace(n,2,(const char*)&data,2);
	}

	void ByteStream::setDWORD(const DWORD data, std::size_t n)
	{
		_data.replace(n,4,(const char*)&data,4);
	}

	void ByteStream::setQWORD(const QWORD data, std::size_t n)
	{
		_data.replace(n,8,(const char*)&data,8);
	}

	void ByteStream::setSTREAM(const ByteStream& data, std::size_t n)
	{
		_data.replace(n,data.size(),data.toString());
	}

	void ByteStream::setSTREAM(const void *data, std::size_t dataLen, std::size_t n)
	{
		_data.replace(n,dataLen,reinterpret_cast<const char*>(data));
	}

	ByteStream ByteStream::operator +(const ByteStream& other)
	{
		return _data + other._data;
	}

	ByteStream &ByteStream::operator +=(const ByteStream& other)
	{
		_data += other._data;
		return *this;
	}

	ByteStream &ByteStream::operator =(const ByteStream &other)
	{
		_data = other._data;
		return *this;
	}

	ByteStream &ByteStream::operator =(ByteStream &&other)
	{
		if(this == &other) return *this;
		_data = std::move(other._data);
		return *this;
	}

	bool ByteStream::operator ==(const ByteStream &other)
	{
		return _data == other._data;
	}
}
