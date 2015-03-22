/*
 * Resource.h
 *
 *  Created on: 22 mar 2015
 *      Author: mac
 */

#ifndef SRC_RESOURCE_H_
#define SRC_RESOURCE_H_

#include <boost/filesystem.hpp>
#include "resources_types.h"
#include "varchar.h"

namespace tie {
namespace lfd {

struct Header {
	TypeEnum type;
	Varchar<8> name;
	std::uint32_t length;
};

typedef Header RmapSubHeader;

//class Resource {
//private:
//	boost::filesystem::path filename_;
//public:
//	Resource(const boost::filesystem::path & file);
//	virtual ~Resource();
//
//	const boost::filesystem::path & filename() const {
//		return filename_;
//	}
//};

} /* namespace lfd */
} /* namespace tie */

#endif /* SRC_RESOURCE_H_ */
