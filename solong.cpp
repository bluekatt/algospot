#include <bits/stdc++.h>

#include <utility>

using namespace std;

const int ALPHABET = 26;

struct TrieNode {
    TrieNode* children[ALPHABET];
    int terminal;
    int first;

    TrieNode(): terminal(-1), first(-1) {
        memset(children, 0, sizeof(children));
    }

    ~TrieNode() {
        for(int i=0;i<ALPHABET;i++)
            if(children[i])
                delete children[i];
    }

    void insert(const char* key, int id) {
        if(first==-1) first = id;
        if(*key==0) {
            terminal = id;
        } else {
            int next = (*key) - 'A';
            if(children[next]==NULL) children[next] = new TrieNode();
            children[next]->insert(key+1, id);
        }
    }

    TrieNode* find(const char* key) {
        if(*key==0) return this;
        int next = (*key) - 'A';
        if(children[next]==NULL) return NULL;
        return children[next]->find(key+1);
    }

    int recommend(const char* key, int id) {
        if(*key==0) return 0;
        if(first==id) return 1;
        int next = (*key) - 'A';
        return 1 + children[next]->recommend(key+1, id);
    }
};

int countKeys(TrieNode* node, const char* key) {
    TrieNode* tar = node->find(key);

    if(tar==NULL || tar->terminal==-1) return strlen(key);

    return node->recommend(key, tar->terminal);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        TrieNode* root = new TrieNode();
        int n, m;
        cin >> n >> m;
        vector<pair<int, string> > inputs;
        for(int i=0;i<n;i++) {
            string word;
            int freq;
            cin >> word >> freq;
            inputs.push_back(make_pair(-freq, word));
        }
        sort(inputs.begin(), inputs.end());
        for(int i=0;i<n;i++) {
            root->insert(inputs[i].second.c_str(), i);
        }
        root->first = -1;
        int typed = 0;
        for(int i=0;i<m;i++) {
            string input;
            cin >> input;
            typed += countKeys(root, input.c_str());
        }
        typed += m-1;
        cout << typed << "\n";
    }
}
