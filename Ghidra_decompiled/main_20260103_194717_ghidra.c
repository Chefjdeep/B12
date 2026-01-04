// Function: entry
undefined4 entry(void)

{
  int iVar1;
  int iVar2;
  undefined4 local_2c;
  sockaddr local_28;
  long local_18;
  
  local_18 = *(long *)PTR____stack_chk_guard_100004000;
  iVar1 = _socket(2,1,0);
  if (iVar1 < 0) {
    _perror("socket");
    local_2c = 1;
  }
  else {
    local_28.sa_data[6] = '\0';
    local_28.sa_data[7] = '\0';
    local_28.sa_data[8] = '\0';
    local_28.sa_data[9] = '\0';
    local_28.sa_data[10] = '\0';
    local_28.sa_data[11] = '\0';
    local_28.sa_data[12] = '\0';
    local_28.sa_data[13] = '\0';
    local_28.sa_len = '\0';
    local_28.sa_family = '\x02';
    local_28.sa_data[0] = '\x11';
    local_28.sa_data[1] = '\\';
    local_28.sa_data[2] = '\0';
    local_28.sa_data[3] = '\0';
    local_28.sa_data[4] = '\0';
    local_28.sa_data[5] = '\0';
    iVar2 = _inet_pton(2,"192.168.1.100",local_28.sa_data + 2);
    if (iVar2 < 1) {
      _perror("inet_pton");
      _close(iVar1);
      local_2c = 1;
    }
    else {
      iVar2 = _connect(iVar1,&local_28,0x10);
      if (iVar2 < 0) {
        _perror("connect");
        _close(iVar1);
        local_2c = 1;
      }
      else {
        _system("echo Hello > test.txt");
        _printf("Decoded string: %s\n");
        _close(iVar1);
        local_2c = 0;
      }
    }
  }
  if (*(long *)PTR____stack_chk_guard_100004000 - local_18 != 0) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(*(long *)PTR____stack_chk_guard_100004000 - local_18);
  }
  return local_2c;
}

// Function: _socket
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _socket(int param_1,int param_2,int param_3)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001000005d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__socket_100004008)(param_1,param_2,param_3);
  return iVar1;
}

// Function: _perror
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void _perror(char *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x0001000005e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR__perror_100004010)();
  return;
}

// Function: _inet_pton
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _inet_pton(int param_1,char *param_2,void *param_3)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001000005f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__inet_pton_100004018)(param_1);
  return iVar1;
}

// Function: _close
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _close(int param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001000005fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__close_100004020)(param_1);
  return iVar1;
}

// Function: _connect
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _connect(int param_1,sockaddr *param_2,socklen_t param_3)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000100000608. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__connect_100004028)(param_1,param_2,param_3);
  return iVar1;
}

// Function: _system
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _system(char *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000100000614. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__system_100004030)((int)param_1);
  return iVar1;
}

// Function: _printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000100000620. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_100004038)((int)param_1);
  return iVar1;
}

// Function: ___stack_chk_fail
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x00010000062c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_100004040)();
  return;
}

