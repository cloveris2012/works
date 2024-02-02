#ifndef Skel_HashMap_h
#define Skel_HashMap_h

#include "../Extension.h"
#include "common/Vector.h"
#include "common/SkelObject.h"

 // Required for new with line number and file name in MSVC
#ifdef _MSC_VER
#pragma warning(disable:4291)
#endif

namespace skel {
template<typename K, typename V>
class SK_API HashMap : public SkelObject {
private:
	class Entry;

public:
	class SK_API Pair {
	public:
		explicit Pair(K &k, V &v) : key(k), value(v) {}

		K &key;
		V &value;
	};

	class SK_API Entries {
	public:
		friend class HashMap;

		explicit Entries(Entry *entry) : _entry(NULL), _hasChecked(false) {
			_start.next = entry;
			_entry = &_start;
		}

		Pair next() {
			assert(_entry);
			assert(_hasChecked);
			_entry = _entry->next;
			Pair pair(_entry->_key, _entry->_value);
			_hasChecked = false;
			return pair;
		}

		bool hasNext() {
			_hasChecked = true;
			return _entry->next;
		}

	private:
		bool _hasChecked;
		Entry _start;
		Entry *_entry;
	};

	HashMap() :
			_head(NULL),
			_size(0) {
	}

	~HashMap() {
		clear();
	}

	void clear() {
		for (Entry *entry = _head; entry != NULL;) {
			Entry* next = entry->next;
			delete entry;
			entry = next;
		}
		_head = NULL;
		_size = 0;
	}

	size_t size() {
		return _size;
	}

	void put(const K &key, const V &value) {
		Entry *entry = find(key);
		if (entry) {
			entry->_key = key;
			entry->_value = value;
		} else {
			entry = new(__FILE__, __LINE__) Entry();
			entry->_key = key;
			entry->_value = value;

			Entry *oldHead = _head;

			if (oldHead) {
				_head = entry;
				oldHead->prev = entry;
				entry->next = oldHead;
			} else {
				_head = entry;
			}
			_size++;
		}
	}

	bool containsKey(const K &key) {
		return find(key) != NULL;
	}

	bool remove(const K &key) {
		Entry *entry = find(key);
		if (!entry) return false;

		Entry *prev = entry->prev;
		Entry *next = entry->next;

		if (prev) prev->next = next;
		else _head = next;
		if (next) next->prev = entry->prev;

		delete entry;
		_size--;

		return true;
	}

	V operator[](const K &key) {
		Entry *entry = find(key);
		if (entry) return entry->_value;
		else {
			assert(false);
			return 0;
		}
	}

	Entries getEntries() const {
		return Entries(_head);
	}

private:
	Entry *find(const K &key) {
		for (Entry *entry = _head; entry != NULL; entry = entry->next) {
			if (entry->_key == key)
				return entry;
		}
		return NULL;
	}

	class SK_API Entry : public SkelObject {
	public:
		K _key;
		V _value;
		Entry *next;
		Entry *prev;

		Entry() : next(NULL), prev(NULL) {}
	};

	Entry *_head;
	size_t _size;
};
}

#endif /* Skel_HashMap_h */
