/*
 * description.h
 *
 *  Created on: 22 mar 2015
 *      Author: mac
 */

#include "resource.h"

namespace tie {
namespace assets {

template<lfd::TypeEnum T, typename C>
struct Descriptor {
	constexpr lfd::TypeEnum ContainerType() const {
		return T;
	}
	typedef C asset_type;
};

};
};
