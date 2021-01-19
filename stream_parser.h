#ifndef __c_css_stream_parser_h__
#define __c_css_stream_parser_h__


#include <stdint.h>


#include <sti/sti.h>


typedef uint32_t u32;




typedef struct ccss_stream_parser_ctx {
	u32* source;
	size_t slen;
	
	u32* cursor;
	u32* end; // the byte after the last byte of input. not necessarily readable.
	
	char eof;
	
} ccss_stream_parser_ctx;




void ccss_create_stream_parser(ccss_stream_parser_ctx* ctx);
void ccss_start_stream_parser_utf32(ccss_stream_parser_ctx* ctx, u32* source, size_t slen);






#endif // __c_css_stream_parser_h__
