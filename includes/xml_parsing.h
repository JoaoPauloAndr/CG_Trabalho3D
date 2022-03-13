#ifndef XML_PARSING_H
#define XML_PARSING_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "tinyxml.h"
#include "info.h"
//using namespace std;

void readXml(const char * xmlFile, 
             Arena *arena_info, 
             std::vector<Platform>& platforms, 
             std::vector<Character_info> &enemies_info, 
             Character_info *player_info
            );

void printXml(const char * xmlFile);            

#endif