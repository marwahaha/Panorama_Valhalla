#ifndef VALHALLA_MEILI_STATE_H_
#define VALHALLA_MEILI_STATE_H_

#include <cstdint>
#include <functional>
#include <limits>

namespace valhalla {
namespace meili {

constexpr uint32_t kInvalidTime = std::numeric_limits<uint32_t>::max();

union StateId
{
 public:
  using Time = uint32_t;

  using Id = uint32_t;

  StateId()
      : fields_({kInvalidTime, 0})
  {}

  explicit StateId(const Time& time, Id id)
      : fields_({time, id})
  {}

  Time time() const
  { return fields_.time; }

  Id id() const
  { return fields_.id; }

  bool IsValid() const
  { return fields_.time != kInvalidTime; }

  bool operator ==(const StateId& rhs) const
  { return value_ == rhs.value_; }

  bool operator !=(const StateId& rhs) const
  { return value_ != rhs.value_; }

  uint64_t value() const
  { return value_; }

 private:
  struct {
    uint64_t time: 32;
    uint64_t id: 32;
  } fields_;

  uint64_t value_;
};

}
}

// Extend the standard namespace to know how to hash StateIds
namespace std {
template <>
struct hash<valhalla::meili::StateId> {
  inline std::size_t operator()(const valhalla::meili::StateId& stateid) const {
    return static_cast<size_t>(stateid.value());
  }
};
}

#endif // VALHALLA_MEILI_STATE_H_
