#include "hash.h"

struct HashValue makeHashValue(char* c){
	struct HashValue h;
	long long value1=0,value2=0,value;
	int len=strlen(c);
	for(int i=0;i<len;i++){
		value1 = (value1*256 + (int)c[i])%M1;
	}
	for(int i=0;i<len;i++){
		value2 = (value2*256 + (int)c[i])%M2;
	}
	h.hash1 =value1,h.hash2 =value2;
	return h;
}

int cmpHashValue(struct HashValue h1,struct HashValue h2){
	if()
}
