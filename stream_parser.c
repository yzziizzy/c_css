

typedef ccss_stream_parser_ctx* pctx; 


void ccss_init_stream_parser(ccss_stream_parser_ctx* ctx) {
	memset(ctx, 0, sizeof(*ctx));
	
}




#define CHECK_EOF(c) \
do { \
	if((c)->eof || (c)->cursor >= (c)->end) { \
		(c)->eof = 1; \
		return 1; \
	} \
} while(0)

#define INC_EOF(c) \
do { \
	(c)->cursor++; \
	CHECK_EOF(c); \
} while(0)

static int consume_whitespace(pctx ctx) {
	while(1) {
		CHECK_EOF(ctx);
		
		if(!isspace32(*ctx->cursor)) return 0;	
	
		ctx->cursor++;
	}
	
	return 1;
}



static u32 css_getchar(pctx ctx) {
	if(ctx->cursor >= ctx->end) {
		ctx->eof = 1;
		return 0;
	}
	
	u32 c = ctx->cursor[0];
	ctx->cursor++;
	
	if(c == '\\') {
		// escape sequence
		
		if(!isxdigit(ctx->cursor[0])) {
			c = ctx->cursor[0];
			ctx->cursor++;
		}
		else {
			char tmp[7];
			int n = 0;
			
			// eat up to 6 hex digits
			for(int i = 0; i < 6 && ctx->cursor < ctx->end; i++) {
			
				if(isxdigit(ctx->cursor[0])) {
					tmp[n++] = ctx->cursor[0];
				}
				
				ctx->cursor++;
			}
			
			tmp[n] = 0;
			c = strtol(tmp, NULL, 16);
			
			// check for and eat a single whitespace
			if(isspace32(ctx->cursor[0])) {
				ctx->cursor++;
			}
			
		}
	}
	
	
	if(ctx->cursor >= ctx->end) ctx->eof = 1;
	
	return c;
}


static u32 css_strstr(pctx ctx, u32* s, u32* accept, u32** end) {
	u32* orig_cursor = ctx->cursor;
	
	while(1) {
		u32 c = css_getchar(ctx);
		if(ctx->eof) return 0;
		
		for(int i = 0; accept[i]; i++) {
			if(c == accept[i]) {
				*end = ctx->cursor;
				
				ctx->cursor = orig_cursor;
				return c;
			}
		}
		
	}

	ctx->eof = 1;
	return 0;
}

// "@media"
static int parse_at_rule(pctx ctx) {
	
	// skip the '@'
	INC_EOF(ctx);
	
	// get the rule prelude
	// find the next ; or {, skiping escapes
	u32* end;
	u32 terminals[] = {';', '{', 0};
	u32 c = css_strstr(ctx, ctx->cursor, terminals, &end);
	
	if(c == '{') {
		// parse the body
		// recurse past bracket pairs until a lone } is found
		
		
		
		
		return 0;
	}
	
	// non-body rule (;) or broken rule (file ended before the rule ended)
	// treat it like an at-rule with no body
	
	// call the user 
	
		
	return 0;
}


// ".foo > .bar"
static int parse_qualified_rule(pctx ctx) {

	u32* end;
	u32 terminals[] = {'{', 0};
	u32 c = css_strstr(ctx, ctx->cursor, terminals, &end);
	
	if(c != '{') {
		// broken rule; file ended before {
		
		return 1;
	}
	
	// parse declarations
	ctx->cursor = end;
	INC_EOF(ctx); // skip the {
	
	consume_whitespace(ctx);
	
	while(1) {
		
		// look for :
		
		// look for ;
		
	}
	
	
	
}


static int parse_loop(pctx ctx) {
	
	
	while(!ctx->eof) {
		
		consume_whitespace(ctx);
		
		// at the base level of the file
		
		u32 c = ctx->cursor[0];
		if(c == '@') {
			// at-rule ("@media")
			parse_at_rule(ctx);
		}
		else {
			// qualified rule (".foo > .bar")
			parse_qualified_rule(ctx);
		}
		
		
	}
	
	// close off any open blocks on the stack
	
	
}



void ccss_start_stream_parser_utf32(css_stream_parser_ctx* ctx, u32* source, size_t slen) {
		ctx->source = source;
		ctx->slen = slen;
		
		ctx->cursor = source;
		ctx->end = ctx->source + slen;
		
		ctx->eof = 1;
		
		
		// start parsing
		parse_loop(pctx);
				
	
}



