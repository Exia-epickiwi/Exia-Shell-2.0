#ifndef _LANGUAGEHEADER_
#define _LANGUAGEHEADER_

typedef struct LangString{
  char key[KEY_LENGTH];
  char value[COMMAND_LENGTH];
  LangString *next;
} LangString;

typedef struct Language{
  LangString *first;
  int length;
} Language;

#endif
