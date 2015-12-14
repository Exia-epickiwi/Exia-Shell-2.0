#ifndef _LOGHEADER_
#define _LOGHEADER_
  #include "config.h"
  #define PATH_LOG "/var/log/exsh.log"
  void toLog(char *string);
  void loadHistory(Config *config);
  void seeLog(Config *config);
#endif
