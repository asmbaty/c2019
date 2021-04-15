// three-way operator with std::tie
#include <iostream>
#include <compare>
#include <tuple>
#include <string>

using namespace std::string_literals;

struct headphone {
    int max_volume;
    double quality;
    std::string color;
    std::string vendor;

    /// @note Check for performance
    [[nodiscard]] auto operator <=> (const headphone& rhs) const {
        return std::tie(quality, max_volume) <=> std::tie(rhs.quality, rhs.max_volume);
    }

    [[nodiscard]] auto operator == (const headphone& rhs) const {
        return quality == rhs.quality && max_volume == rhs.max_volume;
    }
};

int main(int argc, char const *argv[])
{
    headphone h1 {
        .max_volume = 12,
        .quality = 5.0,
        .color = "red",
        .vendor = "huawei"
    };

    headphone h2 {
        .max_volume = 13,
        .quality = 5.0,
        .color = "green",
        .vendor = "samsung"
    };

    if(h1 < h2) {
        std::cout << "Second headphone is better\n";
    }

    return 0;
}
