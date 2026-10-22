#include "BinaryStream.hpp"

using namespace std;

BasicBinaryStream::~BasicBinaryStream()
{}

/* BinaryNullStream */

BinaryNullStream::BinaryNullStream():
    BasicBinaryStream(), _pos(0)
{}

void BinaryNullStream::write(const void * /* data */, size_t size)
{
  _pos += size;
}

void BinaryNullStream::read(void *data, size_t size)
{
  memset(data, 0, size);
  _pos += size;
}

/* BinaryStream */

BinaryStream::BinaryStream(char * buf, size_t size) :
    BasicBinaryStream(), _buf(buf), _ptr(buf), _size(size)
{}

void BinaryStream::write(const void *data, size_t size)
{
  if (_ptr + size > _buf + _size)
    throw std::out_of_range("BinaryStream::put");

  memcpy(_ptr, data, size);
  _ptr += size;
}

void BinaryStream::read(void *data, size_t size)
{
  if (_ptr + size > _buf + _size)
    throw std::out_of_range("BinaryStream::get");

  if (data)
    memcpy(data, _ptr, size);
  _ptr += size;
}


/* BinaryFileStream */

void BinaryFileStream::write(const void *data, size_t size)
{
  _fstream.write((const char*) data, (std::streamsize) size);
}

void BinaryFileStream::read(void *data, size_t size)
{
  if (data)
    _fstream.read((char*) data, (std::streamsize) size);
  else
    _fstream.seekg((std::fstream::off_type) size, std::ios_base::cur);
}
