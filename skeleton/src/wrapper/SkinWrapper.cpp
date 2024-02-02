#include "SkinWrapper.h"


using namespace skel;

SkinWrapper::SkinWrapper(const String & name):Skin(name){

}

std::string SkinWrapper::getSkinName()
{
	std::string name = getName().buffer();//直接返回skel::String会报错
	return name;
}

LuaIntf::LuaRef SkinWrapper::getAttachmentWrappers(lua_State* L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef ref(L, -1);
	LS.pop();
	Skin::AttachmentMap::Entries entries = getAttachments();
	while (entries.hasNext()) {
		Skin::AttachmentMap::Entry &entry = entries.next();
		int slotIndex = entry._slotIndex;
		LuaIntf::LuaRef atts = ref.get< LuaIntf::LuaRef>(slotIndex);
		if ( !atts ) {
			LS.newTable();
			LuaIntf::LuaRef newatts(L, -1);
			LS.pop();
			atts = newatts;
			ref.set<int, LuaIntf::LuaRef>(slotIndex, atts);
		}
		auto len = atts.len() + 1;

		if ( entry._attachment->getRTTI().instanceOf(RegionAttachment::rtti)) {
			atts.set<int, RegionAttachmentWrapper*>(len,dynamic_cast<RegionAttachmentWrapper*>(entry._attachment));
		}
		else if (entry._attachment->getRTTI().instanceOf(MeshAttachment::rtti)) {
			atts.set<int, MeshAttachmentWrapper*>(len, dynamic_cast<MeshAttachmentWrapper*>(entry._attachment));
		}
	}
	return ref;
}

void SkinWrapper::addAttachmentWrapper(int slotIndex,const char* name,Attachment *atta) {
	setAttachment(slotIndex, atta->getName(), atta);
}

void SkinWrapper::removeAttachmentWrapper(int slotIndex, const char* name) {
	skel::String str(name);
	removeAttachment(slotIndex, str);
}

void SkinWrapper::addSlot(int slotIndex){
	Skin::AttachmentMap::Entries entries = getAttachments();
	auto &bucket = entries._buckets;
	if (slotIndex + 1 < bucket.size()) {
		auto lastIndex = bucket.size()-1;
		bucket.add(bucket[lastIndex]);
		while (lastIndex > slotIndex) {
			bucket[lastIndex] = bucket[lastIndex - 1];
			lastIndex--;
		}
		bucket[slotIndex] = Vector<Skin::AttachmentMap::Entry>();
	}
	else {

		bucket.setSize(slotIndex + 1,Vector<Skin::AttachmentMap::Entry>());
	}
}

void SkinWrapper::removeSlot(int slotIndex){
	Skin::AttachmentMap::Entries entries = getAttachments();
	auto &bucket = entries._buckets;
	if (slotIndex < bucket.size()) {
		while (slotIndex < bucket.size() - 1) {
			bucket[slotIndex] = bucket[slotIndex+1];
			slotIndex++;
		}
		//如果不设置新值，remove时会把对应的引用干掉，slotIndex-1的值就会被销毁
		bucket[slotIndex] = Vector<Skin::AttachmentMap::Entry>();
		bucket.removeAt(slotIndex);
	}
}

void SkinWrapper::copySkin(SkinWrapper * skin)
{
	return Skin::copySkin(dynamic_cast<Skin *>(skin));
}

void SkinWrapper::addSkin(SkinWrapper * skin)
{
	return Skin::addSkin(dynamic_cast<Skin *>(skin));
}
