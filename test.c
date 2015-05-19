#include <bios.h>
int main()
{
	while (1)
	{
		printf("%x\n",bioskey(0));
	}
	return 0;
}