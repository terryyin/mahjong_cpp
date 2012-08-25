#include "Perspective.h"
#include "tile_pool.h"
#include "stdlib.h"
#include "string.h"
#include "mj_table.h"
#include "assert.h"

MahjongTable::~MahjongTable() {
	int i = 0;
	for (; i < this->player_count; i++)
		delete this->players[i];
}

Perspective * MahjongTable::get_player_of_distance( int i) {
	return this->players[(this->current_player + i)%this->player_count];
}

void MahjongTable::add_player(
		Perspective * player) {
	this->players[this->player_count++] = player;
}
int MahjongTable::get_player_count() {
	return this->player_count;
}
void MahjongTable::pick( tile_t tile) {
	int i = 0;
	for (i = 0; i < this->player_count ; i++) {
		Perspective * agent = get_player_of_distance(i);
		agent->pick(tile, i);
	}
}
void MahjongTable::change_host() {
	this->host = (this->host + 1) % this->player_count;
	this->current_player = this->host;
}
void MahjongTable::change_current_player( int distance) {
	this->current_player = (this->current_player + distance) % this->player_count;
}
void MahjongTable::win( int score) {
	int i = 0;
	for (i = 0; i < this->player_count ; i++) {
		Perspective * agent = get_player_of_distance(i);
		agent->win(score, i);
	}
	change_host();
}

void MahjongTable::deal( tile_t tiles[], int n) {
	int i = 0;
	for (i = 0; i < this->player_count ; i++) {
		Perspective * agent = get_player_of_distance(i);
		agent->deal(tiles, n, i);
	}
	change_current_player(1);
}

void MahjongTable::throw_tile( tile_t tile){
	int i = 0;
	for (i = 0; i < this->player_count ; i++) {
		Perspective * agent = get_player_of_distance(i);
		agent->discard_tile(tile, i);
	}
	this->last_tile = tile;
	change_current_player(1);
}
void MahjongTable::pong(){
	int i = 0;
	for (i = 0; i < this->player_count ; i++) {
		Perspective * agent = get_player_of_distance(i);
		agent->pong(this->last_tile, i);
	}
}
int MahjongTable::chow( tile_t with){
	int i = 0;
	Perspective * agent = get_player_of_distance(0);
	if (!agent->chow(this->last_tile, with, 0))
		return 0;
	for (i = 1; i < this->player_count ; i++) {
		agent = get_player_of_distance(i);
		agent->chow(this->last_tile, with, i);
	}
	return 1;
}

MahjongTable * create_mj_table(tile_pool_t *pool)
{
	return new MahjongTable(pool);
}
MahjongTable::MahjongTable(tile_pool_t *pool)
{
	this->tile_pool = pool;
	this->state = GAME_END;
	this->player_count = 0;
	this->current_player = 0;
	this->host = 0;
}

void MahjongTable::setPool(tile_pool_t * pool)
{
	tile_pool = pool;
}
void MahjongTable::remove_agent( Perspective * agent)
{
	int i = 0;
	for (; i < this->player_count; i++)
		if (this->players[i] == agent)
			this->players[i] = NULL;

}

game_state_t MahjongTable::get_state()
{
	return this->state;
}

void MahjongTable::update_state()
{
	int i;
	tile_t action_tile;
	Perspective * agent = get_player_of_distance(0);
	action_t player_action = agent->get_action(&action_tile);

	/**********
	 * get current player.
	 * *******************/
	if (player_action == ACTION_RESTART) {
		int i = 1;
		for (; i < this->player_count; i++) {
			Perspective * agent = get_player_of_distance(i);
			if(ACTION_RESTART != agent->get_action(NULL)){
				player_action = NO_ACTION;
				break;
			}
		}
	}

	if(this->state == GAME_END) {
		if (ACTION_RESTART == player_action){
			tile_pool->shuffle();
			tile_t tiles[MAX_HOLDING_COUNT];

			int cnt = get_player_count();
			for (; cnt >0; cnt --) {
				for (i = 0; i < MAX_HOLDING_COUNT; i++) {
					tiles[i] = tile_pool->pop_a_tile();
				}
				deal(tiles, MAX_HOLDING_COUNT);
			}

			pick(tile_pool->pop_a_tile());

			this->state = GAME_PICKED;
		}
	}
	else if (this->state == GAME_WAITING) {
		if (tile_pool->is_end()) {
			win(0);
			this->state = GAME_END;
		}
		else {
			this->state = GAME_PICKING;
		}
	}
	else if (this->state == GAME_PICKED) {
		if (NO_ACTION == player_action){
		}
		else if (ACTION_DISCARD == player_action) {
			throw_tile(action_tile);
			this->state = GAME_WAITING;
		} else if (ACTION_WIN == player_action) {
			win(1);
			this->state = GAME_END;
		}
	}
	else if (this->state ==GAME_PICKING) {
		if (ACTION_PICK == player_action) {
			pick(tile_pool->pop_a_tile());
			this->state = GAME_PICKED;
		}
		else if (ACTION_WIN == player_action) {
			win(1);
			this->state = GAME_END;
		}
		else if (ACTION_PONG == player_action) {
			pong();
			this->state = GAME_PICKED;
		}
		else if (ACTION_CHOW == player_action) {
			if(chow(action_tile))
				this->state = GAME_PICKED;
		}
	}
}
