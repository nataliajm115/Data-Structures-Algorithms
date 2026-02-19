#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TrieNode* Trie;

struct TrieNode {
  bool endNode;
  Trie children[26];
};

// A helper function mapping a to 0, b to 1, etc.
int c2n(char c) {
  c = tolower(c);
  return (c - 'a');
}

// Search for a word in a trie.
bool searchInTrie(Trie k, char* word) {
	if (k ==  NULL) return false;
	for (int i = 0; word[i] != '\0'; i++) {
		char x = word[i];
		int indx = c2n(x);

		if (k->children[indx] == NULL) return false;

		k = k->children[indx];
	}

	return k->endNode;
}

// Helper function to make tries. Do not modify this.
Trie makeEmptyTrie(void) {
  Trie t = malloc(1 * sizeof(struct TrieNode));
  t->endNode = false;
  for (int i = 0; i < 26; i++) {
    t->children[i] = NULL;
  }
  return t;
}

// Create an example Trie for the set {a, are, bee}. Do not modify this.
Trie makeExampleTrie(void) {
  Trie t = makeEmptyTrie();
  t->children[c2n('a')] = makeEmptyTrie();
  t->children[c2n('a')]->endNode = true;
  t->children[c2n('a')]->children[c2n('r')] = makeEmptyTrie();
  t->children[c2n('a')]->children[c2n('r')]->children[c2n('e')] = makeEmptyTrie();
  t->children[c2n('a')]->children[c2n('r')]->children[c2n('e')]->endNode = true;
  t->children[c2n('b')] = makeEmptyTrie();
  t->children[c2n('b')]->children[c2n('e')] = makeEmptyTrie();
  t->children[c2n('b')]->children[c2n('e')]->children[c2n('e')] = makeEmptyTrie();
  t->children[c2n('b')]->children[c2n('e')]->children[c2n('e')]->endNode = true;
  return t;
}

// Do not modify this.
void freeTrie(Trie t) {
  for (int i = 0; i < 26; i++) {
    if (t->children[i] != NULL) {
      freeTrie(t->children[i]);
    }
  }
  free(t);
}

// Do not edit the main function.
int main(void) {
  Trie t = makeExampleTrie();
  char word[256] = "";
  printf("Which word do you want to search in the trie?\n");
  scanf("%255s", word);
  if (searchInTrie(t, word)) {
    printf("The word '%s' is in the trie.\n", word);
  } else {
    printf("The word '%s' is not in the trie.\n", word);
  }
  freeTrie(t);
  return 0;
}
