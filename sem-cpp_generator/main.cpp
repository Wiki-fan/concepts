#include <iostream>
#include <istream>
#include <fstream>

class CFibonacciGenerator {
 public:
    class CFibIterator {
     public:
        std::string operator*() const { return word; }

        bool operator==(const CFibIterator& other) const { return (isEnd == other.isEnd && index == other.index) || (isEnd == true && other.isEnd == true); }
        bool operator!=(const CFibIterator& other) const { return !(*this == other); }

        CFibIterator& operator++() {
            ++index;
            word = gen.getNextToken();
            if (word.empty()) {
                isEnd = true;
            }
            return *this;
        }

     private:
        CFibIterator(CFibonacciGenerator& gen, bool isEnd) : gen(gen), index(0), isEnd(isEnd) {
            word = gen.getNextToken();
            if (word.empty()) {
                isEnd = true;
            }
        }

        int index;
        bool isEnd;
        CFibonacciGenerator& gen;
        std::string word;

        friend class CFibonacciGenerator;
    };

    explicit CFibonacciGenerator(std::istream& istream) : istream(istream) {}

    CFibIterator begin() { return CFibIterator(*this, false); }
    CFibIterator end() { return CFibIterator(*this, true); }

    std::string getNextToken() {
        std::string s;
        istream >> s;
        return s;
    }
 private:
    std::istream& istream;
    int numberCount;
};

int main() {
    std::ifstream ifs("/home/sharik/code/concepts2/text.txt", std::ios_base::in);
    if (!ifs.is_open()) {
        return 12;
    }
    for (auto&& word : CFibonacciGenerator(ifs)) {
        std::cout << word<< std::endl;
    }
    return 0;
}