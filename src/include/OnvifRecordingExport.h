
#ifndef ONVIFRECORDING_EXPORT_H
#define ONVIFRECORDING_EXPORT_H

#ifdef ONVIFRECORDING_STATIC_DEFINE
#  define ONVIFRECORDING_EXPORT
#  define ONVIFRECORDING_NO_EXPORT
#else
#  ifndef ONVIFRECORDING_EXPORT
#    ifdef onvifrecording_EXPORTS
        /* We are building this library */
#      define ONVIFRECORDING_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define ONVIFRECORDING_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef ONVIFRECORDING_NO_EXPORT
#    define ONVIFRECORDING_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef ONVIFRECORDING_DEPRECATED
#  define ONVIFRECORDING_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ONVIFRECORDING_DEPRECATED_EXPORT
#  define ONVIFRECORDING_DEPRECATED_EXPORT ONVIFRECORDING_EXPORT ONVIFRECORDING_DEPRECATED
#endif

#ifndef ONVIFRECORDING_DEPRECATED_NO_EXPORT
#  define ONVIFRECORDING_DEPRECATED_NO_EXPORT ONVIFRECORDING_NO_EXPORT ONVIFRECORDING_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ONVIFRECORDING_NO_DEPRECATED
#    define ONVIFRECORDING_NO_DEPRECATED
#  endif
#endif

#endif /* ONVIFRECORDING_EXPORT_H */
