#include "main.h"

int main()
{
	XinputHandler* handler = new XinputHandler(1);


	handler->ResetStates();
	handler->SetPlayer(0);
	handler->UpdatePlayerState();

	bool save = handler->AButtonIsDown();



	int bp = 1;

	return 0;
}