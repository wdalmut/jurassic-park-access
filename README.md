
# Jurassic Park - Access (State Machine Pattern - C Programming Language)

Just a simple "access program" from jurassic park movie...

http://www.youtube.com/watch?v=RfiQYRn7fBg

## Why

Just for fun and to implement a state machine pattern in C programming language.

Effectively the Jurassic Park program is not very similar to this example because is 
probably more close to a custom shell.

## How

The machine state is configured to execute steps using input commands:

 * access security
 * access security grid
 * access main security grid

When the latest command is executed the state machine loop itself into the "alarm state"
use CTRL-C to stop it.

## Compile

Just use make

```shell
make
```



