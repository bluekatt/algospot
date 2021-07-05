#include <bits/stdc++.h>

using namespace std;

const int ALPHABET = 26;

struct TrieNode {
    TrieNode* children[ALPHABET];
    int frequency;
    TrieNode* recommendation;

    TrieNode(): frequency(-1), recommendation(NULL) {
        memset(children, 0, sizeof(children));
    }

    ~TrieNode() {
        for(int i=0;i<ALPHABET;i++)
            if(children[i])
                delete children[i];
    }

    void insert(const char* key, const int freq) {
        if(*key==0) {
            frequency = freq;
        } else {
            int next = (*key) - 'A';
            if(children[next]==NULL) children[next] = new TrieNode();
            children[next]->insert(key+1, freq);
        }
    }

    TrieNode* find(const char* key) {
        if(*key==0) return this;
        int next = (*key) - 'A';
        if(children[next]==NULL) return NULL;
        return children[next]->find(key+1);
    }

    TrieNode* recommend() {
        if(recommendation!=NULL) return recommendation;
        TrieNode* ret = NULL;
        if(frequency!=-1) ret = this;
        for(int i=0;i<ALPHABET;i++) {
            if(children[i]) {
                TrieNode* recommended = children[i]->recommend();
                if(recommended == NULL) continue;
                if(ret==NULL) ret = recommended;
                if(recommended->frequency > ret->frequency) {
                    ret = recommended;
                }
            }
        }
        return (recommendation = ret);
    }
};

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        TrieNode* root = new TrieNode();
        int n, m;
        cin >> n >> m;
        for(int i=0;i<n;i++) {
            string word;
            int freq;
            cin >> word >> freq;
            root->insert(word.c_str(), freq);
        }
        string input[20000];
        for(int i=0;i<m;i++) {
            cin >> input[i];
        }
        int typed = m-1;
        for(int i=0;i<m;i++) {
            TrieNode* tar = root->find(input[i].c_str());
            int size = input[i].size();
            char str[12];
            bool succeed = false;
            for(int j=0;j<size-1;j++) {
                typed++;
                str[j] = input[i].at(j); str[j+1] = 0;
                TrieNode* found = root->find(str);
                if(found==NULL) continue;
                TrieNode* rec = found->recommend();
                if(rec == tar) {
                    succeed = true;
                    typed++;
                    break;
                }
            }
            if(!succeed) typed++;
        }
        cout << typed << "\n";
    }
}
