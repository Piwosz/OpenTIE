/*
 * resources_types.h
 *
 *  Created on: 21 mar 2015
 *      Author: mac
 */

#ifndef SRC_RESOURCES_TYPES_H_
#define SRC_RESOURCES_TYPES_H_

namespace tie {
namespace lfd {

#define RESOURCE_TYPE_SET(X) \
	X(Anim, 0x4D494E41, "Animation") 		\
	X(Blas, 0x53414c42, "Sound effects")	\
	X(Bmap, 0x50414d42, "Bitmap")			\
	X(Cust, 0x54535543, "Custom")			\
	X(Delt, 0x544c4544, "Static image")		\
	X(Film, 0x4d4c4946, "Layout")			\
	X(Font, 0x544e4f46, "Font")				\
	X(Gmid, 0x44494D47, "MIDI")				\
	X(Mask, 0x4B53414D, "Mask")				\
	X(Mtrx, 0x5852544D, "Matrix")			\
	X(Panl, 0x4C4E4150, "Cockpit panel")	\
	X(Pltt, 0x54544c50, "Palette")			\
	X(Rmap, 0x50414D52, "Resource map")		\
	X(Ship, 0x50494853, "Ship")				\
	X(Text, 0x54584554, "Strings")			\
	X(Voic, 0x43494f56, "Voice")			\
	X(Xact, 0x54434158, "ACT image")

enum class TypeEnum : unsigned int {
	Undefined,
#define X(name, value, ignore) name = value,
	RESOURCE_TYPE_SET(X)
#undef X
	Last
};

static const char * GetTypeName(TypeEnum type) {
	switch(type) {
#define X(name, type, descr) case TypeEnum::name: return descr;
	RESOURCE_TYPE_SET(X)
#undef X
	default:
		break;
	}
	return "Unkown";
}

}
}

#endif /* SRC_RESOURCES_TYPES_H_ */
