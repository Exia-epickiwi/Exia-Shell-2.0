#ifndef _ASSISTANTHEADER_
#define _ASSISTANTHEADER_

#define MAX_CATEGORY_LINE_LENGTH 500

typedef struct Category Category;
typedef struct CategoryElement CategoryElement;
typedef struct CategoryCommand CategoryCommand;

struct Category{
  CategoryElement *first;
  CategoryElement *last;
  CategoryElement *parent;
};

struct CategoryElement{
  Category *above;
  Category *under;
  CategoryCommand *command;
  CategoryElement *next;
  char name[COMMAND_LENGTH];
};

struct CategoryCommand{
  char command[COMMAND_LENGTH];
  char parameters[COMMAND_LENGTH];
};

int initAssistantMode(Config *config);
void printCategoryTree(Category *index,int deep);

#endif
