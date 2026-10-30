//https://leetcode.com/problems/minimum-depth-of-binary-tree/
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode()
      :
      val(0),
      left(nullptr),
      right(nullptr) {
  }
  TreeNode(int x)
      :
      val(x),
      left(nullptr),
      right(nullptr) {
  }
  TreeNode(int x, TreeNode *l, TreeNode *r)
      :
      val(x),
      left(l),
      right(r) {
  }
};

class Solution {
 public:
  int minDepth(TreeNode *root) {
    if (root == nullptr)
      return 0;
    return iterativeDeepeningDFS(root);
  }
  int iterativeDeepeningDFS(TreeNode *root) {
    int thisDepth = 1;
    bool foundMin = false;
    while (true) {
      foundMin = depthLimitedSearch(root, thisDepth);
      if (foundMin) {
        return thisDepth;
      } else {
        thisDepth++;
      }
    }
  }
  bool depthLimitedSearch(TreeNode *root, int depth) {
    bool left = false;
    bool right = false;
    if (depth > 0) {
      if (root->left == nullptr && root->right == nullptr) {
        return true;
      }
      if (root->left != nullptr) {
        left = depthLimitedSearch(root->left, depth - 1);
      }
      if (root->right != nullptr) {
        right = depthLimitedSearch(root->right, depth - 1);
      }
      return left || right;
    } else {
      return false;
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  queue<pair<TreeNode *, int>> nodes;
  vector<TreeNode *> gc;
  int i;
  TreeNode * root = nullptr;
  rep(i, 0, n){
    int val;
    cin >> val;
    TreeNode * node = nullptr;
    if(val!=-1){
      node = new TreeNode(val);
      gc.push_back(node);
    }
    if(nodes.empty()){
      root = node;
      nodes.push({node, 0});
    }else{
      TreeNode * parent;
      int index;
      tie(parent, index) = nodes.front();
      if (index==0){
        if(parent!=nullptr)
          parent->left = node;
        ++index;
        nodes.push({node, 0});
      }else if(index==1){
        if(parent!=nullptr)
          parent->right = node;
        ++index;
        nodes.push({node, 0});
      }
      if(index>1){
        nodes.pop();
      }
    }
  }
  cout << Solution().minDepth(root) << endl;
  for(TreeNode * node: gc){
    delete node;
  }
  return 0;
}
