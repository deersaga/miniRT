#include <stdlib.h>

__attribute__((destructor))
static void destructor() {
    system("leaks -q miniRT 2>/dev/null | grep -E ' leak(s)? for ' -A 5");
}
