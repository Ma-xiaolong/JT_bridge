/*********************************************************************
** \file "<!FileBase!>.h"
** created by python:3.9.13
** time:2018-09-10 14:14:36
** \brief This file provides a declaration of the class
*********************************************************************/


#ifndef MAKEXTEND_EXPORT_H
#define MAKEXTEND_EXPORT_H

// Detect operating system
#if defined(_WIN32) || defined(_WIN64)
    #define OS_WINDOWS
    #ifdef BUILDING_MAKEXTEND_DLL
        #define MAKEXTEND_EXPORT __declspec(dllexport)
    #else
        #define MAKEXTEND_EXPORT __declspec(dllimport)
    #endif
#else
    #define OS_LINUX
    #ifdef BUILDING_MAKEXTEND_DLL
        #define MAKEXTEND_EXPORT __attribute__((visibility("default")))
    #else
        #define MAKEXTEND_EXPORT
    #endif
#endif
#endif // MAKEXTEND_EXPORT_H