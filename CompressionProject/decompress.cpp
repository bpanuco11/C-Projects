#include "HCTree.hpp"

void decompress(const char* input_file, const char* output_file) {

    FancyInputStream input(input_file);

    int inSize = input.filesize();
    // if empty file
    if (inSize == 0) {
        ofstream output(output_file, ios::binary);
        output.flush();
        cout << "file is empty";
        return;
    }
    //cout << fileSize << endl;
    vector<int> frequencies(256, 0);
    HCTree tree;

    // read all ascii frequencies and store to create Huffman tree
    for (int i = 0; i < 256; i++) {

        frequencies[i] = input.read_int();
        if (frequencies[i] != 0) 
            //cout << frequencies[i] << ": " << i << endl;
            tree.ascii_Map[i] = frequencies[i];
    }

    // make huffman tree from frequencies inside compressed file
    tree.build(frequencies);
    
    ofstream output(output_file, ios::binary);
    int remainingSymbols = inSize - 1024; // calculate remaining bytes by deleting header

    // trailing zeroes:
    //cout << tree.bits << " bits!" << endl;
    //remainingSymbols = (remainingSymbols * 8) -6 ; //-treebits
    remainingSymbols = tree.bits;
    //cout << remainingSymbols << endl;
    int reduceC = 0;

    // loop until there are no more huffman tree bits left to read AND ignore trailing zeroes
    while (remainingSymbols > 0) {
        unsigned char symbol = tree.decode(input, reduceC);
        output.put(symbol);
        remainingSymbols -= reduceC;
        reduceC = 0;
    }

    output.flush();
}


int mains(char* args[]) {
    const char* infile = "compressed.txt"; 
    const char* outfile = "decompressed.txt";
    //const char* infile = args[1];
    //const char* outfile = args[2];

    decompress(infile, outfile);
    return 0;
}
