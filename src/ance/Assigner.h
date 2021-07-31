#ifndef ANCE_SRC_ANCE_ASSIGNER_H_
#define ANCE_SRC_ANCE_ASSIGNER_H_

class Assigner
{
  public:
    enum Value
    {
        COPY_ASSIGNMENT,
        MOVE_ASSIGNMENT,
        FINAL_COPY_ASSIGNMENT
    };

    Assigner() = default;
    constexpr Assigner(Value val) : value_(val) {}// NOLINT(google-explicit-constructor)

             operator Value() const;// NOLINT(google-explicit-constructor)
    explicit operator bool() = delete;

    bool isFinal();

  private:
    Value value_;
};

#endif
