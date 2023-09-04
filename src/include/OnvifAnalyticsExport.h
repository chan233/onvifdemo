
#ifndef ONVIFANALYTICS_EXPORT_H
#define ONVIFANALYTICS_EXPORT_H

#ifdef ONVIFANALYTICS_STATIC_DEFINE
#  define ONVIFANALYTICS_EXPORT
#  define ONVIFANALYTICS_NO_EXPORT
#else
#  ifndef ONVIFANALYTICS_EXPORT
#    ifdef onvifanalytics_EXPORTS
        /* We are building this library */
#      define ONVIFANALYTICS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define ONVIFANALYTICS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef ONVIFANALYTICS_NO_EXPORT
#    define ONVIFANALYTICS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef ONVIFANALYTICS_DEPRECATED
#  define ONVIFANALYTICS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ONVIFANALYTICS_DEPRECATED_EXPORT
#  define ONVIFANALYTICS_DEPRECATED_EXPORT ONVIFANALYTICS_EXPORT ONVIFANALYTICS_DEPRECATED
#endif

#ifndef ONVIFANALYTICS_DEPRECATED_NO_EXPORT
#  define ONVIFANALYTICS_DEPRECATED_NO_EXPORT ONVIFANALYTICS_NO_EXPORT ONVIFANALYTICS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ONVIFANALYTICS_NO_DEPRECATED
#    define ONVIFANALYTICS_NO_DEPRECATED
#  endif
#endif

#endif /* ONVIFANALYTICS_EXPORT_H */
