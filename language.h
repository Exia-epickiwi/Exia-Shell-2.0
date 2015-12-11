#ifndef _LANGUAGEHEADER_
#define _LANGUAGEHEADER_

#define MAX_LANG_LINE_LENGTH 390

typedef struct LangString LangString;

struct LangString{
  char key[KEY_LENGTH];
  char value[COMMAND_LENGTH];
  LangString *next;
};

typedef struct Language{
  LangString *first;
  LangString *last;
  int length;
} Language;

Language* loadLanguage(char *file);
Language* parseLanguageFile(FILE *langFile);
void addLanguageString(Language *target,char *key, char *value);

#endif
