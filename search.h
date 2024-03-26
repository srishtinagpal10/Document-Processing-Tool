// Do NOT add any other includes
#include <string> 
#include <vector>
#include "Node.h"

class DLL {
public:
    Node* DLLroot;
    int count;

    DLL();
    void insert(Node* node);
};

class SearchEngine {
public:
    vector<string> sent;
    vector<Node*> sentnode;

    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
    vector<int> rabin_karp(string const& s, string const& t);
    
};