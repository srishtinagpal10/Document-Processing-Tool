// Do NOT add any other includes
#include "dict.h"
vector <string> sentence_breaker (string sentence);
unsigned long hash_function(const std::string& str);
string to_lower (string word);
Dict::Dict(){
    // Implement your function here
    dict.resize(5381);    
}

Dict::~Dict(){
    // Implement your function here   
    for (int i = 0; i < dict.size(); i++) {
        dict[i].clear();  
    }
    dict.clear();  
}
void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    vector<string> words = sentence_breaker(sentence);

    for (const string& word1 : words) {
        string word;
        word=to_lower(word1);
        unsigned long hashValue = hash_function(word);
        int index = hashValue % dict.size();
        bool wordExists = search(word);
        if (!wordExists) {
            Pair pair;
            pair.id = word;
            pair.word_count = 1;
            dict[index].push_back(pair);
        } else {
           
            for (Pair& pair : dict[index]) {
                if (pair.id == word) {
                    pair.word_count+=1;
                    break;
                }
            }
        }
    } 
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here  
    string word1=to_lower(word);
    unsigned long hashValue = hash_function(word1);  
    int index = hashValue % dict.size();
    for (Pair& pair : dict[index]) {
        if (pair.id == word) {
            return pair.word_count;    
        }
    }
    return -1;
}
void Dict::dump_dictionary(string filename){
    // Implement your function here  
    std::ofstream outFile(filename);

    if (outFile.is_open()) {
        for (const std::vector<Pair>& slot : dict) {
            for (const Pair& pair : slot) {
                outFile << pair.id << ", " << pair.word_count << std::endl;
            }
        }
        outFile.close();
    }
    return;
}
vector <string> sentence_breaker (string sentence){
    vector <string> result;
    int len= sentence.length();
    string word;
    bool inWord = false;
    for(int i=0;i<len;i++){
        if  (sentence[i]!=' ' && sentence[i]!='.'&& sentence[i]!=',' && sentence[i]!='-' && sentence[i]!=':' && 
        sentence[i]!='(' && sentence[i]!=')' && sentence[i]!='?' && sentence[i]!=']' && sentence[i]!='['  && sentence[i]!='\''
        && sentence[i]!=';' && sentence[i]!='@' && sentence[i]!='!' && sentence[i]!='"') {
            word += sentence[i];
            inWord = true;
        } 
        else if (inWord) {
            result.push_back(word);
            word.clear();
            inWord = false;
        }
    }
    if (inWord) {
        result.push_back(word);
    }
    return result;
} 
unsigned long hash_function(const std::string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c); /* hash * 33 + c */
    }
    return hash;
}
bool Dict::search (string word){
    string word1=to_lower(word);
    unsigned long hashValue = hash_function(word1);
    int index = hashValue % dict.size();
    for (Pair& pair : dict[index]) {
        if (pair.id == word) {
            return true;
        }
    }
    return false;
}
string to_lower (string word){
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
