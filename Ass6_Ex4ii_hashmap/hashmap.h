//
//  hashmap.h
//  
//
//  Created by KD on 6.03.21.
//  Modified on 22.03.22
//

#ifndef hashmap_h
#define hashmap_h

template<class K, class T> class hashmap
{
public:
    hashmap(int size = 20);
    T &operator[](int index);
// The operation add inserts
// an element into the hashmap,
// remove deletes an
// element and member checks,
// if the element is in the hashmap
    void add(K key, T item);
    void remove(K key);
    T retrieve(K key);
    bool member(K key, T item);
// The function display is only used
// for testing purposes.
// It shows the size of
// the hashmap, the number of elements,
// and displays all entries
    void display(void);
private:
    int numitems;
    // contains the number of elements in the hashmap
    K **keyarray;
    T *reprarray;
/* keyarray defines a pointer to (an array of)
 * pointers to key values of type K.
 * reprarray defines an array of
 * corresponding values of type T.
 * We will use a null pointer,
 * if an entry is undefined,
 * and a fixed pointer as placeholder
 * for free entries (after remove) */
    K *pt_nil;
    // used as placeholder
    int maxsize;
    // defines the size of the hashmap
    void rehash(int newsize);
// rehash is an internal function
// to enlarge or shrink the hashtable,
// if the fill factors 0.75 or 0.25
// are exceeded or undershot, resp.
};

#endif /* hashmap_h */
