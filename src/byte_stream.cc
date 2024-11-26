#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity )
{
  buffer_.reserve( capacity );
}

bool Writer::is_closed() const
{
  // Your code here.
  return isclosed_;
}

void Writer::push( string data )
{
  if ( is_closed() )
    return;
  // Your code here.
  uint64_t len = min( data.size(), available_capacity() );
  buffer_ += data.substr( 0, len );
  bytes_pushed_ += len;
}

void Writer::close()
{
  // Your code here.
  isclosed_ = true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return isclosed_ && buffer_.size() == 0;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return bytes_poped_;
}

string_view Reader::peek() const
{
  // Your code here.
  string_view sv( buffer_.data(), min( static_cast<uint64_t>( 1024 ), bytes_buffered() ) );
  return sv;
}

void Reader::pop( uint64_t len )
{ // Your code here.
  buffer_.erase( buffer_.begin(), buffer_.begin() + len );
  bytes_poped_ += len;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return buffer_.size();
}
