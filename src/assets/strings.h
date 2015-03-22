/*
 * strings.h
 *
 *  Created on: 22 mar 2015
 *      Author: mac
 */

#ifndef SRC_ASSETS_STRINGS_H_
#define SRC_ASSETS_STRINGS_H_

#include "description.h"

namespace tie {
namespace assets {

class RStrings {
public:
	RStrings();
	~RStrings();

};

typedef Descriptor<lfd::TypeEnum::Text, RStrings> TagStrings;

} /* namespace assets */
} /* namespace tie */

#endif /* SRC_ASSETS_STRINGS_H_ */
