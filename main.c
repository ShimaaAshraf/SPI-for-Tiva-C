
#include "SSI0.h"

int main(void)
{
	SSI0Init();
	unsigned char RxData = 0;
	unsigned char TxData = 'a';
	while(1)
	{
		RxData = SSI0ExchangeData(TxData);
		TxData++;
	}
}
