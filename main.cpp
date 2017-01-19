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

template<typename K, typename V>
void insertToMap(std::map<K, V>& mapRef, typename std::map<K, V>::iterator& hint, K key, V value) {
    if(mapRef.empty()) {
        hint = mapRef.insert(std::pair<K, V>(key, value)).first;
    } else {
        hint = mapRef.insert(hint, std::pair<K, V>(key, value));
    }
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

    /*--------------------------------------------------------------------------------
       Constants
    */

    static const std::istreambuf_iterator<char> eosIn;
    static const std::ostreambuf_iterator<char> eosOut;

    /*
    --------------------------------------------------------------------------------
    */

    std::istream& inputStream;
    std::ostream& outputStream;

    //used for tree generation
    std::map<char, int> frequencyMap;
    std::map<char, int>::iterator frequencyMapIterator;
    std::priority_queue<Node*, std::vector<Node*>, Node::Comparator> nodesQueue;


    Node* root;
    std::map<char, std::string> charmap;
    std::map<char, std::string>::iterator charmapIterator;

    unsigned long payloadSize;
    unsigned long compressedBitsSize;


    /*--------------------------------------------------------------------------------
       Below are function routines for compress
    */

    void createCharFreqMap() {
        for(std::istreambuf_iterator<char> iter(inputStream); iter!= eosIn; iter++) {
            if(frequencyMap.empty()) {
                frequencyMapIterator = frequencyMap.insert(std::pair<char, int>(*iter, 1)).first;
            } else {
                frequencyMapIterator = frequencyMap.insert(frequencyMapIterator, std::pair<char, int>(*iter, 0));
                frequencyMapIterator->second += 1;
            }
        }
    }


    void createInitialQueue() {
        for(std::map<char, int>::const_iterator iter = frequencyMap.begin(); iter != frequencyMap.end(); iter++) {
            nodesQueue.push(new Node(iter->first, iter->second));
        }
    }

    void createHuffmanTreeFromQueue() {
        while(nodesQueue.size() > 1) {
            Node* firstNode = nodesQueue.top();
            nodesQueue.pop();

            Node* secondNode = nodesQueue.top();
            nodesQueue.pop();

            nodesQueue.push(new Node(firstNode, secondNode));
        }

        //set the root and clear the queue
        root = nodesQueue.top();
        nodesQueue.pop();
    }


    /*
    ----------------------------------------------------------------------------------
    */

    void createCharMap(const Node* rootNode, std::string code = "") {
        if(rootNode == nullptr) return;

        if(rootNode->left != nullptr) createCharMap(rootNode->left, code + '0');
        if(rootNode->right != nullptr) createCharMap(rootNode->right, code + '1');

        if(rootNode->isLeaf()) {
            insertToMap(charmap, charmapIterator, rootNode->character, code);
        }
    }


    /*--------------------------------------------------------------------------------
       Below are function helper for compression
    */



    /*
    --------------------------------------------------------------------------------
    */


    int compress() {
        int payloadSize = 0; //payload size in bits
        int treeSize = 0; //serialized tree size in bytes
    }

public:

    enum OperationMode {
        comp, decomp
    };

    //compress or decompress from inputStream and output to outputStream
    HuffmanCode(OperationMode om, std::istream& is, std::ostream& os): inputStream(is), outputStream(os) {

    }

    double getCompressionRatio() {

    }

    ~HuffmanCode() {
        delete root;
    }
};
