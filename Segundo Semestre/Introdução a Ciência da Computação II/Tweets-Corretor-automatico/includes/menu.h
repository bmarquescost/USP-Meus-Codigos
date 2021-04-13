#ifndef _MENU_H_
#define _MENU_H_

TRIE *create_dictionary_from_books(void);
JSON_DATA *json_construct_from_tweet(void);
void speel_check_tweet(TRIE *dict, JSON_DATA *js);
void free_memory(TRIE *, JSON_DATA *);

#endif