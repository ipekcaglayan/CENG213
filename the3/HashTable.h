#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"
#include "ItemNotFoundException.h"
#include "iostream"
/* Do not add new libraries or files */
using namespace std;
#define BUCKET_SIZE 2

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template<class K, class T>
class HashTable {
    struct Entry {
        K Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[BUCKET_SIZE];
    };

    int _capacity; // INDICATES THE TOTAL CAPACITY OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket *_table; // THE HASH TABLE

    // == DEFINE HELPER METHODS & VARIABLES BELOW ==
    void resizeHelper(const K &key, const T &value, Bucket * &newTable);


public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();

    // COPY THE WHOLE CONTENT OF RHS INCLUDING THE KEYS THAT WERE SET AS DELETED
    HashTable(const HashTable<K, T> &rhs);

    HashTable<K, T> &operator=(const HashTable<K, T> &rhs);

    ~HashTable();
    


    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY E_table[hashCode].entriesISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY E_table[hashCode].entriesISTING ONE. IF THE LOAD FACTOR OF THE TABLE IS GREATER THAN 0.6,
    // RESIZE THE TABLE WITH THE NE_table[hashCode].entriesT PRIME NUMBER.
    void Insert(const K &key, const T &value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT E_table[hashCode].entriesIST IN THE TABLE, THROW ItemNotFoundException()
    void Delete(const K &key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT E_table[hashCode].entriesIST, THROW ItemNotFoundException()
    T &Get(const K &key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS E_table[hashCode].entriesECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE E_table[hashCode].entriesISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES
    void Resize(int newCapacity);

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const; // RETURN THE TOTAL CAPACITY OF THE TABLE
    int Size() const; // RETURN THE NUMBER OF ACTIVE ITEMS
    void getKeys(K *keys); // PUT THE ACTIVE KEYS TO THE GIVEN INPUT PARAMETER
};


template<class K, class T>
HashTable<K, T>::HashTable() {
    // TODO: IMPLEMENT THIS FUNCTION.
    _capacity = 7;
    _size = 0;
    _table = new Bucket[_capacity];


}

template<class K, class T>
HashTable<K, T>::HashTable(const HashTable<K, T> &rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    _table= new Bucket[7];
    *this = rhs;

}

template<class K, class T>
HashTable<K, T> &HashTable<K, T>::operator=(const HashTable<K, T> &rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    delete[] _table;
    _capacity = rhs.Capacity();
    _size = rhs.Size();
    Bucket *created = new Bucket[_capacity];
    for (int i = 0; i < _capacity; i++) {
        created[i].entries[0] = rhs._table[i].entries[0];
        created[i].entries[1] = rhs._table[i].entries[1];


    }
    _table = created;
    return *this;

}

template<class K, class T>
HashTable<K, T>::~HashTable() {
    // TODO: IMPLEMENT THIS FUNCTION.

    delete[] _table;


}

template<class K, class T>
void HashTable<K, T>::Insert(const K &key, const T &value) {
    // TODO: IMPLEMENT THIS FUNCTION.
    int hashVal = Hash(key) % _capacity;
    //check if key already exists
    int k = 1;
    int x=1;
    int index = hashVal;
    //continue until find an empty (not deleted)
    while (_table[index].entries[0].Active || _table[index].entries[1].Active || _table[index].entries[0].Deleted ||
           _table[index].entries[1].Deleted) {
        if (_table[index].entries[0].Active && _table[index].entries[0].Key == key) {
            _table[index].entries[0].Value = value;
            return;
        }
        else if(_table[index].entries[1].Active==false && _table[index].entries[1].Deleted==false){
            break;
        }
         else if (_table[index].entries[1].Active && _table[index].entries[1].Key == key) {
            _table[index].entries[1].Value = value;
            return;
        }

        index = (hashVal + x)%_capacity;
        k++;
        x = k*k;
    }
    //new key will be added
    index=hashVal;
    k=0;
    while (1) {
        if (_table[index].entries[0].Active==false) {
            _table[index].entries[0].Key = key;
            _table[index].entries[0].Value = value;
            _table[index].entries[0].Active = true;
            _table[index].entries[0].Deleted = false;
            _size++;
            break;

        }
            //second entry empty
        else if (_table[index].entries[1].Active==false) {
            _table[index].entries[1].Key = key;
            _table[index].entries[1].Value = value;
            _table[index].entries[1].Active = true;
            _table[index].entries[1].Deleted = false;
            _size++;

            break;

        } else {
            k++;
            x=k* k;
            index = hashVal + x;
            if (index >= _capacity) {
                index = index % _capacity;
                if(index<0){
                    index+=_capacity;
                }
            }


        }

    }
    if ((double) _size / (2*_capacity) > 0.6) {
        Resize(NextCapacity(_capacity));
    }
}

//template<class K, class T>
//void HashTable<K, T>::resizeHelper(const K &key, const T &value, Bucket * &newTable){
//    int hashVal = Hash(key) % _capacity;
//    //check if key already exists
//    int k = 1;
//    int index = hashVal;
//    //new key will be added
//    // first entry empty
//    if (!newTable[hashVal].entries[0].Active) {
//        newTable[hashVal].entries[0].Key = key;
//        newTable[hashVal].entries[0].Value = value;
//        newTable[hashVal].entries[0].Active = true;
//        newTable[hashVal].entries[0].Deleted = false;
//    }
//        //second entry empty
//    else if (!newTable[hashVal].entries[1].Active) {
//        newTable[hashVal].entries[1].Key = key;
//        newTable[hashVal].entries[1].Value = value;
//        newTable[hashVal].entries[1].Active = true;
//        newTable[hashVal].entries[1].Deleted = false;
//
//
//
//
//    }
//        // table[hashVal] is full
//    else {
//        int k = 1;
//        int index = hashVal + 1;
//        while (1) {
//            if (!newTable[index].entries[0].Active) {
//                newTable[index].entries[0].Key = key;
//                newTable[index].entries[0].Value = value;
//                newTable[index].entries[0].Active = true;
//                newTable[index].entries[0].Deleted = false;
//                break;
//
//            }
//                //second entry empty
//            else if (!newTable[index].entries[1].Active) {
//                newTable[index].entries[1].Key = key;
//                newTable[index].entries[1].Value = value;
//                newTable[index].entries[1].Active = true;
//                newTable[index].entries[1].Deleted = false;
//                break;
//
//            } else {
//                k++;
//                k *= k;
//                index = hashVal + k;
//                if (index >= _capacity) {
//                    index = index % _capacity;
//                    if(index<0){
//                        index+=_capacity;
//                    }
//                }
//
//
//            }
//
//        }
//
//    }
//}
template<class K, class T>
void HashTable<K, T>::Delete(const K &key) {
    // TODO: IMPLEMENT THIS FUNCTION.
    int hashVal = Hash(key) % _capacity;
    int k = 1;
    int x=1;
    int index = hashVal;
    while (_table[index].entries[0].Active || _table[index].entries[1].Active || _table[index].entries[0].Deleted ||
           _table[index].entries[1].Deleted) {
        if (_table[index].entries[0].Active && _table[index].entries[0].Key == key) {
            _table[index].entries[0].Deleted=true;
            _table[index].entries[0].Active=false;
            _size--;
            return;

        } else if (_table[index].entries[1].Active && _table[index].entries[1].Key == key) {
            _table[index].entries[1].Deleted=true;
            _table[index].entries[1].Active=false;
            _size--;
            return;
        }

        index = hashVal + x;
        if (index >= _capacity) {
            index = index % _capacity;
        }
        k++;
        x = k*k;
    }
    throw ItemNotFoundException();


}

template<class K, class T>
T &HashTable<K, T>::Get(const K &key) const {
    // TODO: IMPLEMENT THIS FUNCTION.
    int hashVal = Hash(key) % _capacity;
    //check if key already exists
    int k = 1;
    int x=1;
    int index = hashVal;
    while (_table[index].entries[0].Active || _table[index].entries[1].Active || _table[index].entries[0].Deleted ||
           _table[index].entries[1].Deleted) {
        if (_table[index].entries[0].Active && _table[index].entries[0].Key == key) {
            return _table[index].entries[0].Value;
        }
        else if(_table[index].entries[1].Active==false && _table[index].entries[1].Deleted==false){
            break;
        }
        else if (_table[index].entries[1].Active && _table[index].entries[1].Key == key) {
            return _table[index].entries[1].Value;
        }

        index = (hashVal + x)%_capacity;
        k++;
        x = k*k;
    }
    throw ItemNotFoundException();
}


template<class K, class T>
void HashTable<K, T>::Resize(int newCapacity) {
    // TODO: IMPLEMENT THIS FUNCTION.
     K *keys=new K[_size];
     getKeys(keys);
     T *values=new T[_size];
     for( int i=0; i<_size;i++){
         values[i]=Get(keys[i]);

     }
     delete[] _table;
     int before=_size;
     _capacity=newCapacity;
     _size=0;
     _table=new Bucket[_capacity];
     for(int i=0; i<before;i++){
         Insert(keys[i],values[i]);

     }
     delete[] keys;
     delete[] values;


}


template<class K, class T>
int HashTable<K, T>::Capacity() const {
    return _capacity;
}

template<class K, class T>
int HashTable<K, T>::Size() const {
    return _size;
}


template<class K, class T>
void HashTable<K, T>::getKeys(K *keys) {
    int index = 0;

    for (int i = 0; i < _capacity; i++) {
        Bucket &bucket = _table[i];
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted) {
                keys[index++] = bucket.entries[j].Key;
            }
        }
    }
}



#endif