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

Config *loadConfig();

#endif
