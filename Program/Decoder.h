#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_LTH 9
#define MAX_KEYWORD_NR 2
//#define NULL 0

enum TokenType {KEYWORD, NUMBER, STRING};

enum KeywordCode {LED, ID};

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
	char cString[MAX_KEYWORD_LTH + 1];
};

unsigned char DecodeMsg(char *pcString);
