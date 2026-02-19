/**
 * @file  spellcheck.c
 * @brief Spellchecker using a Trie data structure for fast dictionary lookup.
 * The program reads a dictionary of words (before the '%' symbol)
 * and then processes a block of text. Every word in the text that does
 * not appear in the dictionary is printed, one per line, followed by
 * the total number of unknown words.
 *
 * Part 1: Fixes the parsing logic so that words are extracted
 * 	   character-by-character, handling punctuation.
 * Part 2: Replaces array-based dictionary with a Trie, improving
 * lookup efficiency from O(n) to O(L) where L is the word length.
 *
 * BONUS:
 * When enableColor = true, the program prints the full input text with the
 * unknown words in red. This does not affect the required output and is
 * disabled by default for CodeGrade tests.
 *
 * Date: 27/11/2025
 * Course: Data Structures and Algorithms (Lab 3)
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// maximum length for a word
#define LENGTH 45

// BONUS toggle - must be FALSE for CodeGrade auto-tests
bool enableColor = false;

/*
 * ============================================================================
 *                               TRIE IMPLEMENTATION
 * ============================================================================
 */

typedef struct TrieNode* Trie;

/**
 * @struct TrieNode
 * @brief Node of a Trie used to store dictionary words
 *
 * @var endNode		true if the node marks the end of a valid dictionary word
 * @var children	array of 26 Trie pointers, one for each lowercase letter a-z.
 */
struct TrieNode {
  bool endNode;
  Trie children[26];
};

/*
 * @struct dict
 * @brief Wrapper containing the root of a Trie.
 */
typedef struct dict {
  Trie root;
} dict;

/*
 * @brief Allocates and initializes a new empty Trie node.
 *
 * @pre None.
 * @post A TrieNode is allocated, initialized with endNode = false and all children are set to NULL.
 *
 * @return Trie pointer to the newly allocated TrieNode.
 */
Trie newTrieNode(void) {
  Trie node = malloc(sizeof(struct TrieNode));

  if (node == NULL) {
    return 0;
  }

  node->endNode = false;
  for (int i = 0; i < 26; i++) {
    node->children[i] = NULL;
  }

  return node;
}

/*
 * @brief Creates an empty dictionary containing only a root node.
 *
 * @pre Memory must be available.
 * @post A valid dict pointer is returned with a new Trie root.
 *
 * @return Pointer to a new dictionary structure.
 */
dict* newEmptyDict(void) {
  dict* d = malloc(sizeof(dict));
  if (d == NULL) {
    return 0;
  }

  d->root = newTrieNode();
  return d;
}

/*
 * @brief Checks whether a word exists in the dictionary.
 *
 * @param word	Null-terminated clean lowercase word.
 * @param d	Pointer to dictionary.
 *
 * @pre word is lowercase alphabetic and null-terminated.
 * @post returns true iff the word is stored in the Trie.
 *
 * @return true if word exists in dictionary, false otherwise.
 */
bool check(const char* word, dict* d) {
  Trie node = d->root;

  for (int i = 0; word[i] != '\0'; i++) {
    int idx = word[i] - 'a';

    if (node->children[idx] == NULL) {
      return false;
    }

    node = node->children[idx];
  }

  return node->endNode;
}

/*
 * @brief Inserts a cleaned, lowercase word into the Trie.
 *
 * @param word	Null-terminated cleaned lowercase word.
 * @param d	Pointer to dictionary.
 *
 * @pre  word contains only lowercase alphabetic characters.
 * @post word is inserted into the Trie, which grows as needed.
 */
void addWord(char word[LENGTH + 1], dict* d) {
  Trie node = d->root;
  for (int i = 0; word[i] != '\0'; i++) {
    int idx = word[i] - 'a';

    if (node->children[idx] == NULL) {
      node->children[idx] = newTrieNode();
    }

    node = node->children[idx];
  }

  node->endNode = true;
}

/*
 * @brief Recursively frees a Trie node and all its children.
 *
 * @param node   Pointer to TrieNode (may be NULL)
 *
 * @pre   None.
 * @post  node and its subtrees are freed.
 */
void freeTrie(Trie node) {
  if (!node) {
    return;
  }

  for (int i = 0; i < 26; i++) {
    freeTrie(node->children[i]);
  }

  free(node);
}

/*
 * @brief Frees the entire dictionary.
 *
 * @param d    Pointer to dictionary.
 *
 * @pre   d != NULL.
 * @post  All Trie nodes and the dictionary are freed.
 */
void freeDict(dict* d) {
  if (!d) {
    return;
  }

  freeTrie(d->root);
  free(d);
}

/*
 * @brief Cleans a dictionary word:
 * 		- removes all non-letter characters
 * 		- converts letters to lowercase.
 * @param word  Input/output string to clean.
 *
 * @pre   word is null-terminated.
 * @post  word contains only lowercase letter, or becomes empty.
 */
void trimWord(char* word) {
  int k = 0;
  int len = strlen(word);
  for (int i = 0; i < len; i++) {
    if (isalpha(word[i])) {
      word[k] = tolower(word[i]);
      k++;
    }
  }

  word[k] = '\0';
}

/* ============================================================================
 *                 DYNAMIC LIST FOR STORING UNKNOWN WORDS
 * ============================================================================
 */

/*
 * @struct UnknownList
 * @brief Dynamic list of unknown words discovered in the text.
 *
 * @var words		dynamic array of strings
 * @var size		number of unknown words stored
 * @var capacity	allocated capacity of the array
 */
typedef struct UnknownList {
  char** words;  // dynamic array of C strings
  int size;      // number of unknown words stored
  int capacity;  // allocated capacity
} UnknownList;

/**
 * @brief Creates an empty UnknownList.
 *
 * @pre   Memory available
 * @post  UnknownList with capacity=1000 and size=0 is created.
 *
 * @return Pointer to the newly created UnknownList.
 */
UnknownList* newUnknownList(void) {
  UnknownList* u = malloc(sizeof(UnknownList));
  if (!u) {
    exit(1);
  }

  u->capacity = 1000;
  u->size = 0;
  u->words = malloc(u->capacity * sizeof(char*));

  if (!u->words) {
    exit(1);
  }

  return u;
}

/**
 * @brief Adds a newly found unknown word to the dynamic list, resizing as needed.
 *
 * @param u	Pointer to UnknownList.
 * @param word	Null-terminated string containing the unknown word.
 *
 * @pre		word is not NULL.
 * @post	word is copied and appended, capacity might be increased.
 */
void addUnknown(UnknownList* u, const char* word) {
  if (u->size == u->capacity) {
    u->capacity *= 2;
    u->words = realloc(u->words, u->capacity * sizeof(char*));

    if (!u->words) {
      exit(1);
    }
  }

  u->words[u->size] = malloc(strlen(word) + 1);
  strcpy(u->words[u->size], word);
  u->size++;
}

/**
 * @brief Frees all memory used by the unknown-word list.
 *
 * @param u	Pointer to the UnknownList to be removed
 *
 * @pre   	u is not NULL.
 * @post  	All stored words and the list are freed.
 */
void freeUnknownList(UnknownList* u) {
  if (!u) {
    return;
  }

  for (int i = 0; i < u->size; i++) {
    free(u->words[i]);
  }

  free(u->words);
  free(u);
}

/* ============================================================================
 *                                   MAIN
 * ============================================================================
 */

/*
 * @brief Main program: builds dictionary, processes text, outputs unknown words.
 *
 * @pre   Input must follow format:
 * 		<dictionary words separated by non-alphabetic characters>
 * 		%
 * 		<text>
 * @post  Unknown words are printed and then their count.
 *
 * @return exit (0) on success.
 */
int main(void) {
  // Step 1: read in the dictionary
  char buffer[LENGTH + 1];            // Temporary string used to read dictionary words.
  dict* dictionary = newEmptyDict();  // Trie storing all valid dictionary words.

  // Read words until '%' appears
  while (scanf("%45s", buffer) == 1) {
    if (strchr(buffer, '%') != NULL) {
      break;  // stop when encountering %
    }

    trimWord(buffer);
    if (buffer[0] != '\0') {
      addWord(buffer, dictionary);
    }
  }

  // Step 2: read in text
  UnknownList* unknown = newUnknownList();

  char word[LENGTH + 1];  // Dynamic structure storing all unknown words.
  int index = 0;          // Currently accumulated word taken from the input text.
  int c;                  // Current character read from input.

  if (enableColor) {
    printf("\n");
  }

  while ((c = getchar()) != EOF) {
    if (isalpha(c)) {
      // Collect characters into current word
      if (index < LENGTH) {
        word[index++] = tolower(c);
      }

    } else {
      // End of word
      if (index > 0) {
        word[index] = '\0';

        bool known = check(word, dictionary);  // True if the word exists in the dictionary.

        // BONUS: inline full-text colored output
        if (enableColor) {
          if (known) {
            printf("%s", word);
          } else {
            printf("\033[31m%s\033[0m", word);
          }
        }

        // Store unknown words
        if (!known) {
          addUnknown(unknown, word);
        }

        index = 0;  // Reset buffer for next word.
      }

      // Print punctuation only when bonus enabled
      if (enableColor) {
        putchar(c);
      }
    }
  }

  // File ended but last word was not flushed if no punctuation in the end (index greater than 0).
  if (index > 0) {
    word[index] = '\0';
    bool known = check(word, dictionary);  // True if last word exists in dictionary

    // Print whole text with unknown words in red (only if enableColor is set to true)
    if (enableColor) {
      if (known) {
        printf("%s", word);
      } else {
        printf("\033[31m%s\033[0m", word);
      }
    }

    if (!known) {
      addUnknown(unknown, word);
    }
  }

  // Step 3: print number of unknown words
  for (int i = 0; i < unknown->size; i++) {
    printf("%s\n", unknown->words[i]);
  }

  printf("%d\n", unknown->size);  // Print number of unknown words

  freeUnknownList(unknown);  // Free unknown word list
  freeDict(dictionary);      // Free Trie dictionary.

  return 0;
}
