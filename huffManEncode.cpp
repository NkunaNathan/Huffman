#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;

class TreeNode{
public:
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    char value = '*';
    int frequency = -1;
    /*
    s 11
    a 0100
    l 100
    r 010100
    t 010101
    y 010110
    b 0101110
    e 00
      101
    o 0101111
    h 011
    */
/*
s 11
a 0100
l 100
r 010100
t 010101
y 010110
b 0101110
e 00
  101
o 0101111
h 011
*/

/*
s 11
h 011
e 00
  101
l 100
a 0100
o 0101111
b 0101110
y 010110
t 010101
r 010100
*/
    bool operator<(const TreeNode &other){
        if(frequency < other.frequency){
            return true;
        }else if(frequency > other.frequency){
            return false;
        }else if(value < other.value){
            return true;
        }else {
            return false;
        }
    }

    void preorder(){
        cout << value << "[" << frequency << "] ";
        if(left) left->preorder();
        if(right) right->preorder();
    }


};

class Compare{
public:
    bool operator()(TreeNode* l, TreeNode* r){
        if(l->frequency == r->frequency){
            return l->value > r->value;
        }else
            return l->frequency > r->frequency;
    }
};
TreeNode *merge(TreeNode *t1, TreeNode *t2){
    // Return a new node with t1 and t2 as children
    TreeNode *output = new TreeNode();

    // Fill this out

//    output->value = '\0';
//    output->left->value = tl;
//    output->right =  t2;
    int freqSum = t1->frequency + t2->frequency;
    output->frequency = freqSum;
    output->left = t1;
    output->right = t2;
//    output->frequency = t1->frequency + t1->frequency;
//    cout <<"In merge the value is: " << output->value << "\n";
//    cout <<"In merge the frequency is: " << output->frequency << "\n";
//    cout <<"In merge the left is: " << output->left->frequency << "\n";
//    cout <<"In merge the right is: " << output->right->frequency << "\n";

    return output;
}

TreeNode* getNodes(char v, int freq){
    TreeNode *node =  new TreeNode();
    node->value = v;
    node->frequency = freq;
    return node;
}

void encoding (TreeNode* root, string str ,unordered_map<char, string>&code ){
//    cout << "Starting to Encode...\n";
    if(root == nullptr){
        return;
    }
//    cout << "found a leaf\n";
    if(!root->left  && !root->right){
//        checking to see if the roots are correct
//        cout << "root value: " << root->value <<"\n";
        code[root->value] = str;
    }

//    label the edges on the right with ones
//    if(root->right->operator <(&**root->left))
//    cout << root->right->frequency;
//    cout << "Root value in the recursive call on the right " << root->frequency << endl;
     encoding(root->right, str + "1",code);
    //    label the edges on the left with zeros
//     cout << root->left->frequency;
//     cout << "Root value in the recursive call on the left " << root->left << endl;
     encoding(root->left, str + "0", code);
}

void showpq(priority_queue<TreeNode*, vector<TreeNode*>, Compare> pq){
//    cout << "Starting...\n";
    TreeNode *t = new TreeNode();
    priority_queue<TreeNode*, vector<TreeNode*>, Compare> q = pq;
    priority_queue<TreeNode*, vector<TreeNode*>, Compare> q2 = pq;
    while(!q.empty()){
        t = q.top();
        cout << '\t' << t->frequency;/* << " " << t->value;;*/
//        q.value_type->frequency;


        q.pop();
    }
    cout << "\n";
    while(!q2.empty()){
        t = q2.top();
        cout << '\t' << t->value;;
//        q.value_type->frequency;


        q2.pop();
    }
    cout << "\n";
//    cout << "Finished\n";
}

int main()
{
// This is how to use the tree
    TreeNode *l1 = new TreeNode();
    TreeNode *l2 = new TreeNode();
//###########################################################################
   /* l1->value = 'i';
    l1->frequency = 4;

    l2->value = 'h';
    l2->frequency = 4;

     l1->preorder(); cout << endl;

     if(*l1 < *l2){
         cout << "L1 <  L2" << endl;
     }else{
         cout << "L1 >= L2" << endl;
     }*/
//###########################################################################

    string line = "she sells sea shells by the sea shore";
//            "she sells sea shells by the sea shore";
//    getline(cin, line);
//    cout << "Line " << line << endl;


    // Build frequency table
    int counter(0);

    // this will map each character with it's frequency i guess this is a table if not fuck it.
    unordered_map<char, int> freq;
    for (char ch: line) {freq[ch]++; counter++;}

    // put showpq here delete below

//    freq.empty();
//    for(auto x: freq){

//        if(x.first == ' '){
//            cout << '\t' <<"Space";
//        }else{
//            cout << '\t' << x.first;
//        }
//    }
//    cout << "\n";
//    for(auto x: freq){
//        cout << '\t' << x.second;
//    }
//    cout << endl << counter << endl;
//    // Create the tree


    // Create a priority queue to store live nodes of
    // Huffman tree;
    priority_queue<TreeNode*, vector<TreeNode*>, Compare> pq;
//    showpq(pq);

    for(auto thePair: freq){
//        cout <<"First " << thePair.first << " " << " Second " << thePair.second << "\n";
        pq.push(getNodes(thePair.first, thePair.second));
    }
    // showpq to see what is in the queue and how it is orderd
    showpq(pq);

    while(pq.size() != 1){

        l1 = pq.top();
//        cout << "Top Frequency " << l1->frequency << " Top value " << l1->value<< endl;
//        l1->preorder(); cout << endl;
        pq.pop();

        l2 = pq.top();
//        cout << "Top " << l2->frequency << " Top value " << l2->value << endl;
//        l2->preorder(); cout << endl;
        pq.pop();

        pq.push(merge(l1,l2));
//        cout << pq.size() << endl;
    }
//    showpq(pq); // this is not necessary

//    There is no need to output counter
//    cout << "Counter " << counter << "\n";

    // Encode the string
    unordered_map<char, string> code;
    if(pq.empty()){
        cout << "The queue is empty\n";
        return 0;
    }else{
//        cout <<pq.size() << " " <<  pq.top() << endl;
        TreeNode *root = pq.top(); /*cout << "Root: " <<root->value << "\n";*/ encoding(root, "", code);
    }



//    encoding(root, "", code);
//    int totalEncoding = 0;
//    int bitSize = 8;
//    int another = 0;
//    for(auto n: code){
//        another = 0;
//        cout << n.first << " " << n.second << endl;
////        another = n.second;
////        totalEncoding += bitSize * another;
//    }

    // Output encoding
    int totalEncoding = 0;
//    int bitSize = 8;
    int bitTotal = 0;
    string allCodes = "";
    for (char ch: line) {
//        cout << code[ch].length() << endl;
        bitTotal = code[ch].length();
        allCodes += code[ch];
        totalEncoding +=/* 1 * */bitTotal;
    }
    cout << allCodes << endl;
    cout << "Total Bits (Original): " << (counter * 8) << endl;
    cout << "Total Bits (Coded): " << totalEncoding << endl;

//    decoding



    return 0;
}
//https://www.youtube.com/watch?v=lUUEf0_m_bU


/* to decode
 * Sample Input:
b o r t y a h l e s
1 1 1 1 1 2 4 4 7 7 8
100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000
Total Bits (Original):296
Total Bits (Coded):114
*/
