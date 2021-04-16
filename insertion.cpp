#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Node {
    T key;
    int priority, size;
    Node *left, *right;

    Node(const T& _key): key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}

    void setLeft(Node* node) {
        left = node;
        calcSize();
    }

    void setRight(Node* node) {
        right= node;
        calcSize();
    }

    void calcSize() {
        size = 1;
        if(left) size += left->size;
        if(right) size += right->size;
    }
};

template <typename T>
using NodePair = pair<Node<T>*, Node<T>*>;

template <typename T>
NodePair<T> split(Node<T>* root, T k) {
    if(root==NULL) return NodePair<T>(NULL, NULL);
    if(root->key>k) {
        NodePair<T> ls = split(root->left, k);
        root->setLeft(ls.second);
        return NodePair<T>(ls.first, root);
    } else {
        NodePair<T> rs = split(root->right, k);
        root->setRight(rs.first);
        return NodePair<T>(root, rs.second);
    }
}

template <typename  T>
Node<T>* insert(Node<T>* root, Node<T>* node) {
    if(root==NULL) return node;
    if(node->priority>root->priority) {
        NodePair<T> sp = split(root, node->key);
        node->setLeft(sp.first);
        node->setRight(sp.second);
        return node;
    } else {
        if(root->key>node->key) {
            Node<T>* left = insert(root->left, node);
            root->setLeft(left);
        } else {
            Node<T>* right = insert(root->right, node);
            root->setRight(right);
        }
        return root;
    }
}

template <typename T>
Node<T>* merge(Node<T>* a, Node<T>* b) {
    if(a==NULL) return b;
    if(b==NULL) return a;
    if(a->priority>b->priority) {
        a->setRight(merge(a->right, b));
        return a;
    } else {
        b->setLeft(merge(a, b->left));
        return b;
    }
}

template <typename  T>
Node<T>* erase(Node<T>* root, T k) {
    if(root==NULL) return NULL;
    if(root->key==k) {
        Node<T>* newNode = merge(root->left, root->right);
        delete root;
        return newNode;
    } else if(root->key>k) {
        root->setLeft(erase(root->left, k));
        return root;
    } else {
        root->setRight(erase(root->right, k));
        return root;
    }
}

template <typename T>
Node<T>* kth(Node<T>* root, int k) {
    int l = 0;
    if(root->left!=NULL) l = root->left->size;
    if(k==l+1) {
        return root;
    } else if(k<=l) {
        return kth(root->left, k);
    } else {
        return kth(root->right, k-l-1);
    }
}

template <typename T>
int countLessThan(Node<T>* root, int a) {
    if(root==NULL) return 0;
    if(root->key>=a) {
        return countLessThan(root->left, a);
    } else {
        int ls = (root->left ? root->left->size : 0);
        return ls+1+countLessThan(root->right, a);
    }
}


int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        int n;
        cin >> n;
        Node<int>* root = NULL;
        vector<int> input;
        vector<int> ans;
        for(int i=0;i<n;i++){
            Node<int>* node = new Node<int>(i+1);
            root = insert(root, node);
            int num;
            cin >> num;
            input.push_back(num);
        }
        for(auto it=input.rbegin();it!=input.rend();it++){
            int k = root->size - *it;
            Node<int>* node = kth(root, k);
            ans.push_back(node->key);
            root = erase(root, node->key);
        }
        for(auto it=ans.rbegin();it!=ans.rend();it++) {
            cout << *it << " ";
        }
        cout << "\n";
        t--;
    }
}
