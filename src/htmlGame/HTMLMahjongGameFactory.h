#ifndef HTMLMAHJONGGAMEFACTORY_H_
#define HTMLMAHJONGGAMEFACTORY_H_

#include "MahjongGameFactory.h"
struct HTMLMahjongGameFactory : public MahjongGameFactory{
	MahjongGameRespond * createMahjongGameRespond();
};

#endif /* HTMLMAHJONGGAMEFACTORY_H_ */
