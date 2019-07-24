// Flyweight Design Pattern
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

// Research: Boost.Flyweight

class formatted_text
{
public:
    struct text_range
    {
        int start, end;

        bool covers(int idx) const {
            return start <= idx && idx < end;
        }

        //text_range(int _start, int _end) : start(_start), end(_end) { std::cout << "construct\n";}
        //text_range(text_range const& other) : start(other.start), end(other.end) { std::cout << "copied\n";}
        //text_range(text_range&& other) : start(other.start), end(other.end) { std::cout << "moved\n";}

    };

    formatted_text(const std::string& str) : plain_text(str) {}

    text_range& capitalize(int start, int end)
    {
        formatting.emplace_back(text_range{start,end});
        return *formatting.rend();
    }

    friend std::ostream& operator << (std::ostream& out, const formatted_text& obj)
    {
        int len = static_cast<int>(obj.plain_text.size());
        for(int i = 0; i<len; ++i)
        {
            auto c = obj.plain_text[i];
            for(const auto& tr : obj.formatting) {
                    if(tr.covers(i))
                         c = toupper(c);
            }
            out << c;
        }
        return out;
    }

private:
    std::string plain_text;
    std::vector<text_range> formatting;
};

int main(int argc, char const *argv[])
{
    formatted_text t {"hello, how are you?"};
    t.capitalize(7,10);
    std::cout << t << '\n';

    return 0;
}
