#include "logging.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static unsigned char logging_opt;
void _p_log(const char *fmt, va_list lst, const char *pfx);
void log_set(unsigned char level) { logging_opt = level; }
#define logfnc(name, opt, pfx)\
void log_##name(const char *fmt, ...) {\
	va_list args; \
	va_start(args, fmt); \
	if (logging_opt & opt) \
		_p_log(fmt, args, pfx); \
	va_end(args); }
logfnc(err, LOGGING_ERR, LOGGING_PFX_ERR);
logfnc(warn, LOGGING_WARN, LOGGING_PFX_WARN);
logfnc(info, LOGGING_INFO, LOGGING_PFX_INFO);
logfnc(dbg, LOGGING_DBG, LOGGING_PFX_DBG);
logfnc(xtra, LOGGING_XTRA, LOGGING_PFX_XTRA);
#undef logfnc

void _p_log(const char *fmt, va_list lst, const char *pfx)
{
	char *buf;
	buf = (char *)malloc(strlen(fmt) + strlen(pfx) + 1);
	sprintf(buf, "%s\t\t%s\n", pfx, fmt);
	vprintf(buf, lst);
	free(buf);
}
