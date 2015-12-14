#ifndef _HANOIHEADER_
#define _HANOIHEADER_

typedef struct HanoiTower HanoiTower;
typedef struct HanoiDisc HanoiDisc;

struct HanoiTower{
  HanoiDisc *top;
  int height;
};

struct HanoiDisc{
  HanoiTower *tower;
  HanoiDisc *next;
  int size;
};

void initHanoiGame(Language *lang);

#endif
