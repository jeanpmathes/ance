#ifndef ANCE_SRC_LANG_UTILITY_STORAGE_H_
#define ANCE_SRC_LANG_UTILITY_STORAGE_H_

#include <concepts>
#include <string>

class Storage;

/**
 * A type that can be stored in a storage and retrieved from it.
 */
template<typename T>
concept Storable = requires(T* t, Storage& s) {
                       {
                           T::synchronize(t, s)
                       } -> std::same_as<void>;
                   };

/**
 * A storable type with relaxed requirements, used for polymorphic types or types that perform their own indirection.
 * If a type K does not perform indirection, an indirection-type like T = K* should be used as PolymorphicStorable.
 */
template<typename T>
concept PolymorphicStorable = requires(T t, Storage& s) {
                                  {
                                      synchronize(t, s)
                                  } -> std::same_as<void>;
                              };

/**
 * Used to read from and write to.
 */
class Storage
{
  public:
    virtual ~Storage() = default;

    [[nodiscard]] virtual bool isReading() const { return false; }
    [[nodiscard]] virtual bool isWriting() const { return false; }

    virtual void sync(int8_t& value)   = 0;
    virtual void sync(uint8_t& value)  = 0;
    virtual void sync(int16_t& value)  = 0;
    virtual void sync(uint16_t& value) = 0;
    virtual void sync(int32_t& value)  = 0;
    virtual void sync(uint32_t& value) = 0;
    virtual void sync(int64_t& value)  = 0;
    virtual void sync(uint64_t& value) = 0;

    virtual void sync(float& value)  = 0;
    virtual void sync(double& value) = 0;

    virtual void sync(bool& value) = 0;

    virtual void sync(std::string& value) = 0;

    template<Storable T>
    void sync(T& value)
    {
        T::synchronize(&value, *this);
    }

    template<PolymorphicStorable T>
    void sync(T& value)
    {
        synchronize(value, *this);
    }
};

/**
 * Reads from a binary storage using a stream.
 * This uses system endianness.
 */
class Reader : public Storage
{
  public:
    ~Reader() override = default;

    explicit Reader(std::istream& stream) : stream_(stream) {}
    [[nodiscard]] bool isReading() const override { return true; }

    void sync(int8_t& value) override;
    void sync(uint8_t& value) override;
    void sync(int16_t& value) override;
    void sync(uint16_t& value) override;
    void sync(int32_t& value) override;
    void sync(uint32_t& value) override;
    void sync(int64_t& value) override;
    void sync(uint64_t& value) override;
    void sync(float& value) override;
    void sync(double& value) override;
    void sync(bool& value) override;
    void sync(std::string& value) override;

  private:
    std::istream& stream_;
};

/**
 * Writes to a binary storage using a stream.
 * This uses system endianness.
 */
class Writer : public Storage
{
  public:
    ~Writer() override = default;

    explicit Writer(std::ostream& stream) : stream_(stream) {}
    [[nodiscard]] bool isWriting() const override { return true; }

    void sync(int8_t& value) override;
    void sync(uint8_t& value) override;
    void sync(int16_t& value) override;
    void sync(uint16_t& value) override;
    void sync(int32_t& value) override;
    void sync(uint32_t& value) override;
    void sync(int64_t& value) override;
    void sync(uint64_t& value) override;
    void sync(float& value) override;
    void sync(double& value) override;
    void sync(bool& value) override;
    void sync(std::string& value) override;

  private:
    std::ostream& stream_;
};

#endif
