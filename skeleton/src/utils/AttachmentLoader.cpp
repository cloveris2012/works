#include "AttachmentLoader.h"

#include "../entities/Skin.h"
#include "../entities/attachments/RegionAttachment.h"
#include "../entities/attachments/MeshAttachment.h"
#include "../entities/attachments/BoundingBoxAttachment.h"
#include "../entities/attachments/PathAttachment.h"
#include "../entities/attachments/PointAttachment.h"
#include "../entities/attachments/ClippingAttachment.h"

using namespace skel;

RTTI_IMPL_NOPARENT(AttachmentLoader)

AttachmentLoader::AttachmentLoader() {
}

AttachmentLoader::~AttachmentLoader() {
}
