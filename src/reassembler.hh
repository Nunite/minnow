#pragma once
#include "byte_stream.hh"
#include <set>

class Reassembler
{

public:
  explicit Reassembler( ByteStream&& output ) : output_( std::move( output ) ) {}
  // 插入一个可组组装的子string到ByteStream
  void insert( uint64_t first_index, std::string data, bool is_last_substring );
  // 组装器本身存储了多少字节？
  uint64_t bytes_pending() const;
  // Access output stream reader
  Reader& reader() { return output_.reader(); }
  const Reader& reader() const { return output_.reader(); }

  // Access output stream writer, but const-only (can't write from outside)
  const Writer& writer() const { return output_.writer(); }

private:
  ByteStream output_;
  struct Seg
  {
    uint64_t first_index;
    std::string data;
    bool operator<( const Seg& other ) const { return first_index < other.first_index; }
    Seg( uint64_t f, const std::string& d )
    {
      first_index = f;
      data = d;
    }
  };
  std::set<Seg> Segments_ {};
  uint64_t nread_ {};
  uint64_t nwrite_ {};
  uint64_t used_{};
};