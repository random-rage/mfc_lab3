#ifndef LAB3_HASH_H
#define LAB3_HASH_H

#include <stdlib.h>

class Hash
{
private:
	size_t len;
	
public:
	Hash(size_t size);
	
	u_int FAQ6(u_char *str);    // Bob Jenkins Hash Function
	u_int LY(u_char *str);      // Congruential generator proposed by Leonid Yuriev.
	
	size_t getLen() const;
	void setLen(size_t len);
};

#endif //LAB3_HASH_H