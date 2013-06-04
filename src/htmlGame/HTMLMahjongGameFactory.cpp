#include "HTMLMahjongGameFactory.h"
#include "HTMLMahjongGameRespond.h"

MahjongGameRespond * HTMLMahjongGameFactory::createMahjongGameRespond(){
	return new HTMLMahjongGameRespond();
}
