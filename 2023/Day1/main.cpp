#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <fstream>
#include <unordered_map>
#include <map>

// we want the first and the last number of the line
std::pair<int, int> find_numbers(std::string const &line) {
    int first = 0;
    int last = 0;

    for(auto const &c : line) {
        if(std::isdigit(c)) {
            if(first == 0) {
                first = static_cast<int>(c) - static_cast<int>('0');
            }

            last = static_cast<int>(c) - static_cast<int>('0');
        }
    }

    return std::make_pair(first, last);
}

// we want the first and the last number of the line and they can alse be a word "one,two,three" etc.
std::pair<int, int> find_numbers2(std::string const &line) {
    const std::map<std::string, int> nr_map = {
        {"one",   1},
        {"two",   2},
        {"three", 3},
        {"four",  4},
        {"five",  5},
        {"six",   6},
        {"seven", 7},
        {"eight", 8},
        {"nine",  9}
    };

    int first = 0;
    int last = 0;

    for(auto i = 0; i < line.length(); i++) {
        auto c = line[i];
        if(std::isdigit(c)) {
            if(first == 0) {
                first = static_cast<int>(c) - static_cast<int>('0');
            }
            last = static_cast<int>(c) - static_cast<int>('0');
        }
        else {
            int nr = 0;
            for (auto &[key, val] : nr_map) {
                if (line.substr(i, key.size()) == key) {
                    nr = val;
                    break;
                }
            }

            if(nr == 0) {
                continue;
            }

            if(first == 0) {
                first = nr;
            }

            last = nr;
        }
    }


    return std::make_pair(first, last);
}

std::vector<std::string> file_content(std::string const &file) {
    std::ifstream f("input.txt");

    if (!f.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return {};
    }

    std::vector<std::string> ret;
    std::string line;

    while (std::getline(f, line)) {
        ret.push_back(line);
    }
    f.close();

    return ret;
}

int main()
{
    auto input = file_content("input.txt");

    // part one
    int sum = 0;
    for(auto const &l : input) {
        auto num = find_numbers(l);
        sum += ((num.first * 10) + num.second);
    }
    std::cout << "sum of numbers part one: " << sum << std::endl;

    // part two
    int sum2 = 0;
    for(auto const &l : input) {
        auto num = find_numbers2(l);
        sum2 += ((num.first * 10) + num.second);
    }
    std::cout << "sum of numbers part two: " << sum2 << std::endl;

    return 0;
}
