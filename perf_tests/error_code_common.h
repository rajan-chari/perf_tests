#pragma once
#include <system_error>

enum class error_code {
    success,
    fail,
};

namespace std
{
  template <>
    struct is_error_code_enum<::error_code> : true_type {};
}

struct error_category : std::error_category
{
  const char* name() const noexcept override;
  std::string message(int ev) const override;
};

const error_category _error_category {};
inline std::error_code make_error_code(error_code e)
{
  return {static_cast<int>(e), _error_category};
}
