#ifndef Skel_ContainerUtil_h
#define Skel_ContainerUtil_h

#include "../Extension.h"
#include "common/Vector.h"
#include "common/HashMap.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"

#include <assert.h>

namespace skel {
	class SK_API ContainerUtil : public SkelObject {
	public:
		/// Finds an item by comparing each item's name.
		/// It is more efficient to cache the results of this method than to call it multiple times.
		/// @return May be NULL.
		template<typename T>
		static T* findWithName(Vector<T*>& items, const String& name) {
			assert(name.length() > 0);

			for (size_t i = 0; i < items.size(); ++i) {
				T* item = items[i];
				if (item->getName() == name) {
					return item;
				}
			}

			return NULL;
		}

		/// @return -1 if the item was not found.
		template<typename T>
		static int findIndexWithName(Vector<T*>& items, const String& name) {
			assert(name.length() > 0);

			for (size_t i = 0, len = items.size(); i < len; ++i) {
				T* item = items[i];
				if (item->getName() == name) {
					return static_cast<int>(i);
				}
			}

			return -1;
		}

		/// Finds an item by comparing each item's name.
		/// It is more efficient to cache the results of this method than to call it multiple times.
		/// @return May be NULL.
		template<typename T>
		static T* findWithDataName(Vector<T*>& items, const String& name) {
			assert(name.length() > 0);

			for (size_t i = 0; i < items.size(); ++i) {
				T* item = items[i];
				if (item->getData().getName() == name) {
					return item;
				}
			}

			return NULL;
		}

		/// @return -1 if the item was not found.
		template<typename T>
		static int findIndexWithDataName(Vector<T*>& items, const String& name) {
			assert(name.length() > 0);

			for (size_t i = 0, len = items.size(); i < len; ++i) {
				T* item = items[i];
				if (item->getData().getName() == name) {
					return static_cast<int>(i);
				}
			}

			return -1;
		}

		template<typename T>
		static void cleanUpVectorOfPointers(Vector<T*>& items) {
			for (int i = (int)items.size() - 1; i >= 0; i--) {
				T* item = items[i];

				delete item;

				items.removeAt(i);
			}
		}

	private:
		// ctor, copy ctor, and assignment should be private in a Singleton
		ContainerUtil();
		ContainerUtil(const ContainerUtil&);
		ContainerUtil& operator=(const ContainerUtil&);
	};
}

#endif /* Skel_ContainerUtil_h */
