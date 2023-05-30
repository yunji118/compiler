typedef union
{
    char *id;
} YYSTYPE;

/* Tokens.  */
#define TLOWERTHANELSE 258
#define TELSE 259
#define TIDENT 260
#define TNUMBER 261
#define TCONST 262
#define TIF 263
#define TINT 264
#define TRETURN 265
#define TVOID 266
#define TWHILE 267
#define TADDASSIGN 268
#define TSUBASSIGN 269
#define TMULASSIGN 270
#define TDIVASSIGN 271
#define TMODASSIGN 272
#define TOR 273
#define TAND 274
#define TEQUAL 275
#define TNOTEQU 276
#define TGREATE 277
#define TLESSE 278
#define TINC 279
#define TDEC 280
#define TPLUS 281
#define TMINUS 282
#define TSTAR 283
#define TSLASH 284
#define TMOD 285
#define TASSIGN 286
#define TNOT 287
#define TLESS 288
#define TGREAT 289
#define TLSBRACKET 290
#define TRSBRACKET 291
#define TCOMMA 292
#define TLMBRACKET 293
#define TRMBRACKET 294
#define TLLBRACKET 295
#define TRLBRACKET 296
#define TSEMICOLON 297
#define TCOMMENT 298
#define TSEPERATOR 299
#define TLINE 300
#define TILLID 301
#define TERROR 302

extern YYSTYPE yylval;