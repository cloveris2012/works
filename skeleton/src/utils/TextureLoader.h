#ifndef Skel_TextureLoader_h
#define Skel_TextureLoader_h

#include "common/SkelObject.h"
#include "common/SkelString.h"

namespace skel {
	class AtlasPage;

	class SK_API TextureLoader : public SkelObject {
	public:
		TextureLoader();

		virtual ~TextureLoader();

		virtual void load(AtlasPage& page, const String& path) = 0;

		virtual void unload(void* texture) = 0;
	};
}

#endif /* Skel_TextureLoader_h */
