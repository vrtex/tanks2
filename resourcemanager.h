#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <map>
#include <string>
#include <iostream>

namespace res
{
	template <typename T>
	class ResourceManager
	{
	public:
		ResourceManager()
		{
			content.emplace(std::make_pair("empty_thing", T()));
		}
		void addContent(std::string id, std::string path)
		{
			if(content.count(id)) return;
			content.emplace(std::make_pair(id, T()));
			content.at(id).loadFromFile(path);
		}
		T &get(std::string id)
		{
			if(!content.count(id))
			{
				std::cout << "no content called " << id << " to return\n";
				return content.at("empty_thing");
			}
			return content.at(id);
		}
		void deleteContent(std::string id)
		{
			if(content.count(id) == 0)
			{
				std::cout << ("no element called " + id + " to delete\n");
				return;
			}
			content.erase(id);
		}
		~ResourceManager()
		{

		}
	private:
		std::map<std::string, T> content;
	};
	template <typename T>
	ResourceManager<T> & getResources()
	{
		static ResourceManager<T> staticResources;
		return staticResources;
	}
}


