#ifndef __PARAMS_H_
#define __PARAMS_H_

void run_args(int, char **);
char *help_usage_message(void);

int entry_state(void);
int security_state(void);
int security_grid_state(void);
int main_security_grid_state(void);
int alarm_state(void);
int help_state(void);
int exit_state(void);

#define EXIT_STATE end
#define ENTRY_STATE entry

#endif
