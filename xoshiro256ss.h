/*
 * xoshiro256** - public domain PRNG by David Blackman and Sebastiano Vigna
 * Header-only implementation for netbench data verification.
 *
 * Reference: https://prng.di.unimi.it/xoshiro256starstar.c
 */

#ifndef XOSHIRO256SS_H
#define XOSHIRO256SS_H

#include <stdint.h>

struct xoshiro256ss_state {
	uint64_t s[4];
};

static inline uint64_t
xoshiro256ss_rotl(uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

static inline uint64_t
xoshiro256ss_next(struct xoshiro256ss_state *state)
{
	uint64_t *s = state->s;
	uint64_t result = xoshiro256ss_rotl(s[1] * 5, 7) * 9;
	uint64_t t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];
	s[2] ^= t;
	s[3] = xoshiro256ss_rotl(s[3], 45);

	return result;
}

/* splitmix64 for seeding */
static inline uint64_t
xoshiro256ss_splitmix64(uint64_t *x)
{
	uint64_t z = (*x += 0x9e3779b97f4a7c15ULL);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
	z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
	return z ^ (z >> 31);
}

static inline void
xoshiro256ss_init(struct xoshiro256ss_state *state, uint64_t seed)
{
	state->s[0] = xoshiro256ss_splitmix64(&seed);
	state->s[1] = xoshiro256ss_splitmix64(&seed);
	state->s[2] = xoshiro256ss_splitmix64(&seed);
	state->s[3] = xoshiro256ss_splitmix64(&seed);
}

#endif /* XOSHIRO256SS_H */
