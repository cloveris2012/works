#ifndef Skel_AnimationStateData_h
#define Skel_AnimationStateData_h

#include "common/HashMap.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"

#include <assert.h>

namespace skel {
	class SkeletonData;
	class Animation;

	/// Stores mix (crossfade) durations to be applied when AnimationState animations are changed.
	class SK_API AnimationStateData : public SkelObject {
		friend class AnimationState;

	public:
		explicit AnimationStateData(SkeletonData* skeletonData);

		/// The SkeletonData to look up animations when they are specified by name.
		SkeletonData* getSkeletonData();

		/// The mix duration to use when no mix duration has been specifically defined between two animations.
		float getDefaultMix();
		void setDefaultMix(float inValue);

		/// Sets a mix duration by animation names.
		void setMix(const String& fromName, const String& toName, float duration);

		/// Sets a mix duration when changing from the specified animation to the other.
		/// See TrackEntry.MixDuration.
		void setMix(Animation* from, Animation* to, float duration);

		/// The mix duration to use when changing from the specified animation to the other,
		/// or the DefaultMix if no mix duration has been set.
		float getMix(Animation* from, Animation* to);

	private:
		class AnimationPair : public SkelObject {
		public:
			Animation* _a1;
			Animation* _a2;

			explicit AnimationPair(Animation* a1 = NULL, Animation* a2 = NULL);

			bool operator==(const AnimationPair &other) const;
		};

		SkeletonData* _skeletonData;
		float _defaultMix;
		HashMap<AnimationPair, float> _animationToMixTime;
	};
}

#endif /* Skel_AnimationStateData_h */
