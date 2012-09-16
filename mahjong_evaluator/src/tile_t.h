#ifndef TILE_T__H
#define TILE_T__H

typedef char tile_t;
#define	NO_TILE  (0)
#define MJ_CHARACTOR_BASE  '0'
#define MJ_CIRCLE_BASE  '@'
#define MJ_BAMBOO_BASE  '`'
#define MJ_EAST  (MJ_BAMBOO_BASE+12)
#define MJ_SOUTH  (MJ_BAMBOO_BASE+15)
#define MJ_WEST  (MJ_BAMBOO_BASE+18)
#define MJ_NORTH  (MJ_BAMBOO_BASE+21)
#define MJ_ZHONG  (MJ_BAMBOO_BASE+24)
#define MJ_BAI  (MJ_BAMBOO_BASE+30)

#define MJ_CHARACTOR(n)    ((MJ_CHARACTOR_BASE + (n)))
#define C MJ_CHARACTOR
#define MJ_CIRCLE(n)    ((MJ_CIRCLE_BASE + (n)))
#define R MJ_CIRCLE
#define MJ_BAMBOO(n)    ((MJ_BAMBOO_BASE + (n)))
#define B MJ_BAMBOO

#endif
