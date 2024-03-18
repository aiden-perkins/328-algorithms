using namespace std;

#ifndef ALGORITHMS_HUFFMANENCODING_H
#define ALGORITHMS_HUFFMANENCODING_H

class HuffmanEncoding {
    private:
        static vector<string> parseInput(const string&);
    public:
        static int huffman(const string&);
};

#endif //ALGORITHMS_HUFFMANENCODING_H
