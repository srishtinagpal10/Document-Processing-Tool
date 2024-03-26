#include "search.h"

string sharp (string word){
    int k=word.length();
    string new_word;
    char c;
    for(int i=0;i<k;i++){
        if(isalpha(word[i])){
            if(isupper(word[i])){
                c=tolower(word[i]); 
                new_word+=c;
            }
            else if(islower(word[i])){
                new_word+=word[i];
            }
        }
        else{
            new_word+=word[i];
        }
    }
    return new_word;
}

DLL::DLL() {
        DLLroot = nullptr;
        count = 0;
    }

void DLL::insert(Node* node) {
        if (DLLroot == nullptr) {
        DLLroot = node;
        return;
    }
    Node* current = DLLroot;
    while (current->right != nullptr) {
        current = current->right;
    }
    current->right = node;
    node->left = current;
    node->right = nullptr;
    count++;
}

SearchEngine::SearchEngine() {
}

SearchEngine::~SearchEngine() {
    sent.clear();
    sentnode.clear();
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence) {
    string newsentence=sharp(sentence);
    sent.push_back(newsentence);
    sentnode.push_back(new Node(book_code,page,paragraph,sentence_no,sent.size()-1));
}

Node* SearchEngine::search(string pattern, int& n_matches) {
    DLL toreturn;
    n_matches = 0;
    int patternsize = pattern.size();
    int sentsize = sent.size();
    const int p = 31; 
    const int m = 1e9 + 9; 
    long long hash = 0;
    long long patternpow = 1;
    for (int i = 0; i < patternsize; i++) {
        hash = (hash * p + (pattern[i] - 'a' + 1)) % m;
        if (i > 0) {
            patternpow = (patternpow * p) % m;
        }
    }
    for (int index = 0; index < sentsize; index++) {
        string sentence = sent[index];
        string sentenceLower = sharp(sentence);
        int sentenceLength = sentenceLower.size();

        for (int i = 0; i <= sentenceLength - patternsize; i++) {
            long long currentHash = 0;

            for (int j = 0; j < patternsize; j++) {
                currentHash = (currentHash * p + (sentenceLower[i + j] - 'a' + 1)) % m;
            }

            if (currentHash == hash && sentenceLower.substr(i, patternsize) == pattern) {
                Node* newNode = new Node(sentnode[index]->book_code, sentnode[index]->page, sentnode[index]->paragraph, sentnode[index]->sentence_no, i);
                toreturn.insert(newNode);
                n_matches++;
            }
        }
    }
    return toreturn.DLLroot;
}
