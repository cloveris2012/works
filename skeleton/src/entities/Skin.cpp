#include "Skin.h"

#include "attachments/Attachment.h"
#include "attachments/MeshAttachment.h"
#include "../Skeleton.h"
#include "entities/Slot.h"
#include "../data/ConstraintData.h"

#include <assert.h>

using namespace skel;

Skin::AttachmentMap::AttachmentMap() {
}

static void disposeAttachment(Attachment* attachment) {
	if (!attachment) return;
	attachment->dereference();
	if (attachment->getRefCount() == 0) delete attachment;
}

void Skin::AttachmentMap::put(size_t slotIndex, const String &attachmentName, Attachment *attachment) {
	if (slotIndex >= _buckets.size())
		_buckets.setSize(slotIndex + 1, Vector<Entry>());
	Vector<Entry> &bucket = _buckets[slotIndex];
	int existing = findInBucket(bucket, attachmentName);
	attachment->reference();
	if (existing >= 0) {
		disposeAttachment(bucket[existing]._attachment);
		bucket[existing]._attachment = attachment;
	} else {
		bucket.add(Entry(slotIndex, attachmentName, attachment));
	}
}

Attachment *Skin::AttachmentMap::get(size_t slotIndex, const String &attachmentName) {
	if (slotIndex >= _buckets.size()) return NULL;
	int existing = findInBucket(_buckets[slotIndex], attachmentName);
	return existing >= 0 ? _buckets[slotIndex][existing]._attachment : NULL;
}

void Skin::AttachmentMap::remove(size_t slotIndex, const String &attachmentName) {
	if (slotIndex >= _buckets.size()) return;
	int existing = findInBucket(_buckets[slotIndex], attachmentName);
	if (existing >= 0) {
		disposeAttachment(_buckets[slotIndex][existing]._attachment);
		_buckets[slotIndex].removeAt(existing);
	}
}

int Skin::AttachmentMap::findInBucket(Vector<Entry> &bucket, const String &attachmentName) {
	for (size_t i = 0; i < bucket.size(); i++)
		if (bucket[i]._name == attachmentName) return i;
	return -1;
}

Skin::AttachmentMap::Entries Skin::AttachmentMap::getEntries() {
	return Skin::AttachmentMap::Entries(_buckets);
}

Skin::Skin(const String &name) : _name(name), _attachments() {
	assert(_name.length() > 0);
}

Skin::~Skin() {
	Skin::AttachmentMap::Entries entries = _attachments.getEntries();
	while (entries.hasNext()) {
		Skin::AttachmentMap::Entry entry = entries.next();
		disposeAttachment(entry._attachment);
	}
}

void Skin::setAttachment(size_t slotIndex, const String &name, Attachment *attachment) {
	assert(attachment);
	_attachments.put(slotIndex, name, attachment);
}

Attachment *Skin::getAttachment(size_t slotIndex, const String &name) {
	return _attachments.get(slotIndex, name);
}

void Skin::removeAttachment(size_t slotIndex, const String& name) {
	_attachments.remove(slotIndex, name);
}

void Skin::findNamesForSlot(size_t slotIndex, Vector<String> &names) {
	Skin::AttachmentMap::Entries entries = _attachments.getEntries();
	while (entries.hasNext()) {
		Skin::AttachmentMap::Entry &entry = entries.next();
		if (entry._slotIndex == slotIndex) {
			names.add(entry._name);
		}
	}
}

void Skin::findAttachmentsForSlot(size_t slotIndex, Vector<Attachment *> &attachments) {
	Skin::AttachmentMap::Entries entries = _attachments.getEntries();
	while (entries.hasNext()) {
		Skin::AttachmentMap::Entry &entry = entries.next();
		if (entry._slotIndex == slotIndex) attachments.add(entry._attachment);
	}
}

const String &Skin::getName() {
	return _name;
}

Skin::AttachmentMap::Entries Skin::getAttachments() {
	return _attachments.getEntries();
}

void Skin::attachAll(Skeleton &skeleton, Skin &oldSkin) {
	Vector<Slot *> &slots = skeleton.getSlots();
	Skin::AttachmentMap::Entries entries = oldSkin.getAttachments();
	while (entries.hasNext()) {
		Skin::AttachmentMap::Entry &entry = entries.next();
		int slotIndex = entry._slotIndex;
		Slot *slot = slots[slotIndex];

		if (slot->getAttachment() == entry._attachment) {
			Attachment *attachment = getAttachment(slotIndex, entry._name);
			if (attachment) slot->setAttachment(attachment);
		}
	}
}

void Skin::addSkin(Skin* other) {
	for (size_t i = 0; i < other->getBones().size(); i++)
		if (!_bones.contains(other->getBones()[i])) _bones.add(other->getBones()[i]);

	for (size_t i = 0; i < other->getConstraints().size(); i++)
		if (!_constraints.contains(other->getConstraints()[i])) _constraints.add(other->getConstraints()[i]);

	AttachmentMap::Entries entries = other->getAttachments();
	while(entries.hasNext()) {
		AttachmentMap::Entry& entry = entries.next();
		setAttachment(entry._slotIndex, entry._name, entry._attachment);
	}
}

void Skin::copySkin(Skin* other) {
	for (size_t i = 0; i < other->getBones().size(); i++)
		if (!_bones.contains(other->getBones()[i])) _bones.add(other->getBones()[i]);

	for (size_t i = 0; i < other->getConstraints().size(); i++)
		if (!_constraints.contains(other->getConstraints()[i])) _constraints.add(other->getConstraints()[i]);

	AttachmentMap::Entries entries = other->getAttachments();
	while(entries.hasNext()) {
		AttachmentMap::Entry& entry = entries.next();
		if (entry._attachment->getRTTI().isExactly(MeshAttachment::rtti))
			setAttachment(entry._slotIndex, entry._name, static_cast<MeshAttachment*>(entry._attachment)->newLinkedMesh());
		else
			setAttachment(entry._slotIndex, entry._name, entry._attachment->copy());
	}
}

Vector<ConstraintData*>& Skin::getConstraints() {
	return _constraints;
}

Vector<BoneData*>& Skin::getBones() {
	return _bones;
}
