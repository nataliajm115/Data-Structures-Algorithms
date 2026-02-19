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

// A helper function mapping 'a' to 0, 'b' to 1, etc.
// Do not modify this.
int c2n(char c) {
  c = tolower(c);
  return (c - 'a');
}

// Exercise 1
// Write a function that prints all the words in a standard trie.
// You may assume that no word is longer than 100 characters.
// Hint: use a helper function with an additional char* argument!
void collectAndPrint(Trie t, char* buffer, int depth) {
	if (t == NULL) return;

	if (t->endNode) {
		buffer[depth] = '\0';
		printf("%s\n", buffer);
	}

	for (int i = 0; i < 26; i++) {
		if (t->children[i] != NULL) {
			buffer[depth] = 'a' + i;
			collectAndPrint(t->children[i], buffer, depth + 1);
		}
	}
}

void printWordsInTrie(Trie t) {
	char buffer[101];
	collectAndPrint(t, buffer, 0);
}

// Exercise 2
// Write a function to print a standard trie. Use dots and spaces to indent and <
// as end marker. For example, print the trie for {a, are, at, bee, bit} like this:
//
// a <
// . r
// . . e <
// . t <
// b
// . e
// . . e <
// . i
// . . t <
//
// Hint: use a helper function with an additional int argument.
void printHelper(Trie t, int depth) {
	if (t == NULL) return;

	for (int i = 0; i< 26; i++) {
		Trie child = t->children[i];
		if (child != NULL) {
			for (int k = 0; k < depth; k++) {
				printf(". ");
			}

			printf("%c", 'a' + i);

			if (child->endNode) printf(" <");
			printf("\n");

			printHelper(child, depth + 1);
		}
	}
}

void printTrie(Trie t) {
	printHelper(t, 0);
}

/** Please do not modify anything below this line. **/

// Helper function to make tries. Please do not modify this.
Trie makeEmptyTrie(void) {
  Trie t = malloc(1 * sizeof(struct TrieNode));
  t->endNode = false;
  for (int i = 0; i < 26; i++) {
    t->children[i] = NULL;
  }
  return t;
}

// An example Trie for the set {a, are, bee}. Please do not modify this.
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

// An example Trie for the set {a, are, at, bee, bit}. Please do not modify this.
Trie makeSecondExampleTrie(void) {
  Trie t = makeEmptyTrie();
  t->children[c2n('a')] = makeEmptyTrie();
  t->children[c2n('a')]->endNode = true;
  t->children[c2n('a')]->children[c2n('r')] = makeEmptyTrie();
  t->children[c2n('a')]->children[c2n('r')]->children[c2n('e')] = makeEmptyTrie();
  t->children[c2n('a')]->children[c2n('r')]->children[c2n('e')]->endNode = true;
  t->children[c2n('a')]->children[c2n('t')] = makeEmptyTrie();
  t->children[c2n('a')]->children[c2n('t')]->endNode = true;
  t->children[c2n('b')] = makeEmptyTrie();
  t->children[c2n('b')]->children[c2n('e')] = makeEmptyTrie();
  t->children[c2n('b')]->children[c2n('e')]->children[c2n('e')] = makeEmptyTrie();
  t->children[c2n('b')]->children[c2n('e')]->children[c2n('e')]->endNode = true;
  t->children[c2n('b')]->children[c2n('i')] = makeEmptyTrie();
  t->children[c2n('b')]->children[c2n('i')]->children[c2n('t')] = makeEmptyTrie();
  t->children[c2n('b')]->children[c2n('i')]->children[c2n('t')]->endNode = true;
  return t;
}

// Free a trie. Please do not modify this.
void freeTrie(Trie t) {
  for (int i = 0; i < 26; i++) {
    if (t->children[i] != NULL) {
      freeTrie(t->children[i]);
    }
  }
  free(t);
}

// Please do not edit the main function.
int main(void) {
  printf("Which of the two example tries do you want to use?\n");
  printf("1. {a, are, bee}\n");
  printf("2. {a, are, at, bee, bit}\n");
  printf("Enter '1' or '2'.\n");
  int tree = 0;
  scanf("%d", &tree);
  getchar();  // skip newline
  Trie t = (tree == 1 ? makeExampleTrie() : makeSecondExampleTrie());
  printf("Do you want to print the trie or the words? Enter 'T' or 'W'.\n");
  char command = ' ';
  scanf("%c", &command);
  getchar();  // skip newline
  if (command == 'T') {
    printTrie(t);
  } else if (command == 'W') {
    printWordsInTrie(t);
  }
  freeTrie(t);
  return 0;
}
