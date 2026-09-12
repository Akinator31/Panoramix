# Panoramix

A multithreaded simulation of Asterix's village, written in C with POSIX threads.
The druid fills a cooking pot with magic potion, villagers drink a serving before
each fight, and they wake the druid up whenever the pot runs dry.

This project is an exercise on threads, mutexes and semaphores: shared state,
synchronization and graceful shutdown.

## Requirements

- A Linux environment
- `gcc` and `make`
- POSIX threads (`-lpthread`)

## Build

```bash
make          # build the panoramix binary
make re       # rebuild from scratch
make clean    # remove object files
make fclean   # remove object files and the binary
```

## Usage

```
./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
```

| Argument | Description |
| --- | --- |
| `nb_villagers` | Number of villagers, each running in its own thread (> 0) |
| `pot_size` | Number of servings the pot holds when full (> 0) |
| `nb_fights` | Number of fights each villager must win before going to sleep (> 0) |
| `nb_refills` | Number of times the druid can refill the pot (> 0) |

All values must be strictly positive. Invalid input prints the usage and exits
with code `84`.

```bash
$> ./panoramix -1 3 2 1 >/dev/null; echo $?
USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
Values must be >0.
84
```

## Example

```bash
$> ./panoramix 3 5 3 1
Druid: I'm ready... but sleepy...
Villager 2: Going into battle!
Villager 1: Going into battle!
Villager 0: Going into battle!
Villager 2: I need a drink... I see 5 servings left.
Villager 0: I need a drink... I see 4 servings left.
Villager 0: Take that roman scum! Only 2 left.
Villager 1: I need a drink... I see 3 servings left.
...
Villager 1: Hey Pano wake up! We need more potion.
Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only make 0 more refills after this one.
Druid: I'm out of viscum. I'm going back to... zZz
...
Villager 0: I'm going to sleep now.
Villager 1: I'm going to sleep now.
Villager 2: I'm going to sleep now.
```

Threads run asynchronously, so the exact interleaving changes between runs.

## How it works

- **One thread per villager, one for the druid.** The main thread parses the
  arguments, starts every thread, then joins them.
- **The pot is shared state.** A mutex protects the serving counter so that two
  villagers never take the last serving at the same time.
- **Semaphores drive the wake-up chain.** A villager that finds an empty pot
  signals the druid and blocks until the refill is announced; the druid blocks
  until it is called.
- **The pot starts full**, so the first `pot_size` servings need no refill.
- **Shutdown is graceful.** Villagers stop once their fights are done, the druid
  stops once it has no viscum left, and every thread is joined before exiting.

### Starvation

When the druid runs out of refills, villagers that still need potion would wait
forever on an empty pot. The druid broadcasts its last refill so that those
threads can unblock and terminate instead of hanging, which is why the program
still exits cleanly when `nb_refills` is too small for the demand.

## Project structure

```
.
├── Makefile
├── include/
│   └── panoramix.h
└── src/
    ├── main.c          # argument parsing and thread orchestration
    ├── villager.c      # villager routine
    └── druid.c         # druid routine
```
