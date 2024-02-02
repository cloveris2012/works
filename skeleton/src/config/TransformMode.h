#ifndef Skel_TransformMode_h
#define Skel_TransformMode_h

namespace skel {
	enum TransformMode {
		TransformMode_Normal = 0,
		TransformMode_OnlyTranslation,
		TransformMode_NoRotationOrReflection,
		TransformMode_NoScale,
		TransformMode_NoScaleOrReflection
	};
}

#endif /* Skel_TransformMode_h */
