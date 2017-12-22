#pragma once
#include <x86intrin.h>

class u64vec4;

class u64vec4 {
 public:
  u64vec4(__m256i data) : data(data) {}
  u64vec4() = default;
  explicit u64vec4(uint64_t x)
    : data(_mm256_set1_epi64x(x)) {}
  u64vec4(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3)
    : data(_mm256_set_epi64x(x3, x2, x1, x0)) {}
  u64vec4(const u64vec4 &) = default;
  u64vec4 &operator=(const u64vec4 &) = default;
  operator __m256i() const { return data; }
  __m256i data;
};

inline u64vec4 operator|(const u64vec4 &lhs, const u64vec4 &rhs) {
  return u64vec4(_mm256_or_si256(lhs.data, rhs.data));
}

inline u64vec4 operator|=(u64vec4 &lhs, const u64vec4 &rhs) {
  return lhs = lhs | rhs;
}

inline u64vec4 operator&(const u64vec4 &lhs, const u64vec4 &rhs) {
  return u64vec4(_mm256_and_si256(lhs.data, rhs.data));
}

inline u64vec4 operator&=(u64vec4 &lhs, const u64vec4 &rhs) {
  return lhs = lhs & rhs;
}

inline u64vec4 andnot(const u64vec4 &lhs, const u64vec4 &rhs) {
  return u64vec4(_mm256_andnot_si256(lhs.data, rhs.data));
}

inline u64vec4 operator^(const u64vec4 &lhs, const u64vec4 &rhs) {
  return u64vec4(_mm256_xor_si256(lhs.data, rhs.data));
}

inline u64vec4 operator^=(u64vec4 &lhs, const u64vec4 &rhs) {
  return lhs = lhs ^ rhs;
}

inline u64vec4 operator~(const u64vec4 &that) {
  __m256i x = _mm256_undefined_si256();
  return u64vec4(_mm256_andnot_si256(that.data,
      _mm256_cmpeq_epi64(x, x)));
}

inline u64vec4 operator+(const u64vec4 &lhs, const u64vec4 &rhs) {
  return u64vec4(_mm256_add_epi64(lhs.data, rhs.data));
}

inline u64vec4 operator-(const u64vec4 &lhs, const u64vec4 &rhs) {
  return u64vec4(_mm256_sub_epi64(lhs.data, rhs.data));
}

inline u64vec4 operator-(const u64vec4 &that) {
  return u64vec4(_mm256_sub_epi64(_mm256_setzero_si256(), that.data));
}

inline u64vec4 operator<<(const u64vec4 &lhs, const u64vec4 &rhs) {
  return u64vec4(_mm256_sllv_epi64(lhs.data, rhs.data));
}

inline u64vec4 operator<<(const u64vec4 &lhs, const int &rhs) {
  return u64vec4(_mm256_slli_epi64(lhs.data, rhs));
}

inline u64vec4 operator>>(const u64vec4 &lhs, const u64vec4 &rhs) {
  return u64vec4(_mm256_srlv_epi64(lhs.data, rhs.data));
}

inline u64vec4 operator>>(const u64vec4 &lhs, const int &rhs) {
  return u64vec4(_mm256_srli_epi64(lhs.data, rhs));
}

inline bool operator==(const u64vec4 &lhs, const u64vec4 &rhs) {
  __m256i x = _mm256_xor_si256(lhs.data, rhs.data);
  return _mm256_testz_si256(x, x);
}

class u64vec2 {
 public:
  u64vec2(__m128i data) : data(data) {}
  u64vec2() = default;
  u64vec2(const u64vec2 &) = default;
  u64vec2 &operator=(const u64vec2 &) = default;
  operator __m128i() const { return data; }
  uint64_t lo() const {
    return _mm_cvtsi128_si64(data);
  }
  uint64_t hi() const {
    return _mm_extract_epi64(data, 1);
  }
  __m128i data;
};

inline u64vec2 operator|(const u64vec2 &lhs, const u64vec2 &rhs) {
  return u64vec2(_mm_or_si128(lhs.data, rhs.data));
}

inline u64vec2 operator|=(u64vec2 &lhs, const u64vec2 &rhs) {
  return lhs = lhs | rhs;
}
