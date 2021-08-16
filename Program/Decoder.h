#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_LTH 8
#define MAX_KEYWORD_NR 3

enum TokenType {KEYWORD, NUMBER, STRING};

enum KeywordCode {ID, TEMPID, TEMPVAL};

union TokenValue
{
	enum KeywordCode eKeyword;
	unsigned int uiValue;
	char *pcString;
};

struct Token
{
	enum TokenType eType;
	union TokenValue uValue;
};

struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_LTH];
};

unsigned char DecodeMsg(char *pcString);
