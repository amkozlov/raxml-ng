#ifndef RAXML_IO_BINARYSTREAM_HPP_
#define RAXML_IO_BINARYSTREAM_HPP_

#include <cstring>
#include <fstream>
#include <stdexcept>


class BasicBinaryStream
{
public:
  virtual ~BasicBinaryStream() {}

  template<typename T>
  T get()
  {
    T tmp;
    *this >> tmp;
//    get(&tmp, sizeof(T));
    return tmp;
  }

  void get(void *data, size_t size) { read(data, size); }
  void put(const void *data, size_t size) { write(data, size); }
  void skip(size_t size) { read(nullptr, size); }

public:
  virtual void read(void *data, size_t size) = 0;
  virtual void write(const void *data, size_t size) = 0;
};

class BinaryNullStream : public BasicBinaryStream
{
public:
  BinaryNullStream(): _pos(0) {}

  size_t pos() const { return _pos; }
  void reset() { _pos = 0; }

  void write(const void * /* data */, size_t size)
  {
    _pos += size;
  }

  virtual void read(void *data, size_t size)
  {
    memset(data, 0, size);
    _pos += size;
  }

private:
  size_t _pos;
};

class BinaryStream : public BasicBinaryStream
{
public:
  BinaryStream(char * buf, size_t size)
  {
    _buf = buf;
    _ptr = buf;
    _size = size;
  }

  ~BinaryStream() {}

  const char* buf() { return _buf; }
  size_t size() const { return _size; }
  size_t pos() const { return _ptr - _buf;}
  char* reset() { _ptr = _buf; return _buf; }

  template<typename T>
  static size_t serialized_size(const T& obj)
  {
    BinaryNullStream bs;

    bs << obj;

    return bs.pos();
  }

  template<typename T>
  static size_t serialize(char * buf, size_t size, const T& obj)
  {
    BinaryStream bs(buf, size);

    bs << obj;

    return bs.pos();
  }

public:
  void write(const void *data, size_t size)
  {
    if (_ptr + size > _buf + _size)
      throw std::out_of_range("BinaryStream::put");

    memcpy(_ptr, data, size);
    _ptr += size;
  }

  void read(void *data, size_t size)
  {
    if (_ptr + size > _buf + _size)
      throw std::out_of_range("BinaryStream::get");

    if (data)
      memcpy(data, _ptr, size);
    _ptr += size;
  }

private:
  char * _buf;
  char * _ptr;
  size_t _size;
};

class BinaryFileStream : public BasicBinaryStream
{
public:
  BinaryFileStream(const std::string& fname, std::ios_base::openmode mode) :
    _fstream(fname, std::ios::binary | mode) {}

public:
  void write(const void *data, size_t size) { _fstream.write((char*) data, size); }
  void read(void *data, size_t size)
  {
    if (data)
      _fstream.read((char*) data, size);
    else
      _fstream.seekg(size, std::ios_base::cur);
  }

  bool good() const { return _fstream.good(); }

private:
  std::fstream _fstream;
};

#endif /* RAXML_IO_BINARYSTREAM_HPP_ */
