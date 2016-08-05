#pragma once

#include <string>
#include <vector>

namespace algorithm {

  template <class StrT>
  inline std::vector<size_t> init_delta(const StrT& pat) {
    size_t char_size(std::pow(2, sizeof(typename StrT::value_type) * 8));
    std::vector<size_t> delta(char_size, pat.size());
    for (size_t k = 1; k <= pat.size(); ++k)
      delta[pat[k - 1]] = pat.size() - k;
    return std::move(delta);
  }

  template <class StrT>
  inline int search(const StrT& text, const StrT& pat) {
    if (pat.empty() || text.empty() || pat.size() > text.size())
      return -1;

    auto delta = init_delta(pat);
    const size_t patlen = pat.size();
    size_t i = patlen, j;

    while (i <= text.size()) {
      j = patlen;
      while (text[--i] == pat[--j])
        if (j == 0)
          return int(i);
      i += std::max(delta[text[i]], patlen - j + 1);
    }
    return -1;
  }

  template <class StrT>
  inline std::vector<size_t> search_all(const StrT& text, const StrT& pat) {
    std::vector<size_t> indices;
    if (pat.empty() || text.empty() || pat.size() > text.size())
      return indices;

    auto delta = init_delta(pat);
    const size_t patlen = pat.size();
    size_t i = patlen, j;

    while (i <= text.size()) {
      j = patlen;
      while (text[--i] == pat[--j])
        if (j == 0) {
          indices.push_back(i);
          break;
        }

      if (j == 0)
        i += patlen + 1;
      else
        i += std::max(delta[text[i]], patlen - j + 1);
    }
    return indices;
  }
}

