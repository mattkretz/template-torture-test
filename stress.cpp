/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright © 2024      GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
 *                       Matthias Kretz <m.kretz@gsi.de>
 */

template <typename T, typename U>
  struct Add
  {};

template <typename...>
  struct Operand
  {};

template <typename... Ts, typename... Us>
#ifdef GO_FAST
  Operand<Add<Operand<Ts...>, Operand<Us...>>>
#else
  Operand<Ts..., Us...>
#endif
  operator+(const Operand<Ts...>&, const Operand<Us...>&)
  { return {}; }

auto
stress_me(auto x)
{
  return (x + x) + x + (x + (x + x) + x) + x + x;
}

auto
apply_stress(auto op)
{
#if STRESS == 1
  return stress_me(op);
#elif STRESS == 2
  return stress_me(stress_me(op));
#elif STRESS == 3
  return stress_me(stress_me(stress_me(op)));
#elif STRESS == 4
  return stress_me(stress_me(stress_me(stress_me(op))));
#elif STRESS == 5
  return stress_me(stress_me(stress_me(stress_me(stress_me(op)))));
#elif STRESS == 6
  return stress_me(stress_me(stress_me(stress_me(stress_me(stress_me(op))))));
#elif STRESS == 7
  return stress_me(stress_me(stress_me(stress_me(stress_me(stress_me(stress_me(
           op)))))));
#elif STRESS == 8
  return stress_me(stress_me(stress_me(stress_me(stress_me(stress_me(stress_me(
           stress_me(stress_me(op)))))))));
#else
  return stress_me(stress_me(stress_me(stress_me(stress_me(stress_me(stress_me(
           stress_me(stress_me(op)))))))));
#endif
}

#ifdef TORTURE
template <typename... Ts>
  struct typelist
  {};

void
invoke(auto);

template <typename T0, typename... Ts>
  void
  apply(typelist<T0, Ts...>, auto&& fun)
  {
    fun(T0{});
    if constexpr (sizeof...(Ts))
      apply(typelist<Ts...>(), fun);
  }
#endif

template <typename T>
  Operand<T>
  make_operand(T)
  { return {}; }

auto
pah()
{
#ifdef TORTURE
  apply(typelist<char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t,
                 short, unsigned short, int, unsigned, long, unsigned long, long long,
                 unsigned long long, float, double, long double, bool>(),
        [](auto op) {
          apply(typelist<char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t,
                         short, unsigned short, int, unsigned, long, unsigned long, long long,
                         unsigned long long, float, double, long double, bool>(),
                [&op](auto op2) {
                  invoke(apply_stress(make_operand(op) + make_operand(op2)));
                });
        });
#else
  return apply_stress(make_operand(1) + make_operand(2l));
#endif
}
