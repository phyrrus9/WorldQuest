#ifndef LOGGING_H
#define LOGGING_H

#define LOGGING_NONE 0x00
#define LOGGING_ERR  0x01
#define LOGGING_WARN 0x02
#define LOGGING_INFO 0x04
#define LOGGING_DBG  0x08
#define LOGGING_XTRA 0x10
#define LOGGING_ALL  0xFF

#define LOGGING_PFX_ERR  "[ERROR]"
#define LOGGING_PFX_WARN "[WARNING]"
#define LOGGING_PFX_INFO "[INFO]"
#define LOGGING_PFX_DBG  "[DEBUG]"
#define LOGGING_PFX_XTRA "[EXTRA]"

#define logfnc(name) void log_##name(const char *fmt, ...)

void log_set(unsigned char);
logfnc(err);
logfnc(warn);
logfnc(info);
logfnc(dbg);
logfnc(xtra);

#undef logfnc

#endif
