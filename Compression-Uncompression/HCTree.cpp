#include "HCTree.hpp"

HCTree::~HCTree() {
    delete_tree(root);
    root = nullptr;
}

void HCTree::delete_tree(HCNode* hctNode) {
    if (hctNode == nullptr)
        return;
    delete_tree(hctNode->c0);
    delete_tree(hctNode->c1);
    delete hctNode;
    hctNode = nullptr;
}

void HCTree::build(const vector<int>& freqs) {
    // used to record
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> p_queue;

    // generate leaf nodes from freqs vector of frequencies
    for (int i = 0; i < freqs.size(); i++) {
        // only build non-zero frequencies ascii chars, ignore the rest
        if (freqs[i] > 0) {
            leaves[i] = new HCNode(freqs[i], (unsigned char)i);
            p_queue.push(leaves[i]);
        }
    }

    // generate Huffman until root is left in p_queue
    while (p_queue.size() > 1) {
        // create left child
        HCNode* c0 = p_queue.top(); // lowest current frequency
        p_queue.pop();
        // create right child
        HCNode* c1 = p_queue.top(); // second lowest current frequency
        p_queue.pop();

        // parent is left child + right child by design, but not an ascii
        HCNode* parent = new HCNode(c0->count + c1->count, 0);
        // left child intialization
        parent->c0 = c0;
        // right child intialization
        parent->c1 = c1;
        // set the children their parent node
        c0->p = parent;
        c1->p = parent;

        // has to be in p_queue since it can be a child of some parent
        p_queue.push(parent);
    }

    // top of the queue has to be the root by design if huffman was created
    if (!p_queue.empty()) 
        root = p_queue.top();
    
    // debugging stuff
    printTreeHelper(root, "");
}

void HCTree::encode(unsigned char symbol, FancyOutputStream& out) const {
    if (root == nullptr || symbol >= leaves.size() || leaves[symbol] == nullptr) {
        error("Invalid symbol/Tree Creatinion Flaw");
    }

    HCNode* node = leaves[symbol];
    vector<int> bits;

    // record bits into bits vector
    while (node->p != nullptr) {
        if (node->p->c0 == node) 
            bits.push_back(0);
        else 
            bits.push_back(1);
        node = node->p;
    }

    // write the encoding for the given ascii char into out
    for (int i = bits.size() - 1; i >= 0; --i) {
        out.write_bit(bits[i]);
        //cout << bits[i];
    }
    //cout << '\n';
}
unsigned char HCTree::decode(FancyInputStream& in , int& reduce) const {
    
    if (root == nullptr) 
        error("No Huffman tree found error");
    
    HCNode* node = root;
    int bit;
    while (node->c0 != nullptr && node->c1 != nullptr) {
        bit = in.read_bit();
        //cout << bit;
        if (bit == -1) 
            error("bit reading error");
        
        if (bit == 0)
            node = node->c0;
        else
            node = node->c1;
        // record visited bit by adding 1 to reduce
        reduce++;

        if (node == nullptr) 
            error("Huffman tree is not valid error");
        
    }
    //cout << "\n";
    return node->symbol;
}

void HCTree::printTreeHelper(HCNode* node, string code)
{
    if (node == nullptr) {
        return;
    }
    // cout leaf node ascii and corresponding Huffman code
    if (node->c0 == nullptr && node->c1 == nullptr) {
        cout << "Character: " << (int)node->symbol << " Code: " << code << endl;
        //bits += code.size();
        //cout << myMap[(int)node->symbol] << endl;
        
        // record number of bits used in our encoding
        // bits = bits + (bit_length * char_frequency)
        bits = bits + (code.size() * ascii_Map[(int)node->symbol]);
        return;
    }

    // print huffman bits from left and right subtrees
    printTreeHelper(node->c0, code + "0");
    printTreeHelper(node->c1, code + "1");
}
