#ifndef MUTINY_ENGINE_RESOURCES_H
#define MUTINY_ENGINE_RESOURCES_H

#include "Debug.h"
#include "Material.h"
#include "Application.h"

#include "internal/Internal.h"

#include <memory>
#include <string>
#include <vector>
#include <typeinfo>
#include <sstream>

namespace mutiny
{

namespace engine
{

class Object;
class Application;

class Resources
{
  friend class mutiny::engine::Application;

public:
  template<class T> static T* load(std::string path)
  {
    std::stringstream ss;
    ss << path << "_" << typeid(T).name();

    for(int i = 0; i < paths.size(); i++)
    {
      if(ss.str() == paths.at(i))
      {
        return (T*)objects.at(i).get();
      }
    }

    T* t = NULL;

    // Game specific resources
    try
    {
      t = T::load(Application::getInternal()->dataPath + "/" + path);
    }
    catch(std::exception& e){}

    // Internal engine files
    if(t == NULL)
    {
      try
      {
        t = T::load(Application::getInternal()->engineDataPath + "/" + path);
      }
      catch(std::exception& e){}
    }

    // Absolute path
    if(t == NULL)
    {
      try
      {
        t = T::load(path);
      }
      catch(std::exception& e){}
    }

    if(t == NULL)
    {
      //Debug::logError("Failed to load '" + path + "'");
      return NULL;
    }

    paths.push_back(ss.str());
    objects.push_back(std::shared_ptr<Object>(t));

    return t;
  }

private:
  static std::vector<std::string> paths;
  static std::vector<std::shared_ptr<Object> > objects;

};

}

}

#endif

