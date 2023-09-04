
#ifndef ONVIFMEDIA_EXPORT_H
#define ONVIFMEDIA_EXPORT_H

#ifdef ONVIFMEDIA_STATIC_DEFINE
#  define ONVIFMEDIA_EXPORT
#  define ONVIFMEDIA_NO_EXPORT
#else
#  ifndef ONVIFMEDIA_EXPORT
#    ifdef onvifmedia_EXPORTS
        /* We are building this library */
#      define ONVIFMEDIA_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define ONVIFMEDIA_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef ONVIFMEDIA_NO_EXPORT
#    define ONVIFMEDIA_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef ONVIFMEDIA_DEPRECATED
#  define ONVIFMEDIA_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ONVIFMEDIA_DEPRECATED_EXPORT
#  define ONVIFMEDIA_DEPRECATED_EXPORT ONVIFMEDIA_EXPORT ONVIFMEDIA_DEPRECATED
#endif

#ifndef ONVIFMEDIA_DEPRECATED_NO_EXPORT
#  define ONVIFMEDIA_DEPRECATED_NO_EXPORT ONVIFMEDIA_NO_EXPORT ONVIFMEDIA_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ONVIFMEDIA_NO_DEPRECATED
#    define ONVIFMEDIA_NO_DEPRECATED
#  endif
#endif

#endif /* ONVIFMEDIA_EXPORT_H */
