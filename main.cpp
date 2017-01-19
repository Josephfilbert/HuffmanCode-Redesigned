#include <iostream>
#include <queue>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <limits>
#include <iomanip>
#include <cstring>

#define PARENT_NODE '\1'

void clear_cin() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void invert_endian_int(unsigned int& num) {
    num = (num << 24) | ((num << 8) & 0x00ff0000) | ((num >> 8) & 0x0000ff00) | (num >> 24);
}



class HuffmanCode {
    struct Node {
        char character; //represent character or no character with number -1
        int weight;
        Node* left;
        Node* right;

        //creates Node without weight for decompression
        Node(char c): character(c), weight(0), left(nullptr), right(nullptr) {}

        //create new node for nodes priority queue
        Node(char c, int w): character(c), weight(w), left(nullptr), right(nullptr) {}

        //create new node as parent of two front nodes in queue
        Node(Node* leftChild, Node* rightChild):
            character(-1), weight(leftChild->weight + rightChild->weight), left(leftChild), right(rightChild) {}

        ~Node() {
            //recursive deletion
            if(left!=nullptr) delete left;
            if(right!=nullptr) delete right;
        }

        bool isLeaf() {
            return (left==nullptr && right==nullptr);
        }

        //for custom comparator class
        struct Comparator {
            bool operator()(const Node* left, const Node* right) {
                return left->weight > right->weight;
            }
        };
    };

    std::istream& inputStream;
    std::ostream& outputStream;

public:

    //compress
    HuffmanCode(std::istream& is, std::ostream& os) {

    }


};
