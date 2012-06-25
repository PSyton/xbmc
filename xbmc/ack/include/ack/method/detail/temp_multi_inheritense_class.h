#pragma once

namespace ack {
namespace detail {

//! Dummy parent class
class parent1
{};

//! Another parent
class parent2
{};

//! dummy multiple inheritance
class temp_multi_inheritense
  : public parent1
  , public parent2
{};

} // namespace detail
} // namespace ack
