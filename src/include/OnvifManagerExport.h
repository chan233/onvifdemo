
#ifndef ONVIFMANAGER_EXPORT_H
#define ONVIFMANAGER_EXPORT_H

#ifdef ONVIFMANAGER_STATIC_DEFINE
#  define ONVIFMANAGER_EXPORT
#  define ONVIFMANAGER_NO_EXPORT
#else
#  ifndef ONVIFMANAGER_EXPORT
#    ifdef onvifManager_EXPORTS
        /* We are building this library */
#      define ONVIFMANAGER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define ONVIFMANAGER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef ONVIFMANAGER_NO_EXPORT
#    define ONVIFMANAGER_NO_EXPORT 
#  endif
#endif

#ifndef ONVIFMANAGER_DEPRECATED
#  define ONVIFMANAGER_DEPRECATED __declspec(deprecated)
#endif

#ifndef ONVIFMANAGER_DEPRECATED_EXPORT
#  define ONVIFMANAGER_DEPRECATED_EXPORT ONVIFMANAGER_EXPORT ONVIFMANAGER_DEPRECATED
#endif

#ifndef ONVIFMANAGER_DEPRECATED_NO_EXPORT
#  define ONVIFMANAGER_DEPRECATED_NO_EXPORT ONVIFMANAGER_NO_EXPORT ONVIFMANAGER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ONVIFMANAGER_NO_DEPRECATED
#    define ONVIFMANAGER_NO_DEPRECATED
#  endif
#endif

#endif /* ONVIFMANAGER_EXPORT_H */
