#ifndef _LOADHEADER_
#define _LOADHEADER_

#define PATH_PROFILE "/etc/exsh/profile/"
#define PATH_LANGUAGE "/etc/exsh/lang/"

typedef struct LangString LangString;
typedef struct Language Language;
typedef struct Config Config;

struct Config {
  int mode;
  char locale[3];
  char prompt[256];
  Language *lang;
};

struct Language {
  LangString *first;
  int length;
};

struct LangString {
  char key[128];
  char value[256];
  LangString *next;
};

Config *loadConfig();

#endif
