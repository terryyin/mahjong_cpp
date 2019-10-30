set(Main_SRCS HTMLCommandParser.cpp HTMLCommandParser.h
  HTMLMahjongGame.cpp HTMLMahjongGame.h
  HTMLMahjongGameFactory.cpp HTMLMahjongGameFactory.h
  HTMLMahjongGameRespond.cpp HTMLMahjongGameRespond.h
  HTMLMahjongGameServer.cpp HTMLMahjongGameServer.h
  HTMLUIEvent.cpp HTMLUIEvent.h
  )

add_library(htmlGame ${Main_SRCS})

