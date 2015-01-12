#ifndef BYTESTREAM_H
#define BYTESTREAM_H

#include <string>

#include <kq/def.h>

namespace kq{

	class ByteStream{
	public:

		ByteStream(const void * data, std::size_t len);
		ByteStream(const std::basic_string<char> &);
		ByteStream(const char *);
		ByteStream(std::size_t reservedSize);
		ByteStream();
		ByteStream(ByteStream &&other);
		ByteStream(ByteStream const& other);


		// adds at the end!
		void pushBYTE(const BYTE data);
		void pushWORD(const WORD data);
		void pushDWORD(const DWORD data);
		void pushQWORD(const QWORD data);
		void pushSTREAM(const ByteStream& data);
		void pushSTREAM(const void *, std::size_t);


		// pops remove value from the stream
		BYTE popBYTE();
		WORD popWORD();
		DWORD popDWORD();
		QWORD popQWORD();
		ByteStream popSTREAM(std::size_t len);


		void insertBYTE(const BYTE data, std::size_t n=0);
		void insertWORD(const WORD data, std::size_t n=0);
		void insertDWORD(const DWORD data, std::size_t n=0);
		void insertQWORD(const QWORD data, std::size_t n=0);
		void insertSTREAM(const ByteStream& data, std::size_t n=0);


		// just read values from the stream.
		BYTE readBYTE(std::size_t pos=0)const;
		WORD readWORD(std::size_t pos=0)const;
		DWORD readDWORD(std::size_t pos=0)const;
		QWORD readQWORD(std::size_t pos=0)const;
		ByteStream readSTREAM(std::size_t pos=0, std::size_t len=0) const;

		//overwriting
		void setBYTE(BYTE d, std::size_t n);
		void setWORD(WORD d, std::size_t n);
		void setDWORD(DWORD d, std::size_t n);
		void setQWORD(QWORD d, std::size_t n);
		void setSTREAM(const ByteStream&, std::size_t n);
		void setSTREAM(const void * data, std::size_t data_len, std::size_t pos);


		inline BYTE& operator[](std::size_t n) { return reinterpret_cast<BYTE&>(_data[n]); }
		inline const BYTE& operator[](std::size_t n) const { return reinterpret_cast<BYTE const&>(_data[n]); }

		inline const char * data()const{return _data.data();}

		inline void erase(std::size_t start = 0, std::size_t len = 0) { _data.erase(start,len); }

		inline void reserve(std::size_t n) { _data.reserve(n); }

		inline void resize(std::size_t n) { _data.resize(n); }
		inline std::size_t size() const { return _data.size(); }

		inline std::basic_string<char> toString() { return _data; }
		inline const std::basic_string<char>& toString() const { return _data; }

		operator std::basic_string<char>&() { return _data; }
		operator const std::basic_string<char>&() const { return _data; }

		void saveToFile(const std::string& filename) const;

		ByteStream operator+(ByteStream const& other);
		ByteStream& operator+=(ByteStream const& other);

		ByteStream& operator=(ByteStream const& other);
		ByteStream& operator=(ByteStream && other);

		bool operator==(ByteStream const& other);



	private:
		std::basic_string<char> _data;
	};

}

#endif
