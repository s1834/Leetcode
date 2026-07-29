class WordDictionary {
    private:
        struct TrieNode {
            TrieNode* links[26];
            bool flag = false;
    
            // check if 'c' already exists
            bool containsKey(char c) {
                return links[c - 'a'] != NULL;
            };
    
            // from 'c' create a new empty node
            void put(char c, TrieNode* node) {
                links[c - 'a'] = node;
            }
    
            // move current pointer to newly created node
            TrieNode* get(char c) {
                return links[c - 'a'];
            }
    
            // if word complete, set flag = true;
            void setEnd() {
                flag = true;
            }
            
            // check if a word ends here
            bool isEnd() {
                return flag;
            }
        };
    
        TrieNode* root;
    
        bool dfs(string &word, TrieNode* node, int i) {
            if(i == word.size()) return node->isEnd();
    
            if(word[i] == '.') {
                for(auto x : node->links) {
                    if(x && dfs(word, x, i + 1)) return true; // if one path is found/succeeded
                }
                return false;
            }
    
            // normal character
            if(!node->containsKey(word[i])) return false;
            node = node->get(word[i]);
    
            return dfs(word, node, i + 1);
        }
    
    public:
        WordDictionary() {
            root = new TrieNode();
        }
        
        void addWord(string word) {
            TrieNode* node = root;
            for(auto x : word) {
                if(!node->containsKey(x)) node->put(x, new TrieNode());
                node = node->get(x);
            }
            node->setEnd();
        }
        
        bool search(string word) {
            return dfs(word, root, 0);
        }
    };
    
    /**
     * Your WordDictionary object will be instantiated and called as such:
     * WordDictionary* obj = new WordDictionary();
     * obj->addWord(word);
     * bool param_2 = obj->search(word);
     */