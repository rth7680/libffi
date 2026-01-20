#if defined(__CET__)
# include <cet.h>
# if (__CET__ & 1) != 0
#   define ENDBR_PRESENT
# endif
# define _CET_NOTRACK notrack
#else
# define _CET_ENDBR
# define _CET_NOTRACK
#endif
