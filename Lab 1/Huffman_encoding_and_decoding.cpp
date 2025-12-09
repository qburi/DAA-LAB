#include <bits/stdc++.h>

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
    unordered_map<char, string> codes; // { character : binary_string }

    HuffmanAlgorithm(string& toEncode) {
        root = buildTree(toEncode);
        generateCodes(root, "");
    }

    TreeNode* buildTree(string& toEncode) {
        auto cmp = [&](TreeNode* left, TreeNode* right) {
            return left->freq > right->freq; // left will have less priority -> ascending order
        };
        priority_queue<TreeNode*, vector<TreeNode*>, decltype(cmp)> pq(cmp);

        unordered_map<char, int> freqMap;
        for (char c: toEncode)
            freqMap[c]++;

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


    string decode(string& code) {
        string result = "";
        TreeNode* current = root;

        for (char bit: code) {
            if (bit == '0') current = current->left;
            else current = current->right;

            if (current->left == nullptr && current->right == nullptr) {
                result.push_back(current->key);
                current = root;
            }
        }
        return result;
    }
};

int main() {
    string input = "banana";
    HuffmanAlgorithm huff(input);

    cout << "Input: " << input << endl;
    cout << "Codes:" << endl;
    for(auto pair : huff.codes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    string encoded = "";
    for(char c : input) encoded += huff.codes[c];

    cout << "\nEncoded: " << encoded << endl;
    cout << "Decoded: " << huff.decode(encoded) << endl;

    return 0;
}