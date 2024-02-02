#ifndef Skel_Skin_h
#define Skel_Skin_h

#include "common/Vector.h"
#include "common/SkelString.h"

namespace skel {
class Attachment;

class Skeleton;
class BoneData;
class ConstraintData;

/// Stores attachments by slot index and attachment name.
/// See SkeletonData::getDefaultSkin, Skeleton::getSkin, and
/// http://esotericsoftware.com/skel-runtime-skins in the SKEL Runtimes Guide.
class SK_API Skin : public SkelObject {
	friend class Skeleton;

public:
	class SK_API AttachmentMap : public SkelObject {
		friend class Skin;

	public:
		struct SK_API Entry {
			size_t _slotIndex;
			String _name;
			Attachment *_attachment;

			Entry(size_t slotIndex, const String &name, Attachment *attachment) :
					_slotIndex(slotIndex),
					_name(name),
					_attachment(attachment) {
			}
		};

		class SK_API Entries {
			friend class AttachmentMap;

		public:
			bool hasNext() {
				while(true) {
					if (_slotIndex >= _buckets.size()) return false;
					if (_bucketIndex >= _buckets[_slotIndex].size()) {
						_bucketIndex = 0;
						++_slotIndex;
						continue;
					};
					return true;
				}
			}

			Entry &next() {
				Entry &result = _buckets[_slotIndex][_bucketIndex];
				++_bucketIndex;
				return result;
			}
			Vector< Vector<Entry> > &_buckets;

		protected:
			Entries(Vector< Vector<Entry> > &buckets) : _buckets(buckets), _slotIndex(0), _bucketIndex(0) {
			}

		private:
			
			size_t _slotIndex;
			size_t _bucketIndex;
		};

		void put(size_t slotIndex, const String &attachmentName, Attachment *attachment);

		Attachment *get(size_t slotIndex, const String &attachmentName);

		void remove(size_t slotIndex, const String &attachmentName);

		Entries getEntries();

	protected:
		AttachmentMap();

	private:

		int findInBucket(Vector <Entry> &, const String &attachmentName);

		Vector <Vector<Entry> > _buckets;
	};

	explicit Skin(const String &name);

	~Skin();

	/// Adds an attachment to the skin for the specified slot index and name.
	/// If the name already exists for the slot, the previous value is replaced.
	void setAttachment(size_t slotIndex, const String &name, Attachment *attachment);

	/// Returns the attachment for the specified slot index and name, or NULL.
	Attachment *getAttachment(size_t slotIndex, const String &name);

	// Removes the attachment from the skin.
	void removeAttachment(size_t slotIndex, const String& name);

	/// Finds the skin keys for a given slot. The results are added to the passed array of names.
	/// @param slotIndex The target slotIndex. To find the slot index, use Skeleton::findSlotIndex or SkeletonData::findSlotIndex
	/// @param names Found skin key names will be added to this array.
	void findNamesForSlot(size_t slotIndex, Vector <String> &names);

	/// Finds the attachments for a given slot. The results are added to the passed array of Attachments.
	/// @param slotIndex The target slotIndex. To find the slot index, use Skeleton::findSlotIndex or SkeletonData::findSlotIndex
	/// @param attachments Found Attachments will be added to this array.
	void findAttachmentsForSlot(size_t slotIndex, Vector<Attachment *> &attachments);

	const String &getName();

	/// Adds all attachments, bones, and constraints from the specified skin to this skin.
	void addSkin(Skin* other);

	/// Adds all attachments, bones, and constraints from the specified skin to this skin. Attachments are deep copied.
	void copySkin(Skin* other);

	AttachmentMap::Entries getAttachments();

	Vector<BoneData*>& getBones();

	Vector<ConstraintData*>& getConstraints();
private:
	const String _name;
	AttachmentMap _attachments;
	Vector<BoneData*> _bones;
	Vector<ConstraintData*> _constraints;

	/// Attach all attachments from this skin if the corresponding attachment from the old skin is currently attached.
	void attachAll(Skeleton &skeleton, Skin &oldSkin);
};
}

#endif /* Skel_Skin_h */