#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET 26

struct Trie{
    int count;
    struct Trie *children[ALPHABET];
};

// Helper function to create a new Trie node
struct Trie *newNode(void);

void insert(struct Trie **ppTrie, char *word);

int numberOfOccurances(struct Trie *pTrie, char *word);

struct Trie *deallocateTrie(struct Trie *pTrie);

int main(void)
{
    struct Trie *trie = NULL;
      //read the number of the words in the dictionary
      // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }
    
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}

// Helper function to create a new Trie node
struct Trie *newNode(void) {
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->count = 0;
    for (int i = 0; i < ALPHABET; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(struct Trie **ppTrie, char *word) {
    if (*ppTrie == NULL) {
        *ppTrie = newNode();
    }
    struct Trie *current = *ppTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = newNode();
        }
        current = current->children[index];
    }
    current->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}


struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET; i++) {
        if (pTrie->children[i] != NULL) {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}