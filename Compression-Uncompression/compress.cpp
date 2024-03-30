#include "HCTree.hpp"

void compress(const char* input_file, const char* output_file) {
   
    /*STEP 1: Record input_file frequencies for each ascii char*/
    FancyInputStream input(input_file);
    // record frequencies of all ascii character codes in relation to input_file
    // desired format e.g: frequencies[97] = 3 => aaa
    vector<int> frequencies(256, 0); 
    // record size in bytes of input file
    int inSize = input.filesize();
    // if empty file
    if (inSize == 0) {
        FancyOutputStream output(output_file);
        output.flush();
        //cout << "file is empty";
        return;
    }

    //cout << inSize << endl;
    //cout << frequencies.size() << endl;

    for (int i = 0; i < inSize; i++) {
 
        unsigned char ascii_char = (unsigned char)input.read_byte();
        // increment the frequency for each present ascii char inside input_file by 1 
        frequencies[ascii_char]++;
        //cout << ascii_char << ": " << frequencies[ascii_char] <<endl;
    }
    
    /*STEP 2: Build Huffman coding tree with the input_file frequencies*/
    HCTree tree;
    tree.build(frequencies);

    /*STEP 3: Write all frequencies for each ascii into output; this will be our output HEADER*/
    FancyOutputStream output(output_file);
    for (int frequency : frequencies) {
        output.write_int(frequency);
        //cout << frequency << endl;
    }
    

    // Start reading input_file from the beginning again
    input.reset();

    /*STEP 4: Encode input_file and write the encoding into output_file right after the header*/
    for (int i = 0; i < inSize; i++) {
        unsigned char ascii_char = (unsigned char)input.read_byte();
        //cout << ascii_char << endl;
        tree.encode(ascii_char, output);
    }
    output.flush();
}

int mains(char* args[]) {
    const char* infile = "input.txt";
    const char* outfile = "compressed.txt";
    //const char* infile = args[1];
    //const char* outfile = args[2];

    compress(infile, outfile);
    return 0;
}
