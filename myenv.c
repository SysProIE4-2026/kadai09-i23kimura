/*
 *  myenv.c : env コマンドのクローン
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#ifdef __linux__
#include "myputenv.h"
#endif

extern char **environ;

int main(int argc, char *argv[]) {
  int i = 1;

  while (i < argc && strchr(argv[i], '=') != NULL) {
    #ifdef __linux__
    myputenv(argv[i]);
    #else
    putenv(argv[i]);
    #endif
    i++;
  }

  if (i == argc) {
    char **env = environ;
    while (*env) {
      printf("%s\n", *env);
      env++;
    }
    return 0;
  }

  pid_t pid = fork();

  if (pid < 0) {
    fprintf(stderr, "env: fork: %s\n", strerror(errno));
    return 1;
  } 
  else if (pid == 0) {
    execvp(argv[i], &argv[i]);

    fprintf(stderr, "env: ‘%s’: %s\n", argv[i], strerror(errno));
        
    if (errno == ENOENT) {
      exit(127);
    } else if (errno == EACCES) {
      exit(126);
    }
    exit(1);
  } 
  else {
    int status;
    if (waitpid(pid, &status, 0) == -1) {
      return 1;
    }

    if (WIFEXITED(status)) {
      return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
      return 128 + WTERMSIG(status);
    }
  }

  return 0;
}

/* 実行例
% make
cc -D_GNU_SOURCE -Wall -std=c99 -o myenv myenv.c myputenv.c
% ./myenv
TMPDIR=/var/folders/lm/w_wtytvs32xgr3ny1gyfwx2r0000gn/T/
__CFBundleIdentifier=com.apple.Terminal
XPC_FLAGS=0x0
TERM=xterm-256color
SSH_AUTH_SOCK=/var/run/com.apple.launchd.NptCCM33FT/Listeners
DISPLAY=/var/run/com.apple.launchd.uu7ozd7mlA/org.xquartz:0
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
COLORTERM=truecolor
OSLogRateLimit=64
TERM_PROGRAM_VERSION=470.2
TERM_SESSION_ID=7C5DB4F3-BDE2-420D-AD62-385A658F1FE2
SHELL=/bin/zsh
HOME=/Users/kimuraharuya
LOGNAME=kimuraharuya
USER=kimuraharuya
PATH=/opt/homebrew/opt/openjdk/bin:/opt/homebrew/opt/openjdk/bin:/opt/homebrew/opt/openjdk/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/pkg/env/global/bin:/opt/X11/bin
SHLVL=1
PWD=/Users/kimuraharuya/SysPro/kadai09-i23kimura
OLDPWD=/Users/kimuraharuya/SysPro
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions:/usr/local/share/zsh/site-functions:/usr/share/zsh/site-functions:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:
CPPFLAGS=-I/opt/homebrew/opt/openjdk/include
LANG=ja_JP.UTF-8
_=/Users/kimuraharuya/SysPro/kadai09-i23kimura/./myenv
% ./myenv LANG=en_US.UTF-8 date
Fri Jul  3 23:55:41 JST 2026
% date
2026年 7月 3日 金曜日 23時55分50秒 JST
% ./myenv TEST_VAR=hoge printenv TEST_VAR
hoge
 % ./myenv VAR1=apple VAR2=banana printenv
TMPDIR=/var/folders/lm/w_wtytvs32xgr3ny1gyfwx2r0000gn/T/
__CFBundleIdentifier=com.apple.Terminal
XPC_FLAGS=0x0
TERM=xterm-256color
SSH_AUTH_SOCK=/var/run/com.apple.launchd.NptCCM33FT/Listeners
DISPLAY=/var/run/com.apple.launchd.uu7ozd7mlA/org.xquartz:0
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
COLORTERM=truecolor
OSLogRateLimit=64
TERM_PROGRAM_VERSION=470.2
TERM_SESSION_ID=7C5DB4F3-BDE2-420D-AD62-385A658F1FE2
SHELL=/bin/zsh
HOME=/Users/kimuraharuya
LOGNAME=kimuraharuya
USER=kimuraharuya
PATH=/opt/homebrew/opt/openjdk/bin:/opt/homebrew/opt/openjdk/bin:/opt/homebrew/opt/openjdk/bin:/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/pkg/env/global/bin:/opt/X11/bin
SHLVL=1
PWD=/Users/kimuraharuya/SysPro/kadai09-i23kimura
OLDPWD=/Users/kimuraharuya/SysPro
HOMEBREW_PREFIX=/opt/homebrew
HOMEBREW_CELLAR=/opt/homebrew/Cellar
HOMEBREW_REPOSITORY=/opt/homebrew
FPATH=/opt/homebrew/share/zsh/site-functions:/usr/local/share/zsh/site-functions:/usr/share/zsh/site-functions:/usr/share/zsh/5.9/functions
INFOPATH=/opt/homebrew/share/info:
CPPFLAGS=-I/opt/homebrew/opt/openjdk/include
LANG=ja_JP.UTF-8
_=/Users/kimuraharuya/SysPro/kadai09-i23kimura/./myenv
VAR1=apple
VAR2=banana

*/
