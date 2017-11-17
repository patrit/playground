#include <experimental/array>
#include <iostream>
#include <stdexcept>
#include <array>
#include <tuple>
#include <algorithm>
#include <experimental/string_view>
#include <cstring>

using namespace std::literals::string_literals;
using namespace std::experimental::string_view_literals;

template <std::size_t N>
constexpr
std::array<char, N> to_char_array(char const (&tmpl)[N])
{
    std::array<char, N> s = std::experimental::to_array(tmpl);
    return s;
}

template<unsigned... Is> struct seq{};
template<unsigned N, unsigned... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<typename T, std::size_t N1, unsigned... I1, std::size_t N2, unsigned... I2>
// Expansion pack
constexpr std::array<T, N1+N2> concat(const std::array<T, N1>& a1, const std::array<T, N2>& a2, seq<I1...>, seq<I2...>){
  return { a1[I1]..., a2[I2]... };
}

template<typename T, std::size_t N1, std::size_t N2>
// Initializer for the recursion
constexpr std::array<T, N1+N2> concat(const std::array<T, N1>& a1, const std::array<T, N2>& a2){
  return concat(a1, a2, gen_seq<N1>{}, gen_seq<N2>{});
}


template<typename T, std::size_t NA>
class Array : public std::array<T, NA>
{
public:
    constexpr
    Array(std::array<T, NA> const& value) : std::array<T, NA>(value) {}    
    constexpr
    Array(std::array<T, NA> const& val1, std::array<T, NA> const& val2) : std::array<T, NA>(concat(val1, val2)) {}    
    constexpr
    Array(std::initializer_list<T> l) : std::array<T, NA>(l) {}
private:
    //T[NA];
};

template<std::size_t NC>
struct Char : public Array<char, NC>
{
    Char() {}    
    constexpr
    Char(std::array<char, NC> value) : Array<char, NC>(value) {}    
    Char(std::initializer_list<char> l) : Array<char, NC>(l) {}
    

    template <std::size_t MC>
    constexpr Char<NC + MC>
    operator+(const Char<MC> &other) const {        
        return concat(static_cast< const Array<char, NC> >(*this),
                      static_cast< const Array<char, MC> >(other));
    }
    
};

template<std::size_t K>
std::ostream& operator<<(std::ostream& s, const Char<K>& v) {
    s << std::string(&v[0], K);
}

template<std::size_t NC>
class CharView {
public:
    constexpr
    CharView(const char* data): _data(data) {}
    const char* data() { return _data; }
    size_t size() { return NC; }

    template <std::size_t MC>
    constexpr Char<NC + MC>
    operator+(const CharView<MC> &other)  {
        Char<NC + MC> ret;
        std::memcpy(ret.data(), data(), NC);
        std::memcpy(ret.data() + NC, other.data(), MC);
        return ret;
    }

private:
    const char* _data = nullptr;
};

#define SV(x) CharView<sizeof(x)>(x)

#define STR(x) Char<sizeof(x)>(to_char_array(x))

int main()
{
    constexpr auto a1 = STR("fooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo the ");
    constexpr auto b1 = STR("wunderful ");
    constexpr auto c1 = STR("bra \n");
    constexpr auto d1 = a1 + b1 + c1;
    std::cout << d1;
    std::cout << "\n\n";

    std::string a2 = "fooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo the "s;
    std::string b2 = "wunderful "s;
    std::string c2 = "bra \n"s;
    std::string d2 = a2 + b2 + c2;
    std::cout << d2;
    std::cout << "\n\n";
    
#if 0
    constexpr auto a3 = SV("fooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo the ");
    constexpr auto b3 = SV("wunderful ");
    constexpr auto c3 = SV("bra \n");
    constexpr auto d3 = a3 + b3 + c3;
    std::cout << d3;
    std::cout << "\n\n";
#endif
}
