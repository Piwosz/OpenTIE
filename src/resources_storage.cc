/*
 * resources_storage.cc
 *
 *  Created on: 22 mar 2015
 *      Author: mac
 */


#include "resources_fs.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cassert>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "resource.h"

namespace tie {
namespace lfd {

Storage::Storage():
	data_size_(0),
	data_no_(0) {
	registered_containers_ = std::map<TypeEnum, ContainerInterface*>{
		{TypeEnum::Anim, new Container<TypeEnum::Anim>},
		{TypeEnum::Blas, new Container<TypeEnum::Blas>},
		{TypeEnum::Bmap, new Container<TypeEnum::Bmap>},
		{TypeEnum::Cust, new Container<TypeEnum::Cust>},
		{TypeEnum::Delt, new Container<TypeEnum::Delt>},
		{TypeEnum::Film, new Container<TypeEnum::Film>},
		{TypeEnum::Font, new Container<TypeEnum::Font>},
		{TypeEnum::Gmid, new Container<TypeEnum::Gmid>},
		{TypeEnum::Mask, new Container<TypeEnum::Mask>},
		{TypeEnum::Mtrx, new Container<TypeEnum::Mtrx>},
		{TypeEnum::Panl, new Container<TypeEnum::Panl>},
		{TypeEnum::Pltt, new Container<TypeEnum::Pltt>},
		{TypeEnum::Rmap, new Container<TypeEnum::Rmap>},
		{TypeEnum::Ship, new Container<TypeEnum::Ship>},
		{TypeEnum::Text, new Container<TypeEnum::Text>},
		{TypeEnum::Voic, new Container<TypeEnum::Voic>},
		{TypeEnum::Xact, new Container<TypeEnum::Xact>},
		{TypeEnum::Undefined, nullptr}
	};
}

bool Storage::IsTieFileResource(const boost::filesystem::path & file) {
	assert(!boost::filesystem::is_directory(file));
	static std::set<std::string> available = {
			".LFD", ".GND",
	};
	return available.count(file.extension().string());
}

struct print_fuckedup_type {
	print_fuckedup_type(TypeEnum type) {
		std::cerr << std::hex << static_cast<unsigned int>(type) << std::endl;
	}
	operator bool() {
		return false;
	}
};

void Storage::Register(TypeEnum type,
		const std::string & name, const ContainerInterface::Entry & entry) {
	auto container = registered_containers_.find(type);
	assert(container != registered_containers_.end() || print_fuckedup_type(type));
	assert(container->second != nullptr);
	if (nullptr == container->second) return;
	container->second->Store(name, entry);

	/* statistics */
	data_size_+=entry.length;
	++data_no_;
}

void Storage::BuildIndexFromFile(const boost::filesystem::path & file) {
	std::ifstream stream(file.c_str(), std::ios::binary);

	Header head;
	static_assert(sizeof(head) == 16, "Bad aligment?");
	while (!stream.eof()) {
		stream.read(reinterpret_cast<char *>(&head), sizeof(head));
		if(stream.gcount() != 16) break;
		std::size_t offset = stream.tellg();
		assert(!head.name.emtpy());

		std::string virtual_path(file.parent_path().leaf().string() + '/' + file.filename().string());
		boost::algorithm::to_lower(virtual_path);
		virtual_path += '/' + head.name.String();

		if (head.type == TypeEnum::Rmap) {
			static_assert(sizeof(RmapSubHeader) == 0x10, "Zly rozmiar?");
			std::size_t nsubheaders = head.length / sizeof(RmapSubHeader);
			std::cout << "subheades: " << std::dec << nsubheaders << std::endl;

			RmapSubHeader subheader;
			for (int n = 0; n < nsubheaders; ++n) {
				stream.read(reinterpret_cast<char *>(&subheader), sizeof(subheader));
				std::cout << virtual_path << "/"
						<< subheader.name.String() << std::endl;
			}
		} else {
			stream.ignore(head.length);
		}

		Register(
				static_cast<TypeEnum>(head.type),
				virtual_path,
				{nullptr, offset, head.length}
		);
	}
}

void Storage::LoadTieDirectory(const std::string & directory) {
	std::cout << "LoadTieDirectory: " << directory << std::endl;
	if (!boost::filesystem::exists(directory)) {
		std::cerr << directory << " doesn't exists!" << std::endl;
		return;
	}

	boost::filesystem::recursive_directory_iterator itr(directory);
	boost::filesystem::recursive_directory_iterator end;
	for (; itr != end; ++itr) {
		if (boost::filesystem::is_directory(itr->status())) continue;
		if (!IsTieFileResource(itr->path())) continue;
		BuildIndexFromFile(itr->path());
	}

	std::cout << "Loaded data size: " << std::dec << data_size_ << std::endl;
	std::cout << "Loaded data items: " << std::dec << data_no_ << std::endl;
	std::cout << "Loaded containers: "
			<< std::dec << registered_containers_.size() << std::endl;

	for (const auto & container : registered_containers_) {
		if (!container.second) continue;
		std::cout << "Container: 0x"
				<< std::hex << static_cast<int>(container.second->Type())
				<< " name: " << container.second->Name()
				<< " holds: " << std::dec << container.second->entries_map.size()
				<< " items" << std::endl;
	}
}

void ContainerInterface::Store(const std::string & name, const Entry & entry) {
	std::cout << "entry: " << name
			<< " of type " <<  std::hex << static_cast<unsigned int>(Type())
			<< std::endl;
	if (entries_map.count(name)) {
		std::cerr << "name collision: " << name << std::endl;
		assert(!entries_map.count(name));
		return;
	}
	entries_map.emplace(name, entry);
}

const char * ContainerInterface::Name() const {
	return GetTypeName(Type());
}


}
}
