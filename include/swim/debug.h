#ifndef SWIM_DEBUG_H
#define SWIM_DEBUG_H

#define SWIM_DEBUG_PRINT(...)
#define SWIM_DEBUG(fmt, ...)
#define SWIM_D(str)

#ifdef SWIM_DEBUG_ENABLED
    #include <stdio.h> /* For fprintf */

    #undef SWIM_DEBUG_PRINT
    #undef SWIM_DEBUG
    #undef SWIM_D

    #define SWIM_DEBUG_HERE_STR "[file %s, line %d]: "

    #define SWIM_DEBUG_HERE_ARGS __FILE__, __LINE__

    #define SWIM_DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)

    #define SWIM_DEBUG(fmt, ...) SWIM_DEBUG_PRINT(SWIM_DEBUG_HERE_STR fmt,  \
                                                 (SWIM_DEBUG_HERE_ARGS),    \
                                                 (__VA_ARGS__))

    #define SWIM_D(str) SWIM_DEBUG("%s\n", str)

#else
    #define SWIM_DEBUG_DISABLED
#endif

#endif /* SWIM_DEBUG_H */
