#include <iostream>
#include <vector>

using namespace std;

#define MAX_TREE_HT 100

struct Node {
    char character;
    unsigned frequency;
    struct Node *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct Node** array;
};

struct Node* createNewNode(char character, unsigned frequency) {
    struct Node* temp = new Node;
    temp->left = temp->right = nullptr;
    temp->character = character;
    temp->frequency = frequency;
    return temp;
}

struct MinHeap* createNewMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = new MinHeap;
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = new Node*[minHeap->capacity];
    return minHeap;
}

void swapNodes(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isHeapSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

Node* extractMinimum(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void insertToMinHeap(MinHeap* minHeap, Node* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = node;
}

void constructMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printNodeCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printNodeCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printNodeCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        cout << root->character << ": ";
        for (int i = 0; i < top; ++i)
            cout << arr[i];
        cout << "\n";
    }
}

MinHeap* createAndBuildNewMinHeap(char data[], unsigned freq[], int size) {
    MinHeap* minHeap = createNewMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNewNode(data[i], freq[i]);

    minHeap->size = size;
    constructMinHeap(minHeap);

    return minHeap;
}

Node* constructHuffmanTree(char data[], unsigned freq[], int size) {
    Node *left, *right, *top;
    MinHeap* minHeap = createAndBuildNewMinHeap(data, freq, size);

    while (!isHeapSizeOne(minHeap)) {
        left = extractMinimum(minHeap);
        right = extractMinimum(minHeap);

        top = createNewNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertToMinHeap(minHeap, top);
    }

    return extractMinimum(minHeap);
}

void generateHuffmanCodes(char data[], unsigned freq[], int size) {
    Node* root = constructHuffmanTree(data, freq, size);

    int arr[MAX_TREE_HT], top = 0;
    printNodeCodes(root, arr, top);
}

int main() {
    int arraySize;

    cout << "Enter the size of the character array: ";
    cin >> arraySize;

    char characters[arraySize];
    unsigned frequencies[arraySize];

    cout << "Enter the characters and their frequencies:" << endl;
    for (int i = 0; i < arraySize; ++i) {
        cout << "Character " << i + 1 << ": ";
        cin >> characters[i];
        cout << "Frequency " << i + 1 << ": ";
        cin >> frequencies[i];
    }

    generateHuffmanCodes(characters, frequencies, arraySize);

    return 0;
}
