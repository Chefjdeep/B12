// Function: _unsafe_buffer
void _unsafe_buffer(void)

{
  int iVar1;
  char acStack_20 [8];
  long local_18;
  
  local_18 = *(long *)PTR____stack_chk_guard_100004008;
  _printf("Enter your name: ");
  _gets(acStack_20);
  iVar1 = _printf("Hello %s\n");
  if (*(long *)PTR____stack_chk_guard_100004008 - local_18 != 0) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(*(long *)PTR____stack_chk_guard_100004008 - local_18,iVar1);
  }
  return;
}

// Function: _command_execution
void _command_execution(void)

{
  int iVar1;
  char acStack_58 [64];
  long local_18;
  
  local_18 = *(long *)PTR____stack_chk_guard_100004008;
  _printf("Enter a command (demo only): ");
  _scanf("%63s");
  iVar1 = _system(acStack_58);
  if (*(long *)PTR____stack_chk_guard_100004008 - local_18 != 0) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(*(long *)PTR____stack_chk_guard_100004008 - local_18,iVar1);
  }
  return;
}

// Function: entry
undefined8 entry(void)

{
  int iVar1;
  int local_18;
  
  _printf("1. Unsafe buffer demo\n");
  _printf("2. Command execution demo\n");
  _printf("Choose: ");
  iVar1 = _scanf("%d");
  if (local_18 == 1) {
    _unsafe_buffer(0);
  }
  else if (local_18 - 2U == 0) {
    _command_execution(iVar1);
  }
  else {
    _printf("Invalid choice\n",(ulong)(local_18 - 2U));
  }
  return 0;
}

// Function: ___stack_chk_fail
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001000005f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_100004000)();
  return;
}

// Function: _gets
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * _gets(char *param_1)

{
  char *pcVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000100000604. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pcVar1 = (char *)(*(code *)PTR__gets_100004010)();
  return pcVar1;
}

// Function: _printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000100000610. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_100004018)((int)param_1);
  return iVar1;
}

// Function: _scanf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _scanf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00010000061c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__scanf_100004020)((int)param_1);
  return iVar1;
}

// Function: _system
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _system(char *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000100000628. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__system_100004028)((int)param_1);
  return iVar1;
}

