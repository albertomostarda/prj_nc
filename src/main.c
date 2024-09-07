/**
 * @file main.c
 * @author Alberto Mostarda (mostarda.alberto04@gmail.com)
 * @brief Il file principale del programma.
 * @version 1.0
 * @date 2024-09-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../include/features.h"
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    start();
    run();
    stop();
    return 0;
}