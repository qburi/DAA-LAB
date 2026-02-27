#include <bits/stdc++.h>


using namespace std;

struct TrieNode {
    vector<TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        children = vector<TrieNode*>(256, nullptr);
        isEndOfWord = false;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string s) {
        TrieNode* curr = root;
        for (int i = 0; i < s.length(); i++) {
            if (curr->children[s[i]] == nullptr)
                curr->children[s[i]] = new TrieNode();
            curr = curr->children[s[i]];
        }
        curr->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode* curr = root;
        for (int i = 0; i < word.length(); i++) {
            if (curr->children[word[i]] == nullptr)
                return false;
            curr = curr->children[word[i]];
        }
        return true;
    }

};

class Solution {
public:
    void printSolution(string s, vector<string> p, int n) {


        Trie trie;
        for (int i = s.length() - 1; i >= 0; i--) {
            trie.insert(s.substr(i));
        }

        cout << "Root edges: ";
        for (int i = 0; i < 256; i++)
            if (trie.root->children[i] != nullptr)
                cout << (char)(i) << " ";
        cout << endl;

        for (string pattern: p)
            if (trie.search(pattern))
                cout << "Pattern found" << endl;
            else
                cout << "Pattern not found" << endl;

    }
};

int main() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> p(n, "");
    for (int i = 0; i < n; i++)
        cin >> p[i];
    Solution solution;
    solution.printSolution(s, p, n);
    return 0;
}