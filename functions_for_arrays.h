#pragma once

///functions for arrays of basic types///

///  return begin elements  ///
template <typename T, size_t N>
const T* begin(const T(&str)[N]) { return str; }

///  return end elements  ///
template <typename T, size_t N>
const T* end(const T(&str)[N]) { return str + N; }

/// return size array ///
template <typename T, size_t N>
const T size(const T(&str)[N]) { return N; }
