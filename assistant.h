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
Category* parseCategory(FILE *file,long position,Category *parent);
Category* loadCategories(char *path);
int getDeep(char *buffer);
void addCategoryElement(Category *parent,char *name,Category *under, CategoryCommand *command);
char* getCategoryLineName(char* buffer);
void printCategoryTree(Category *index,int deep);
char* getCategoryCommand(char* buffer);
int printCategoryElements(Language *lang,Category *cat);
Category* performCategoryAction(Language *lang,Category *nowCategory,char *input,int maxChoice);
int execCategoryCommand(Language *lang,CategoryCommand *command);
char getNextCategoryParam(char *command);
void askForCategoryPram(Language *lang,char* command,char paramType,char *pramsNames);
char* getCategoryParams(char* buffer);

#endif
