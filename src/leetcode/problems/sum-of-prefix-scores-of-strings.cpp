#include "leetcode/problems/sum-of-prefix-scores-of-strings.h"

namespace leetcode {
namespace problem_2416 {

// Trie node structure
struct TrieNode {
    TrieNode* children[26] = {nullptr};
    int count = 0;  // number of words passing through this node
    
    ~TrieNode() {
        for (int i = 0; i < 26; ++i) {
            delete children[i];
        }
    }
};

static vector<int> solution1(vector<string>& words) {
    // Build the Trie
    TrieNode* root = new TrieNode();
    
    // Insert all words into Trie, counting prefix occurrences
    for (const string& word : words) {
        TrieNode* cur = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!cur->children[idx]) {
                cur->children[idx] = new TrieNode();
            }
            cur = cur->children[idx];
            cur->count++;
        }
    }
    
    // For each word, sum up the counts of all its prefixes
    vector<int> result;
    result.reserve(words.size());
    
    for (const string& word : words) {
        TrieNode* cur = root;
        int score = 0;
        for (char c : word) {
            int idx = c - 'a';
            cur = cur->children[idx];
            score += cur->count;
        }
        result.push_back(score);
    }
    
    delete root;
    return result;
}

SumOfPrefixScoresOfStringsSolution::SumOfPrefixScoresOfStringsSolution() {
  setMetaInfo({
      .id = 2416,
      .title = "Sum of Prefix Scores of Strings",
      .url = "https://leetcode.com/problems/sum-of-prefix-scores-of-strings/"
  });
  registerStrategy("Trie", solution1);
}

vector<int> SumOfPrefixScoresOfStringsSolution::sumPrefixScores(vector<string>& words) {
  return getSolution()(words);
}

}  // namespace problem_2416
}  // namespace leetcode
