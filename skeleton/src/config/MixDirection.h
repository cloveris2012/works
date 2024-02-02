#ifndef Skel_MixDirection_h
#define Skel_MixDirection_h

namespace skel {

/// Indicates whether a timeline's alpha is mixing out over time toward 0 (the setup or current pose) or mixing in toward 1 (the timeline's pose).
/// See also Timeline::apply(Skeleton&, float, float, Vector&, float, MixPose, MixDirection)
enum MixDirection {
	MixDirection_In = 0,
	MixDirection_Out
};

}

#endif /* Skel_MixDirection_h */
