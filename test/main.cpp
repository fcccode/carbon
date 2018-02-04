#include "../include/carbon.hpp"
#include <fstream>
#include <vector>
#include <list>
#include <tuple>
#include <array>

struct baz {
    std::vector<int> v;
    std::size_t      s;
    CARBON_SERIALIZABLE(baz, v, s);
};

struct triv_copyable {
    int    i;
    float  f;
    double d;
};

struct foo {
    triv_copyable          tc;
    int                    i;
    std::tuple<int, float> t;
    std::list<baz>         b;
    std::array<int, 5>     a;
    CARBON_SERIALIZABLE(foo, tc, i, a);
};

int main()
{
    foo                       f;
    f.i    = 2;
    f.t    = std::make_tuple(2, 3.f);
    f.b    = { { { 1, 2, 3 }, 4 }, { { 4, 5, 6, 7 }, 5 }, { { 8, 9 }, 10 } };
    f.a[0] = 1;
    f.a[1] = 2;


    std::ifstream in("test.txt", std::ios::binary);

    if (in.is_open()) {
        carbon::deserialize<carbon::archive::binary>(f, in);
        in.close();
    }
    std::ofstream out("test.txt", std::ios::binary);
    carbon::serialize<carbon::archive::binary>(f, out);
}
