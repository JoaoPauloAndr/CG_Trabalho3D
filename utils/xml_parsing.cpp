#include "../includes/xml_parsing.h"

void readXml(const char * xmlFile, 
             Arena *arena_info, 
             std::vector<Platform>& platforms, 
             std::vector<Character_info>& enemies_info, 
             Character_info *player_info)
{
  TiXmlDocument doc;  
  if (!doc.LoadFile(xmlFile)) 
  {  
    printf("Há algum erro no caminho até, ou no nome do arquivo.\n");
    exit(0); 
  } 
  else 
  {
    TiXmlElement* rootElement =  doc.RootElement();
    //Considering Arena rectangle as the first element
    TiXmlElement* arenaSpec = rootElement -> FirstChildElement();
    arena_info->height = atof(arenaSpec->Attribute("height"));
    arena_info->length = atof(arenaSpec->Attribute("width"));
    arena_info->width = 0.5 * arena_info->height;
    arena_info->origin.x = abs(atof(arenaSpec->Attribute("x")));
    //set y to bottom of arena
    arena_info->origin.y = (atof(arenaSpec->Attribute("y"))) + arena_info->height;
    
    //get platforms & characters
    //int rects = 0;
    //int chars = 0;
    TiXmlElement* element = arenaSpec->NextSiblingElement();
    for(; element != NULL; element = element->NextSiblingElement())
    {
      std::string val = element->Value();
      if(val == "rect")
      {
        Platform platform;
        platform.width = atof(element->Attribute("width"));
        platform.height = atof(element->Attribute("height"));
        GLfloat plat_x = atof(element->Attribute("x"));
        GLfloat plat_y = atof(element->Attribute("y"));
        platform.origin.x = (plat_x < 0) ? arena_info->origin.x + plat_x : arena_info->origin.x + plat_x;
        platform.origin.y = arena_info->origin.y - plat_y;
        platforms.push_back(platform);
        //rects += 1;
      }
      else
      {
        std::string role = element->Attribute("fill");
        if(role == "red")
        {
          GLfloat head_radius = atof(element->Attribute("r"));
          GLfloat cx = atof(element->Attribute("cx"));
          GLfloat cy = atof(element->Attribute("cy"));
          GLfloat x = (cx < 0) ? arena_info->origin.x + cx : arena_info->origin.x - cx;
          GLfloat y = arena_info->origin.y - cy;
          Character_info enemyInfo;
          enemyInfo.starting_point.x = x;
          enemyInfo.starting_point.y = y;
          enemyInfo.head_radius = head_radius;
          enemies_info.push_back(enemyInfo);
        }
        else
        {
          player_info->head_radius = atof(element->Attribute("r"));
          GLfloat cx = atof(element->Attribute("cx"));
          GLfloat cy = atof(element->Attribute("cy"));
          player_info->starting_point.x = (cx < 0) ? arena_info->origin.x + cx : arena_info->origin.x - cx;
          player_info->starting_point.y = arena_info->origin.y - cy;
        }
      }
    }
  }  
}

void printXml(const char * xmlFile)
{
    TiXmlDocument doc; 
    //const char * xmlFile = "conf/school.xml";  
    if (doc.LoadFile(xmlFile)) 
    {  
        doc.Print(); 
    } 
    else 
    {
        std::cout << "can not parse xml" << std::endl;
    }  
}