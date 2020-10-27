#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
using namespace std;


class TreeNode{
public:
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    char value = '*';
    int frequency = -1;

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

string cleanInput(string input){
    int spaceCount = 0;
    string newString = "";
    for(unsigned i = 0; i < input.size(); i++){
        if(input.at(i) == ' '){
            spaceCount++;
            if(spaceCount > 1){
                newString += input.at(i);
            }
        }else{
            spaceCount = 0;
            newString += input.at(i);
        }
    }
    return newString;
}

// The below cleanIntInput method is not necessary i think
string cleanIntIput(string input){
    int spaceCount = 0;
    string newString = "";
    for(unsigned i = 0; i < input.size(); i++){
        if(input.at(i) == ' '){
            spaceCount++;
            if(spaceCount > 1){
                newString += input.at(i);
            }
        }else{
            spaceCount = 0;
            newString += input.at(i);
        }
    }
    return newString;
}
//still thinking about this if it is necessary
//string toBinary(string huffCo){
//    string binaryValues = "";
//    for(unsigned i = 0; i < huffCo.size(); i++){
//        cout <<  huffCo.at(i) << endl;
////        if (huffCo.at(i)== 49){
////            int v = huffCo.at(i)- 48;
////            binaryValues += v;
////        }else{
////            int v = huffCo.at(i) - 48;
////            binaryValues += v;
////        }
//    }
//    return binaryValues;
//}


class Compare{
public:
    bool operator()(TreeNode* l, TreeNode* r){
        if((int)l->frequency == (int)r->frequency){
            return l->value > r->value;
        }else
            return l->frequency > r->frequency;
    }
};
TreeNode *merge(TreeNode *t1, TreeNode *t2){
    // Return a new node with t1 and t2 as children
    TreeNode *output = new TreeNode();
    // Fill this out
//    cout << "Sum of the frequency " << t1->frequency + t2->frequency << endl;
    int freqSum = t1->frequency + t2->frequency;
    output->frequency = freqSum;
    output->left = t1;
    output->right = t2;
    return output;
}

TreeNode* getNodes(char v, int freq){
    TreeNode *node =  new TreeNode();
    node->value = v;
    node->frequency = freq;
    return node;
}

// showpq is no longer needed
void showpq(priority_queue<TreeNode*, vector<TreeNode*>, Compare> pq){
    TreeNode *t = new TreeNode();
    priority_queue<TreeNode*, vector<TreeNode*>, Compare> q = pq;
    priority_queue<TreeNode*, vector<TreeNode*>, Compare> q2 = pq;
    while(!q.empty()){
        t = q.top();
        cout << '\t' << t->value;/* << " " << t->value;;*/
        q.pop();
    }
    cout << "\n";
    while(!q2.empty()){
        t = q2.top();
        cout << '\t' << t->frequency;;
//        q.value_type->frequency;


        q2.pop();
    }
    cout << "\n";
}

void decode(TreeNode* root, int &index, string str)
{
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (!root->left && !root->right)
    {
        cout << root->value;
        return;
    }

    index++;

    if (str[index] =='0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}


int main(/*int argc, char *argv[]*/)
{
    vector<char> charVector;
    vector<int> freqVeector;
    // This is how to use the tree
    TreeNode *l1 = new TreeNode();
    TreeNode *l2 = new TreeNode();

//    QCoreApplication a(argc, argv);
//    store inputs
    //the below line need to be in while loop that will loop 3 times taking and input and
    // storing it for later processing or there must be a smarte way to process the 3 inputs
    // when you have found it just comment this lines to not remove them but remove this line
    string characters = "b o r t y a h l  e s";
    string num = "1 1 1 1 1 2 4 4 7 7 8";
    string asciiValues = "100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000";
//    string binary = toBinary(asciiValues);
    unordered_map<char,int> aPair;
    string newString = cleanInput(characters);
    string numString = cleanInput(num);

//    for(unsigned int j = 0; j < numString.size(); j++){
//        cout <<numString.at(j)<< "\n";
//    }

    pair<char,int>charFreqPair;
    for(unsigned int k = 0; k < newString.size(); k++){
        charFreqPair.first = newString.at(k);
        charFreqPair.second =  numString.at(k) - '0';
        aPair.emplace(charFreqPair);
    }


//    we are finished here we can see that we have paired up really nicely

//    for(auto pa: aPair){
//        cout << pa.first << " " << pa.second <<endl;
//    }
     priority_queue<TreeNode*, vector<TreeNode*>, Compare> pq;
     for(auto thePair: aPair){
         pq.push(getNodes(thePair.first, thePair.second));
     }
//     showpq(pq);

     while(pq.size() != 1){

         l1 = pq.top();
         pq.pop();

         l2 = pq.top();
         pq.pop();

         pq.push(merge(l1,l2));
     }

     // This is no longer neccessary as we only have to print out the decoded string
//     cout << "print" << endl;
//     for(unsigned x = 0; x < binary.size(); x++){
//         cout << '\t' << binary.at(x);
//     }
     // This is no longer neccessary as we only have to print out the decoded string
//     for(unsigned v = 0; v < asciiValues.size(); v++){
//         cout << asciiValues.at(v);
//     }

     if(pq.empty()){
         cout << "The queue is empty\n";
         return 0;
     }else{
 //        cout <<pq.size() << " " <<  pq.top() << endl;
         TreeNode *root = pq.top(); /*cout << endl << "Root: " <<root->value << "\n"*/;
//         get the index position
         int position = -1;
         while (position < (int)asciiValues.size()-1) {
//             cout << "Index: " << index << "\n";
             decode(root, position, asciiValues);
         }
     }
     cout << endl;
    return 0;
}


// we are only taking the first 3 lines and ignore the rest

/* to decode
 * Sample Input:
b o r t y a h l e s
1 1 1 1 1 2 4 4 7 7 8
100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000
Total Bits (Original):296
Total Bits (Coded):114
*/
