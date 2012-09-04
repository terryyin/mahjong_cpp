#ifndef PLAYERACTIONREQUEST_H_
#define PLAYERACTIONREQUEST_H_

typedef enum {
	NO_ACTION,
	ACTION_DISCARD,
	ACTION_PICK,
	ACTION_PONG,
	ACTION_CHOW,
	ACTION_KONG,
	ACTION_WIN,
	ACTION_RESTART
}action_t;

class GameState;
class PlayerActionRequest {
public:
	PlayerActionRequest(action_t action, tile_t tile, int a) : action_(action), tile_(tile){}

	bool hasAction() {
		return action_ != NO_ACTION;
	}

	void doPlayerAction(GameState *state) ;

public:
	action_t action_;
	tile_t tile_;
};

#endif /* PLAYERACTIONREQUEST_H_ */
