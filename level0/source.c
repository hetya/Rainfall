#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    int number;
	char **cmd_args;
    uid_t uid;
    gid_t gid;

    number = atoi(av[1]);
    if (number == 423) {
        cmd_args[0] = strdup("/bin/sh");
		cmd_args[1] = 0;
		gid = getegid();
        uid = geteuid();
        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);
        execv("/bin/sh", cmd_args);
    }
	else {
		fwrite("No !\n", 1, 5, stderr);
    }
    return 0;
}