/*
 * resources_fs.h
 *
 *  Created on: 21 mar 2015
 *      Author: mac
 */

#ifndef SRC_RESOURCES_FS_H_
#define SRC_RESOURCES_FS_H_

#include "resources_types.h"
#include <iostream>
#include <cassert>
#include <string>
#include <map>
#include <unordered_map>
#include <boost/filesystem.hpp>

namespace tie {
namespace lfd {

struct Descriptor {
	boost::filesystem::path file;
};

struct ContainerInterface {
	struct Entry {
		Descriptor *descriptor;
		std::size_t offset;
		std::size_t length;
	};

	std::unordered_map<std::string, Entry> entries_map;
	void Store(const std::string & name, const Entry & entry);
	virtual TypeEnum Type() const = 0;
	const char * Name() const;
};

template<TypeEnum TYPE>
struct Container:
	public ContainerInterface {

	virtual TypeEnum Type() const override {
		return TYPE;
	}

	template<typename T>
	T *Load(const std::string & name) {
		auto entry = entries_map.find(name);
		if (entries_map.end() == entry) {
			std::cerr << "element: " << name
				<< " in container " << Name() << " not found" << std::endl;
			return nullptr;
		}


	}
};

class Storage {
private:
	bool IsTieFileResource(const boost::filesystem::path & file);
	void BuildIndexFromFile(const boost::filesystem::path & file);

	std::map<TypeEnum, ContainerInterface*> registered_containers_;
	std::size_t data_size_;
	std::size_t data_no_;

	void Register(TypeEnum type,
			const std::string & name, const ContainerInterface::Entry & entry);
public:
	Storage();
	void LoadTieDirectory(const std::string & directory);


	template<typename T>
	typename T::asset_type* GetAssetByName(const std::string & name) {
		T obj;
		assert(registered_containers_.count(obj.ContainerType()));
		auto container =
			dynamic_cast<Container<obj.ContainerType()>*>(
					registered_containers_.find(obj.ContainerType())->second
			);
		if (!container) throw std::runtime_error("Unknown container!");
		return container->template Load<typename T::asset_type>(name);
	}
};
}
}

#endif /* SRC_RESOURCES_FS_H_ */
