#include<iostream>
#include<stack>
using namespace std;

class TreeNode{
    public:
       int val;
       TreeNode* left;
       TreeNode* right;
       TreeNode(int value):val(value),left(NULL),right(NULL){}
};
class BinaysearchTree{
    public:
       int root;

       BinaysearchTree():root(NULL){}

       void insert(int key){root = insertRec(root,key);}

       void preorder(){
        if(root==NULL) return;
        stack<TreeNode* >s;
        s.push(root);
        while(!s.empty()){
            TreeNode* curr = s.top();
            s.pop();
            cout<<curr->val<< " ";
            if(curr->right)s.push(curr->right);
            if(curr->left)s.push(curr->left);
        }
        cout<<endl;
       }
       void postorder(){
        if(root==NULL) return;
        stack<TreeNode*> s1,s2;
        s1.push(root);
        while(!s1.empty()){
            TreeNode* curr= s1.top();
            s1.pop();
            s2.push(curr);
            if(curr->left) s1.push(curr->left);
            if(curr->right) s1.push(curr->right);
        }
        while(!s2.empty()){
            cout<<s2.top()->val<<" ";
            s2.pop();
        }
        cout<<endl;
       }

       private:
          TreeNode* insertRec(TreeNode* node, int key){
            if(node==NULL)return new TreeNode(key);
            if(key<node->val) node->left=insertRec(node->left,key);
            if(key>node->val) node->right=insertRec(node->right,key);
            return node;
          }
};
int main(){
    BinaysearchTree bst;
    int keys[]={50,30,20,40,70,60,80};
    for(int i=0;i<7;i++){
        bst.insert(keys[i]);
    }

    cout<<"Preorder: ";
    bst.preorder();
    cout<<"Postorder: ";
    bst.postorder();
}