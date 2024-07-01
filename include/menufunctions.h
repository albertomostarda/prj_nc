#ifndef MENUFUNCTIONS_H
#define MENUFUNCTIONS_H

int loadSaves();
void createSaves();
void init_menu();
void menu(int *quit);
void menu_subrun(int mMode, int *pExit, int *lvlPass);
void init_selectLvl();
void selectLvl(int *rQuit);
void selectLvl_subrun(int mode);

#endif