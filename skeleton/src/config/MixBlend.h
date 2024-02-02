#ifndef Skel_MixPose_h
#define Skel_MixPose_h

namespace skel {

/// Controls how a timeline is mixed with the setup or current pose.
/// See also Timeline::apply(Skeleton&, float, float, Vector&, float, Blend, MixDirection)
enum MixBlend {
	MixBlend_Setup = 0,
	MixBlend_First,
	MixBlend_Replace,
	MixBlend_Add
};
}

#endif /* Skel_MixPose_h */
