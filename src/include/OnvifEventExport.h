
#ifndef ONVIFEVENT_EXPORT_H
#define ONVIFEVENT_EXPORT_H

#ifdef ONVIFEVENT_STATIC_DEFINE
#  define ONVIFEVENT_EXPORT
#  define ONVIFEVENT_NO_EXPORT
#else
#  ifndef ONVIFEVENT_EXPORT
#    ifdef onvifevent_EXPORTS
        /* We are building this library */
#      define ONVIFEVENT_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define ONVIFEVENT_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef ONVIFEVENT_NO_EXPORT
#    define ONVIFEVENT_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef ONVIFEVENT_DEPRECATED
#  define ONVIFEVENT_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ONVIFEVENT_DEPRECATED_EXPORT
#  define ONVIFEVENT_DEPRECATED_EXPORT ONVIFEVENT_EXPORT ONVIFEVENT_DEPRECATED
#endif

#ifndef ONVIFEVENT_DEPRECATED_NO_EXPORT
#  define ONVIFEVENT_DEPRECATED_NO_EXPORT ONVIFEVENT_NO_EXPORT ONVIFEVENT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ONVIFEVENT_NO_DEPRECATED
#    define ONVIFEVENT_NO_DEPRECATED
#  endif
#endif

#endif /* ONVIFEVENT_EXPORT_H */
