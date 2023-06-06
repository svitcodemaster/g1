// Consider telephone book database of N clients

#include <iostream>
#include<string.h>
using namespace std;

class HashFunction {
private:
    struct Hash {
        long key;
        string name;
    };
    Hash h[10];

public:
    HashFunction();
    void insert();
    void display();
    int find(long);
    void Delete(long);
    int linearProbe(int);
    int quadraticProbe(int);
};

HashFunction::HashFunction() {
    for (int i = 0; i < 10; i++) {
        h[i].key = -1;
        h[i].name = "NULL";
    }
}

void HashFunction::Delete(long k) {
    int index = find(k);
    if (index == -1) {
        cout << "\n\tKey Not Found";
    } else {
        h[index].key = -1;
        h[index].name = "NULL";
        cout << "\n\tKey is Deleted";
    }
}

int HashFunction::find(long k) {
    for (int i = 0; i < 10; i++) {
        if (h[i].key == k) {
            cout << "\n\t" << h[i].key << " is Found at " << i << " Location With Name " << h[i].name;
            return i;
        }
    }
    return -1;  // if key not found
}

void HashFunction::display() {
    cout << "\n\t\tKey\t\tName";
    for (int i = 0; i < 10; i++) {
        cout << "\n\th[" << i << "]\t" << h[i].key << "\t\t" << h[i].name;
    }
}


int HashFunction::quadraticProbe(int index) {
    int i = 1;
    int offset = 1;

    while (h[(index + (offset * offset)) % 10].key != -1) {
        offset++;
        i++;    
        if (i > 10) // No empty slot found after probing all locations
            return -1;          
    }
    return (index + (offset * offset)) % 10;
}



int HashFunction::linearProbe(int index) {
    int i = index + 1;
    for (; i < 10; i++) {
        if (h[i].key == -1)
            return i;
    }
    if (i == 10) {
        i = 0;
        for (; i < index; i++) {
            if (h[i].key == -1)
                return i;
        }
    }
    return -1; // No empty slot found
}

void HashFunction::insert() {
    char ans;
    string n;
    long k;
    int hi, cnt = 0;
    do {
        if (cnt >= 10) {
            cout << "\n\tHash Table is FULL";
            break;
        }
        cout << "\n\tEnter a Telephone No: ";
        cin >> k;
        cout << "\n\tEnter a Client Name: ";
        cin >> n;
        hi = k % 10;
    if (h[hi].key == -1) {
        h[hi].key = k;
        h[hi].name = n;
    } else {
        cout << "\n Collision occurs...using linear probing for collision resolution";
        int index = linearProbe(hi);
        if (index != -1) {
            h[index].key = k;
            h[index].name = n;
        } else {
            cout << "\n\tNo empty slot available for linear probing";
        }
        
        cout << "\n Collision occurs...using quadratic probing for collision resolution";
        index = quadraticProbe(hi);
        if (index != -1) {
            h[index].key = k;
            h[index].name = n;
        } else {
            cout << "\n\tNo empty slot available for quadratic probing";
        }
    } 
        cnt++;
        cout << "\n\t..... Do You Want to Insert More Key: ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}


int main() {
    long k;
    int ch, index;
    char ans;
    HashFunction obj;
    do {
        cout << "\n\t***** Dictionary (ADT) *****";
        cout << "\n\t1.Insert\n\t2.Display\n\t3.Find\n\t4.Delete\n\t5.Exit";
        cout << "\n\tEnter Your Choice: ";
        cin >> ch;
        switch (ch){
            case 1:
                obj.insert();
                break;
            case 2:
                obj.display();
                break;
            case 3:
                cout << "\n\tEnter a Key Which You Want to Search: ";
                cin >> k;
                index = obj.find(k);
                if (index == -1) {
                    cout << "\n\tKey Not Found";
                }
                break;
            case 4:
                cout << "\n\tEnter a Key Which You Want to Delete: ";
                cin >> k;
                obj.Delete(k);
                break;
            case 5:
                break;
        }
        cout << "\n\t..... Do You Want to Continue in Main Menu: ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}