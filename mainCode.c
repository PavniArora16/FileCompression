#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node {
    char data;
    int freq;
    struct node* left;
    struct node* right;
};

struct minHeap {
    int size;
    int capacity;
    struct node** array;
};

static int total = 0;
static int len;

struct node* createNode(char data, int freq) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct minHeap* createMinHeap(int capacity) {
    struct minHeap* mHeap = (struct minHeap*)malloc(sizeof(struct minHeap));
    mHeap->size = 0;
    mHeap->capacity = capacity;
    mHeap->array = (struct node**)malloc(capacity * sizeof(struct node*));
    return mHeap;
}

void swap(struct node** a, struct node** b) {
    struct node* temp = *a;
    *a = *b;
    *b = temp;
}

void heap(struct minHeap* mHeap, int index) {
    int min = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < mHeap->size && mHeap->array[left]->freq < mHeap->array[min]->freq)
        min = left;
    if (right < mHeap->size && mHeap->array[right]->freq < mHeap->array[min]->freq)
        min = right;
    if (min != index) {
        swap(&mHeap->array[min], &mHeap->array[index]);
        heap(mHeap, min);
    }
}

bool isSizeOne(struct minHeap* mHeap) {
    return (mHeap->size == 1);
}

struct node* extractMin(struct minHeap* mHeap) {
    struct node* temp = mHeap->array[0];
    mHeap->array[0] = mHeap->array[mHeap->size - 1];
    --mHeap->size;
    heap(mHeap, 0);
    return temp;
}

void insertMinHeap(struct minHeap* mHeap, struct node* minHeapNode) {
    ++mHeap->size;
    int i = mHeap->size - 1;
    while (i && minHeapNode->freq <= mHeap->array[(i - 1) / 2]->freq) {
        mHeap->array[i] = mHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    mHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct minHeap* mHeap) {
    int n = mHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; i--)
        heap(mHeap, i);
}

bool isLeaf(struct node* root) {
    return !(root->left) && !(root->right);
}

struct minHeap* createAndBuild(char data[], int freq[], int size) {
    struct minHeap* mHeap = createMinHeap(size);
    int i;
    for (i = 0; i < size; i++)
        mHeap->array[i] = createNode(data[i], freq[i]);
    mHeap->size = size;
    buildMinHeap(mHeap);
    return mHeap;
}

struct node* buildTree(char data[], int freq[], int size) {
    struct node *left, *right, *top;
    struct minHeap* mHeap = createAndBuild(data, freq, size);
    while (!isSizeOne(mHeap)) {
        left = extractMin(mHeap);
        right = extractMin(mHeap);
        top = createNode('#', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(mHeap, top);
    }
    return extractMin(mHeap);
}

void storeCodes(struct node* root, int arr[], int top, char codes[256][50]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, codes);
    }
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, codes);
    }
    if (isLeaf(root)) {
        codes[(unsigned char)root->data][top] = '\0';
        int i;
        for (i = 0; i < top; i++)
            codes[(unsigned char)root->data][i] = arr[i] + '0';
    }
}

struct node* Huffman(char data[], int freq[], int size, char codes[256][50]) {
    struct node* root = buildTree(data, freq, size);
    int arr[50];
    storeCodes(root, arr, 0, codes);
    return root;
}

int frequency(char *g, int *ch, int i, char *inputString) {
    int x, c = 0;
    int count[256] = {0};
    len = strlen(inputString);
    while (inputString[c] != '\0' && inputString[c] != '\n') {
        if (inputString[c] >= 32 && inputString[c] <= 126) {
            x = (unsigned char)inputString[c];
            count[x]++;
        }
        c++;
    }
    for (c = 0; c < 256; c++) {
        if (count[c] != 0) {
            g[i] = c;
            ch[i] = count[c];
            i++;
        }
    }
    return i;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    char input[1000];
    fgets(input, sizeof(input), fp);
    fclose(fp);

    char g[256];
    int ch[256];
    int i=0;
    i = frequency(g, ch, i, input);

    char codes[256][50] = {{0}};
    struct node* root = Huffman(g, ch, i, codes);

    printf("\nHuffman Codes:\n");
    int k;
    for (k = 0; k < i; k++) {
        printf("%c = %s\n", g[k], codes[(unsigned char)g[k]]);
    }

    char encoded[10000] = "";
    for (k = 0; k < strlen(input); k++) {
        if (input[k] >= 32 && input[k] <= 126)
            strcat(encoded, codes[(unsigned char)input[k]]);
    }

    total = strlen(encoded);

    //encoded string
    fp = fopen("input.txt", "a");
    fprintf(fp, "\nEncoded string: %s", encoded);
    fclose(fp);

    //summary
    printf("\nOriginal space required: %d bits\n", len * 8);
    printf("Space required for encoded text: %d bits\n", total);
    double saved = (len * 8) - total;
    double percentage = (saved * 100) / (len * 8);
    printf("Memory saved: %.0f bits, %.2f%% reduction\n", saved, percentage);
    printf("\nTask Done!\n");

    return 0;
}
