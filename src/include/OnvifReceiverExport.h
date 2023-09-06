
#ifndef ONVIFRECEIVER_EXPORT_H
#define ONVIFRECEIVER_EXPORT_H

#ifdef ONVIFRECEIVER_STATIC_DEFINE
#  define ONVIFRECEIVER_EXPORT
#  define ONVIFRECEIVER_NO_EXPORT
#else
#  ifndef ONVIFRECEIVER_EXPORT
#    ifdef onvifreceiver_EXPORTS
        /* We are building this library */
#      define ONVIFRECEIVER_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define ONVIFRECEIVER_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef ONVIFRECEIVER_NO_EXPORT
#    define ONVIFRECEIVER_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef ONVIFRECEIVER_DEPRECATED
#  define ONVIFRECEIVER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ONVIFRECEIVER_DEPRECATED_EXPORT
#  define ONVIFRECEIVER_DEPRECATED_EXPORT ONVIFRECEIVER_EXPORT ONVIFRECEIVER_DEPRECATED
#endif

#ifndef ONVIFRECEIVER_DEPRECATED_NO_EXPORT
#  define ONVIFRECEIVER_DEPRECATED_NO_EXPORT ONVIFRECEIVER_NO_EXPORT ONVIFRECEIVER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ONVIFRECEIVER_NO_DEPRECATED
#    define ONVIFRECEIVER_NO_DEPRECATED
#  endif
#endif

#endif /* ONVIFRECEIVER_EXPORT_H */
