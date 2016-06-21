/*
 * File:   libexport.h
 * Author: 123
 *
 * Created on 1 Март 2014 г., 17:47
 */

#ifndef LIBEXPORT_H
#define LIBEXPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __linux__

#define DLL_EXPORT

#else

#ifdef LIB
#define DLL_EXPORT __declspec(dllexport)
#elif NOLIB
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif /* LIBEXPORT_H */

