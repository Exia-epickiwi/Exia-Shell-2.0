#ifndef _LOADHEADER_
#define _LOADHEADER_
  #include "main.h"
  #define PATH_PROFILE "/etc/exsh/profile"
  #define PATH_LANGUAGE "/etc/exsh/lang/"
  #define PATH_ASSISTANT "/etc/exsh/assistant"

  typedef struct LangString LangString;
  typedef struct Language Language;
  typedef struct Config Config;
  typedef struct HeadLog HeadLog;
  typedef struct ElementLog ElementLog;

  struct Config {
    int mode;
    char locale[3];
    char prompt[256];
    Language *lang;
  };

  struct HeadLog {
    int length;
    ElementLog *first;
  };
  struct ElementLog {
    ElementLog *next;
    char commande[COMMAND_LENGTH];
  };

  Config *loadConfig();

#endif
