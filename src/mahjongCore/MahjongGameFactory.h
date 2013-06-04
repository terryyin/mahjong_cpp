#ifndef MAHJONGGAMEFACTORY_H_
#define MAHJONGGAMEFACTORY_H_

class MahjongGameRespond;
struct MahjongGameFactory {
	virtual ~MahjongGameFactory(){}
	virtual MahjongGameRespond * createMahjongGameRespond() = 0;

};


#endif /* MAHJONGGAMEFACTORY_H_ */
