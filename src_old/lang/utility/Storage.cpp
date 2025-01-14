#include "Storage.h"

#include <iostream>

void Reader::sync(int8_t& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(uint8_t& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(int16_t& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(uint16_t& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(int32_t& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(uint32_t& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(int64_t& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(uint64_t& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(float& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(double& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(bool& value)
{
    stream_.read(reinterpret_cast<char*>(&value), sizeof(value));
}

void Reader::sync(std::string& value)
{
    uint64_t size;
    sync(size);
    value.resize(size);

    uint64_t const max_size = std::numeric_limits<std::streamsize>::max();
    uint64_t       read     = 0;

    while (read < size)
    {
        uint64_t const to_read = std::min(size - read, max_size);
        stream_.read(&value[read], static_cast<std::streamsize>(to_read));
        read += to_read;
    }
}

void Writer::sync(int8_t& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(uint8_t& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(int16_t& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(uint16_t& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(int32_t& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(uint32_t& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(int64_t& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(uint64_t& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(float& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(double& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(bool& value)
{
    stream_.write(reinterpret_cast<char*>(&value), sizeof(value));
}

void Writer::sync(std::string& value)
{
    uint64_t size = value.size();
    sync(size);

    uint64_t const max_size = std::numeric_limits<std::streamsize>::max();
    uint64_t       written  = 0;

    while (written < size)
    {
        uint64_t const to_write = std::min(size - written, max_size);
        stream_.write(&value[written], static_cast<std::streamsize>(to_write));
        written += to_write;
    }
}
