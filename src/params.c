#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "params.h"
#include "access.h"

//Private function
int lookup_transitions(int, int);

//States
int (* state[])(void) = {
    entry_state,
    security_state,
    security_grid_state,
    main_security_grid_state,
    alarm_state,
    help_state,
    exit_state
};
enum state_codes { entry, security, security_grid, main_security_grid, security_alarm, help, end};

//Return codes
enum ret_codes { ok, fail};

//Transition structure
struct transition {
    enum state_codes src_state;
    enum ret_codes   ret_code;
    enum state_codes dst_state;
};
typedef struct transition tran;

//Transitions
tran state_transitions[] = {
    {entry,             	ok,     help},
    {entry,             	fail,   end},
    {security,          	ok,     end},
    {security,          	fail,   end},
    {security_grid,     	ok,     end},
    {security_grid,     	fail,   end},
    {main_security_grid, 	ok,     security_alarm},
    {main_security_grid, 	fail,   end},
    {security_alarm,		ok, 	security_alarm},
    {security_alarm,		fail, 	security_alarm},
    {help,					ok,		end},
    {help,					fail, 	end}
};

// Check next steps
int lookup_transitions(int current_state, int return_code)
{
	int i;
	for (i=0; i<12; i++) {
		struct transition trans = state_transitions[i];
		if (trans.src_state == current_state && trans.ret_code == return_code) {
			return trans.dst_state;
		}
	}

	return end;
}

void run_args(int argv, char **args)
{
	enum state_codes cur_state = ENTRY_STATE;

	switch (argv) {
	case 2:
		if (strcmp(args[1], "security") == 0) {
			cur_state = security;
		}
		break;
	case 3:
		if (strcmp(args[1], "security") == 0 && strcmp(args[2], "grid") == 0) {
			cur_state = security_grid;
		}
		break;
	case 4:
		if (strcmp(args[1], "main") == 0 &&
				strcmp(args[2], "security") == 0 &&
				strcmp(args[3], "grid") == 0) {
			cur_state = main_security_grid;
		}
		break;
	default:
		cur_state = help;
		break;
	}

	enum ret_codes rc;
	int (* state_fun)(void);

	while(1 == 1) {
		state_fun = state[cur_state];
		rc = state_fun();
		if (EXIT_STATE == cur_state)
			break;
		cur_state = lookup_transitions(cur_state, rc);
	}
}

char *help_usage_message(void)
{
    char *message = "\nUsage: access (security|security grid|main security grid)\n\n";

    return message;
}

int help_state(void)
{
	printf("%s", help_usage_message());
	return ok;
}

int entry_state(void)
{
	return ok;
}

int security_state(void)
{
	printf("\aaccess: PERMISSION DENIED.");

	return ok;
}

int security_grid_state(void)
{
	printf("\aaccess: PERMISSION DENIED.");

	return ok;
}

int main_security_grid_state(void)
{
	printf("\aaccess: PERMISSION DENIED.");

	return ok;
}

int alarm_state(void)
{
	printf("...and....\n");
	usleep(LONG_SLEEP);
	while (1 == 1) {
		usleep(CYCLE_SLEEP);
		printf("\aYOU DIDN'T SAY THE MAGIC WORD!!!!!!!\n");
	}

	return ok;
}

int exit_state(void)
{
	printf("\n");
	return ok;
}
