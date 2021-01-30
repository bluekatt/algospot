#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <list>
#include <stack>
#include <map>

using namespace std;

struct TreeNode {
    TreeNode(int _x, int _y, int _r) {
        x = _x; y = _y; r = _r;
    }
    int x, y, r;
    vector<TreeNode*> children;
};

void putNewFort(TreeNode* root, TreeNode* newNode) {
    bool put = false;
    for(auto it=root->children.begin(); it!=root->children.end(); it++) {
        TreeNode* child = *it;
        int cr = child->r, cx = child->x, cy = child->y;
        int nr = newNode->r, nx = newNode->x, ny = newNode->y;
        if((cr-nr)*(cr-nr)>(cx-nx)*(cx-nx)+(cy-ny)*(cy-ny)) {
            if(cr>nr){
                putNewFort(child, newNode);
            }else{
                newNode->children.push_back(*it);
                root->children.erase(it);
                root->children.push_back(newNode);
            }
            put = true;
        }
    }
    if(!put){
        root->children.push_back(newNode);
    }
}

int longest = 0;

int height(TreeNode* root) {
    if(root->children.empty()){
        return 0;
    }
    vector<int> heights;
    for(auto child: root->children){
        heights.push_back(height(child));
    }
    sort(heights.begin(), heights.end());
    int s = heights.size();
    if(s>=2){
        longest = max(longest, 2+heights[s-1]+heights[s-2]);
    }
    return heights.back()+1;
}

int crossWall(TreeNode* root){
    longest = 0;
    int h = height(root);
    return max(h, longest);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        int n;
        cin >> n;
        int x, y, r;
        cin >> x >> y >> r;
        TreeNode root = TreeNode(x, y, r);
        for(int i=1;i<n;i++){
            cin >> x >> y >> r;
            TreeNode* newNode = new TreeNode(x, y, r);
            putNewFort(&root, newNode);
        }
        cout << crossWall(&root) << "\n";
        t--;
    }
}

