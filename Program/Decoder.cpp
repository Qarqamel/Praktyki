#include "Decoder.h"
#include <string.h>
#include <stdio.h>

struct Token asToken[MAX_TOKEN_NR];

struct Keyword asKeywordList[MAX_KEYWORD_NR] =
{
	{LED, "led"},
	{ID, "id"},
  {TEMPVAL, "tempval"},
  {TEMPID, "tempid"}
};

unsigned char ucTokenNr = 0;

unsigned char FindTokens(char *pcStr){
  char *ptr = NULL;
  unsigned char ctr = 0;
  ptr = strtok(pcStr, " ");
  while((ptr != NULL) && (ctr<MAX_TOKEN_NR)){
    asToken[ctr].uValue.pcString = ptr;
    ctr++;
    ptr = strtok(NULL, " ");
  }
  return ctr;
}

unsigned char StringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode){
	
	unsigned char ucKeywordCounter;
	
	for (ucKeywordCounter=0; ucKeywordCounter<MAX_KEYWORD_NR; ucKeywordCounter++){
		if(0 == strcmp(asKeywordList[ucKeywordCounter].cString, pcStr)){
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return 0;
		}
	}
	return 1;
}

void DecodeTokens(){
	
	unsigned char ucTokenCounter;
	struct Token *psCurrentToken;
	unsigned int uiTokenValue;
	enum KeywordCode eTokenCode;
	
	for(ucTokenCounter =0; ucTokenCounter<ucTokenNr; ucTokenCounter++){
		psCurrentToken = &asToken[ucTokenCounter];
		if(0 == StringToKeyword(psCurrentToken->uValue.pcString, &eTokenCode)){
			psCurrentToken->eType = KEYWORD;
			psCurrentToken->uValue.eKeyword = eTokenCode;
		}
		else if (sscanf(psCurrentToken->uValue.pcString, "%d", &uiTokenValue) == 1){
			psCurrentToken->eType = NUMBER;
			psCurrentToken->uValue.uiValue = uiTokenValue;
		}
		else{
			psCurrentToken->eType = STRING;
		}
	}
}

unsigned char DecodeMsg(char *pcString){
	char *ptr = pcString;
	ucTokenNr = FindTokens(pcString);
	DecodeTokens();
  return ucTokenNr;
}
