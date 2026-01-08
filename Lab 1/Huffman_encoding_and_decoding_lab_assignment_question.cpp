#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

struct TreeNode {
    char key;
    int freq;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char key, int freq) : key(key), freq(freq), left(nullptr), right(nullptr) {}
};

class HuffmanAlgorithm {
public:
    TreeNode* root = nullptr;
    unordered_map<char, string> codes; 

    // Constructor 1: For normal string input (like "banana")
    HuffmanAlgorithm(string& toEncode) {
        unordered_map<char, int> freqMap;
        for (char c: toEncode) freqMap[c]++;
        root = buildTree(freqMap);
        generateCodes(root, "");
    }

    // Constructor 2: For explicit frequencies (LAB PROBLEM)
    HuffmanAlgorithm(unordered_map<char, int>& freqMap) {
        root = buildTree(freqMap);
        generateCodes(root, "");
    }

    // Refactored to take map directly
    TreeNode* buildTree(unordered_map<char, int>& freqMap) {
        auto cmp = [&](TreeNode* left, TreeNode* right) {
            return left->freq > right->freq; 
        };
        priority_queue<TreeNode*, vector<TreeNode*>, decltype(cmp)> pq(cmp);

        for (auto& p: freqMap)
            pq.push(new TreeNode(p.first, p.second));

        while (pq.size() > 1) {
            TreeNode* leftPop = pq.top(); pq.pop();
            TreeNode* rightPop = pq.top(); pq.pop();
            TreeNode* newNode = new TreeNode('*', leftPop->freq + rightPop->freq);
            newNode->left = leftPop;
            newNode->right = rightPop;
            pq.push(newNode);
        }
        return pq.top();
    }

    void generateCodes(TreeNode* node, string currentCode) {
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) {
            codes[node->key] = currentCode;
            return;
        }
        generateCodes(node->left, currentCode + "0");
        generateCodes(node->right, currentCode + "1");
    }
};

int main() {
    // Problem from Slide 10: Frequencies derived from first 8 prime numbers
    // Primes: 2, 3, 5, 7, 11, 13, 17, 19
    unordered_map<char, int> labFrequencies = {
        {'a', 2}, {'b', 3}, {'c', 5}, {'d', 7}, 
        {'e', 11}, {'f', 13}, {'g', 17}, {'h', 19}
    };

    HuffmanAlgorithm huff(labFrequencies);

    cout << "--- Lab Problem Output ---" << endl;
    cout << "Char\tFreq\tCode" << endl;
    for(auto pair : labFrequencies) {
        cout << pair.first << "\t" << pair.second << "\t" << huff.codes[pair.first] << endl;
    }

    return 0;
}