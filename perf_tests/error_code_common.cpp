#include "error_code_common.h"

const char* error_category::name() const noexcept
{
  return "Error codes";
}

std::string error_category::message(int ev) const
{
  switch (static_cast<error_code>(ev))
  {
  case error_code::success:
    return "The operation succeeded.";
  case error_code::fail:
    return "The operation failed.";
  default:
    return "Unknown error code.";
  }
}
