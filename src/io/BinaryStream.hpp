#ifndef RAXML_IO_BINARYSTREAM_HPP_
#define RAXML_IO_BINARYSTREAM_HPP_

#include <cstring>
#include <fstream>
#include <cstdint>
#include <stdexcept>

class BasicBinaryStream
{
public:
  virtual ~BasicBinaryStream();

  template<typename T>
  T get()
  {
    T tmp;
    *this >> tmp;
//    get(&tmp, sizeof(T));
    return tmp;
  }

  /* can be used to distinguish between versions or flavors of a binary format */
  uint32_t version() const { return _version; }
  void version(uint32_t ver) { _version = ver; }

  void get(void *data, size_t size) { read(data, size); }
  void put(const void *data, size_t size) { write(data, size); }
  void skip(size_t size) { read(nullptr, size); }

public:
  virtual void write(const void *data, size_t size) = 0;
  virtual void read(void *data, size_t size) = 0;

protected:
  uint32_t _version;

  BasicBinaryStream() : _version(0) {}
};

class BinaryNullStream : public BasicBinaryStream
{
public:
  BinaryNullStream();

  size_t pos() const { return _pos; }
  void reset() { _pos = 0; }

  virtual void write(const void * /* data */, size_t size) override;
  virtual void read(void *data, size_t size) override;

private:
  size_t _pos;
};

class BinaryStream : public BasicBinaryStream
{
public:
  BinaryStream(char * buf, size_t size);

  ~BinaryStream() override {}

  const char* buf() { return _buf; }
  size_t size() const { return _size; }
  size_t pos() const { return (size_t) (_ptr - _buf);}
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
  void write(const void *data, size_t size) override;
  void read(void *data, size_t size) override;

private:
  char * _buf;
  char * _ptr;
  size_t _size;
};

class BinaryFileStream : public BasicBinaryStream
{
public:
  BinaryFileStream(const std::string& fname, std::ios_base::openmode mode) :
    BasicBinaryStream(), _fstream(fname, std::ios::binary | mode) {}

public:
  void write(const void *data, size_t size) override;
  void read(void *data, size_t size) override;

  bool good() const { return _fstream.good(); }

private:
  std::fstream _fstream;
};

#endif /* RAXML_IO_BINARYSTREAM_HPP_ */
