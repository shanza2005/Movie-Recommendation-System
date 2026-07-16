#include <iostream>

using namespace std;

// ==========================================
// 1. TRIE NODE CLASS
// ==========================================
class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
    }
};

// ==========================================
// 2. CUSTOM QUEUE FOR BFS (Using Linked List)
// ==========================================
// Hum khud ki Queue bana rahe hain kyunke built-in <queue> mana hai.
class QueueNode {
public:
    TrieNode* trieNode;
    QueueNode* next;

    QueueNode(TrieNode* node) {
        trieNode = node;
        next = NULL;
    }
};

class CustomQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    CustomQueue() {
        front = NULL;
        rear = NULL;
    }

    // Queue mein element dalna (Peeche)
    void push(TrieNode* node) {
        QueueNode* temp = new QueueNode(node);
        if (rear == NULL) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }

    // Queue se element nikalna (Aage se)
    void pop() {
        if (front == NULL) return;
        QueueNode* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
    }

    // Sab se aage wala element dekhna
    TrieNode* getFront() {
        if (front == NULL) return NULL;
        return front->trieNode;
    }

    // Check karna kya queue khali hai?
    bool isEmpty() {
        return front == NULL;
    }
};

// ==========================================
// 3. MAIN TRIE CLASS WITH DFS & BFS
// ==========================================
class Trie {
private:
    TrieNode* root;

    // DFS Helper: Yeh recursion se gehrai mein jata hai
    // Hum character array aur ek currentLength variable use kar rahe hain string sambhalne ke liye
    void dfsHelper(TrieNode* curr, char currentWord[], int length) {
        // Agar yahan word khatam ho raha hai, to character array ko print karo
        if (curr->isEndOfWord) {
            for (int i = 0; i < length; i++) {
                cout << currentWord[i];
            }
            cout << " ";
        }

        // 'a' se 'z' tak check karo
        for (int i = 0; i < 26; i++) {
            if (curr->children[i] != NULL) {
                currentWord[length] = 'a' + i; // Character add kiya
                dfsHelper(curr->children[i], currentWord, length + 1); // Agli depth par gaye
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // INSERT FUNCTION (Bina kisi string library function ke)
    void insert(const char* word) {
        TrieNode* curr = root;
        
        // Loop tab tak chalega jab tak string ka aakhri hidden character '\0' nahi aata
        for (int i = 0; word[i] != '\0'; i++) {
            int index = word[i] - 'a'; // Character ka index nikala (0 se 25)
            
            // Agar rasta nahi bana hua, to naya node banao
            if (curr->children[index] == NULL) {
                curr->children[index] = new TrieNode();
            }
            curr = curr->children[index]; // Agle node par jump karo
        }
        curr->isEndOfWord = true; // Word khatam, flag true kar diya
    }

    // DFS DISPLAY (Alphabetical order mein print karega)
    void displayDFS() {
        cout << "DFS Traversal (Words): ";
        char wordBuffer[100]; // Words ko temporary store karne ke liye array
        dfsHelper(root, wordBuffer, 0);
        cout << endl;
    }

    // BFS DISPLAY (Level-by-level saare characters print karega)
    void displayBFS() {
        cout << "BFS Traversal (Characters Level by Level): ";
        if (root == NULL) return;

        CustomQueue q; // Humari apni banayi hui Queue!
        q.push(root);

        while (!q.isEmpty()) {
            TrieNode* curr = q.getFront();
            q.pop();

            // Is node ke jitne bhi bache hain, unhe print karo aur queue mein dalo
            for (int i = 0; i < 26; i++) {
                if (curr->children[i] != NULL) {
                    char ch = 'a' + i;
                    cout << ch << " "; // Character print ho raha hai
                    q.push(curr->children[i]); // Bache ko queue mein dal diya
                }
            }
        }
        cout << endl;
    }
};

// ==========================================
// 4. MAIN FUNCTION (Execution)
// ==========================================
int main() {
    Trie myTrie;

    // Words insert kar rahe hain (Simple character arrays ki shakal mein)
    myTrie.insert("cat");
    myTrie.insert("car");
    myTrie.insert("do");

    // Output check karte hain
    myTrie.displayDFS(); 
    myTrie.displayBFS();

    return 0;
}