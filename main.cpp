#include <iostream>

using namespace std;

struct Point{
    int x, y;
    void print_point(){
        cout << "(" << x << ", " << y << ")";
    }
};

struct Pair{
    int key;
    Point value;
    Pair *next, *prev;
    void print_pair(){
        cout << "{" << key << ": " ; value.print_point(); cout << "} ";
    }
};

struct List{

    Pair *beginning;
    Pair *end;

    List(){
        beginning = end = nullptr;
    }

    void add_pair(const int _key, const Point _value){
        Pair *pair = new Pair;
        pair->key = _key;
        pair->value = _value;
        if (beginning != nullptr) {
                pair->prev = end;
                end->next = pair;
                pair->next = nullptr;
                end = pair;
        }else {
            pair->prev = nullptr;
            beginning = end = pair;
        }
    }

    Pair* search_pair(const int s_key) {
        Pair *ptr = beginning;
        while (ptr) {
            if (ptr->key == s_key)
                return ptr;
            ptr = ptr->next;
        }
        cerr << "Key error!";
    }

    void delete_pair(int d_key) {
        Pair *d_pair = search_pair(d_key);
        if (d_pair != beginning and d_pair != end) {
            d_pair->next->prev = d_pair->prev;
            d_pair->prev->next = d_pair->next;
        } else if (d_pair == end) {
            end = d_pair->prev;
            end->next = nullptr;
        } else if (d_pair == beginning) {
            beginning = d_pair->next;
            beginning->prev = nullptr;
        }
        delete d_pair;
    }

    void print_list(){
        Pair *temp = beginning;
        while(temp != nullptr){
            temp->print_pair();
            temp = temp->next;
        }
        cout << endl;
    }
};

int trivial_hash(int key){
    return key%10;
}

struct hash_List{
    List *keys = new List [10];

    void add(int key, Point value){
        int hs = trivial_hash(key);
        keys[hs].add_pair(key, value);
    }

    Pair *search(int key){
        int hs = trivial_hash(key);
        return keys[hs].search_pair(key);
    }

    void del(int key){
        int hs = trivial_hash(key);
        keys[hs].delete_pair(key);
    }
};


int main() {
    hash_List new_table;
    for(int i = 0; i < 20; i++){
        new_table.add(i, {i+1, i+2});
    }
    for(int i = 0; i < 10; i++){
        new_table.keys[i].print_list();
    }
    cout << endl;
    new_table.del(10);
    new_table.keys[0].print_list();
    cout << endl;
    Pair *s_pair = new_table.search(15);
    s_pair->print_pair();
    return 0;
}