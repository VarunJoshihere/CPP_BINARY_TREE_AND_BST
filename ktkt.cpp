#include <bits/stdc++.h>
#include <climits>
using namespace std;
class Node{
    public:
    Node*left;
    Node*right;
    int data;
    Node(int d){
        data=d;
        right=NULL;
        left=NULL;
    }
};
class Pair{
public:
    int height;
    bool balance;
};
int getheight(Node*root){
    if(root==NULL){
        return 0;
    }
    int h1=getheight(root->left);
    int h2=getheight(root->right);
    return max(h1,h2)+1;
}
Node* buildTree(){
    int d;
    cin>>d;
    if(d==-1){
        return NULL;
    }
    Node*root=new Node(d);
    root->left=buildTree();
    root->right=buildTree();
    return root;
}
void bfs(Node*root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node*temp=q.front();
        if(temp==NULL){
            cout<<endl;
            q.pop();
            if(!q.empty()){
            q.push(NULL);}
        }
        else{
        cout<<temp->data<<" ";
        if(temp->left){
            q.push(temp->left);
        }
        if(temp->right){
            q.push(temp->right);
        }
        q.pop();}
    }
}
int diameter(Node*root){
if(root==NULL){
    return 0;
}
int h1=getheight(root->left);
int h2=getheight(root->right);
int op1=h1+h2+1;
int op2=diameter(root->left);
int op3=diameter(root->right);
return max(op1,max(op2,op3));

}
int replaceSum(Node*root){
    if(root==NULL){
        return 0;
    }
    if(root->left==NULL && root->right==NULL){
        return root->data;
    }
    //Recursive Part
    int leftSum = replaceSum(root->left);
    int rightSum = replaceSum(root->right);

    int temp = root->data;
    root->data = leftSum + rightSum;
    return temp + root->data;
}
Pair isBalance(Node*root){
   Pair p;
    if(root==NULL){
        p.height = 0;
        p.balance = true;
        return p;
    }
    //Recurisve Case
    Pair left = isBalance(root->left);
    Pair right = isBalance(root->right);

    p.height = max(left.height,right.height) + 1;

    if(abs(left.height-right.height)<=1 && left.balance && right.balance){
        p.balance = true;
    }
    else{
        p.balance = false;
    }
    return p;


}
Node*buildBalancedTreeFromArr(int *arr,int s,int e){
    if(s>e){
        return NULL;
    }
    int mid=(s+e)/2;
    Node*root=new Node(arr[mid]);
    root->left=buildBalancedTreeFromArr(arr,s,mid-1);
    root->right=buildBalancedTreeFromArr(arr,mid+1,e);
    return root;
    
}
Node*buildTreeFromTrav(int *in,int *pre,int s,int e){
    //issues
  static int i = 0;
    //Base Case
    if(s>e){
        return NULL;
    }
    //Rec Case
    Node *root = new Node(pre[i]);

    int index=-1;
    for(int j=s;s<=e;j++){
        if(in[j]==pre[i]){
            index = j;
            break;
        }
    }

    i++;
    root->left = buildTreeFromTrav(in,pre,s,index-1);
    root->right = buildTreeFromTrav(in,pre,index+1,e);
    return root;
}
void printklevel(Node*root,int level){
    if(root==NULL){
        return;
    }
    if(level==1){
        cout<<root->data<<" ";
    }
 
    printklevel(root->left,level-1);
    printklevel(root->right,level-1);
}
void levelorderprint(Node*root){
    int height=getheight(root);
    for(int i=0;i<=height;i++){
        printklevel(root,i);
        cout<<endl;
    }
}
void rightview(Node*root,int level,int &maxlevel){
    if(root==NULL){
        return;
    }
    if(maxlevel<level){
        cout<<root->data<<endl;
        maxlevel=level;
    }
    rightview(root->right,level+1,maxlevel);
    rightview(root->left,level+1,maxlevel);
    
}
Node*LowestCommonAncestor(Node*root,int a,int b){
    if(root==NULL){
        return NULL;
    }
    if(root->data==a||root->data==b){
return root;
    }
    Node*leftans=LowestCommonAncestor(root->left,a,b);
    Node*rightans=LowestCommonAncestor(root->right,a,b);
    if(leftans&&rightans){
        return root;
    }
    if(leftans&&rightans==NULL){
        return leftans;
    }
    return rightans;
}
void inorder(Node*root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}
Node* insertInBST(Node *root,int data){
    //Base Case
    if(root==NULL){
        return new Node(data);
    }
    //Rec Case - Insert in the Subtree and Update Pointers
    if(data<=root->data){
        root->left = insertInBST(root->left,data);
    }
    else{
        root->right = insertInBST(root->right,data);
    }
    return root;
}

Node* buildbst(){
    //Read a list of numbers till -1 and also these numbers will be inserted into BST
    int d;
    cin>>d;

    Node*root = NULL;

    while(d!=-1){
        root = insertInBST(root,d);
        cin>>d;
    }
    return root;
}
bool search(Node*root,int key){
    if(root==NULL){
        return false;
    }
    if(key==root->data){
        return true;
    }
    if(key<root->data){
        return search(root->left,key);
    }
    if(key>root->data){
        return search(root->right,key);
    }
    return false;
}
// bool isbst(Node*root){
    
// }
Node*deleteinbst(Node*root,int k){
    if(root==NULL){
        return NULL;
    }
    if(root->data>k){
        root->left=deleteinbst(root->left,k);
    }
    if(root->data==k){
        //with zero children
        if(root->left==NULL&&root->right==NULL){
            delete root;
            return NULL;
        }
        //with one child
        if(root->left!=NULL&&root->right==NULL){
            Node*temp=root->left;
            delete root;
            return temp;
        }
        if(root->right!=NULL&&root->left==NULL){
            Node*temp=root->right;
            delete root;
            return temp;
        }
        //with two children
        if(root->left!=NULL&&root->right!=NULL){
            Node*replace=root->right;
            while(replace->left!=NULL){
                replace=replace->left;
            }
            root->data=replace->data;
            root->right=deleteinbst(root->right,replace->data);
        }
        else{
            root->right=deleteinbst(root->right,k);
        }






    }
    return root;
}

class LinkedList{
    public:
        Node*head;
        Node*tail;
};

LinkedList flatten(Node*root){
    LinkedList l;

    if(root==NULL){
        l.head = l.tail = NULL;
        return l;
    }
    // Leaf Node
    if(root->left == NULL && root->right==NULL){
        l.head = l.tail = root;
        return l;
    }
    // Left is Not NULL
    if(root->left!=NULL && root->right==NULL){
        LinkedList leftLL = flatten(root->left);
        leftLL.tail->right = root;

        l.head = leftLL.head;
        l.tail = root;
        return l;
    }
    //Right is Not NULL
    if(root->left==NULL && root->right!=NULL){
        LinkedList rightLL = flatten(root->right);
        root->right = rightLL.head;

        l.head = root;
        l.tail  = rightLL.tail;
        return l;
    }
    //Both Sides are not NULL
    LinkedList leftLL = flatten(root->left);
    LinkedList rightLL = flatten(root->right);

    leftLL.tail->right = root;
    root->right = rightLL.head;

    l.head = leftLL.head;
    l.tail = rightLL.tail;
    return l;

}
bool isBST(Node *root,int minV = INT_MIN,int maxV = INT_MAX){
    if(root==NULL){
        return true;
    }
    if(root->data >= minV && root->data<=maxV && isBST(root->left,minV,root->data) && isBST(root->right,root->data,maxV)){
        return true;
    }
    return false;
}
int main()
{
    // Node*root=buildTree();
    // bfs(root);
    // cout<<"HEIGHT IS : "<<getheight(root)<<endl;
    // cout<<"THE DIAMETER IS : "<< diameter(root)<<endl;
    // replaceSum(root);
    // bfs(root);
    // Pair op=  isBalance(root);
    // if(op.balance){
    //     cout<<"THE TREE IS BALANCED"<<endl;
    // }
    // else{
    //     cout<<"NOT BALANCED"<<endl;
    // }
    // int a[]={1,2,3,4,5,6,7};
    // int n=7;
    // Node*temp=buildBalancedTreeFromArr(a,0,n-1);
    // bfs(temp);
    // int pre[]={1,2,3,4,8,5,6,7};
    // int ino[]={3,2,8,4,1,6,7,5};
    // Node*neww=buildTreeFromTrav(ino,pre,0,7);
    
    // bfs(neww);
    // cout<<"NOW FOR RIGHT VIEW"<<endl;
    // int maxlevel=-1;
// cout<<"bfs"<<endl;
// bfs(neww);
    // rightview(neww,0,maxlevel);
    // cout<<"LEVELORDER";
    // levelorderprint(neww);
    
    // int a=4;
    
    // int b=3;
    // Node*ans=LowestCommonAncestor(root,a,b);
    // cout<<"Lowest Common Ancestor is THE NODE IS WITH VALUE "<<root->data<<endl;
    Node*bst=buildbst();
    bfs(bst);
    inorder(bst);
    cout<<endl;
    
    // int val=1;
    // Node*withinsertion=insertInBST(bst,val);
    // bfs(withinsertion);
    // inorder(withinsertion);
    // cout<<endl;
    // if(search(bst,val)){
    //     cout<<"THE VALUE "<<val<<" IS PRESENT IN THE TREE"<<endl;
    // }

    if(isBST(bst)){
        cout<<"THE CHECKED TREE IS A BST"<<endl;
    }
    Node*afterdelete=deleteinbst(bst,4);
    // cout<<"AFTER DELETE"<<endl;
    // bfs(afterdelete);
    // inorder(afterdelete);
    // cout<<endl;
    // LinkedList node=flatten(afterdelete);
    // cout<<"AFTER FLATTEN"<<endl;
    // Node*neww=node.head;
    // while(neww!=NULL){
    //     cout<<neww->data<<" ";
    //     neww=neww->right;
    // }
    // cout<<endl;
    


    

    

    return 0;
}
