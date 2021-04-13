#ifndef _JSON_H_
#define  _JSON_H_

#define TWEET_PATH ""

typedef struct json_text JSON_TEXT;
typedef struct json_data JSON_DATA;

struct json_text {
    char **string_list;
    int amnt_strings;
};

struct json_data {
    JSON_TEXT *texts;
    int amnt_texts;
};

JSON_DATA *json_read_texts_fields(char *);
JSON_DATA *json_create(void);
void json_delete(JSON_DATA *);
JSON_DATA *json_from_tweet(char *);


#endif