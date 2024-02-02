#ifndef SKEL_SHAREDLIB_H
#define SKEL_SHAREDLIB_H

#ifdef _WIN32
#define DLLIMPORT __declspec(dllimport)
#define DLLEXPORT __declspec(dllexport)
#else
#ifndef DLLIMPORT
#define DLLIMPORT
#endif
#ifndef DLLEXPORT
#define DLLEXPORT
#endif
#endif

#ifdef SKELPLUGIN_API
#define SK_API SKELPLUGIN_API
#else
#define SK_API
#endif

#endif /* SKEL_SHAREDLIB_H */
