/*
 * resources_fs.h
 *
 *  Created on: 21 mar 2015
 *      Author: mac
 */

#ifndef SRC_RESOURCES_FS_H_
#define SRC_RESOURCES_FS_H_

#include "resources_types.h"
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

};
}
}

#endif /* SRC_RESOURCES_FS_H_ */
