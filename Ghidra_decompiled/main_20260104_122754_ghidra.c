// Function: _process_data
int _process_data(long param_1,int param_2)

{
  int iVar1;
  int local_28;
  
  for (local_28 = 0; local_28 < param_2; local_28 = local_28 + 1) {
    if (100 < *(int *)(param_1 + (long)local_28 * 8)) {
      _printf("Large x: %d\n");
    }
  }
  iVar1 = _printf("Average: (%d, %d)\n");
  return iVar1;
}

// Function: _calculate_factorial
int _calculate_factorial(int param_1)

{
  int local_14;
  
  if (param_1 < 2) {
    local_14 = 1;
  }
  else {
    local_14 = _calculate_factorial(param_1 + -1);
    local_14 = param_1 * local_14;
  }
  return local_14;
}

// Function: entry
undefined8 entry(void)

{
  int iVar1;
  int local_48;
  int aiStack_40 [10];
  long local_18;
  
  local_18 = *(long *)PTR____stack_chk_guard_100004008;
  for (local_48 = 0; local_48 < 5; local_48 = local_48 + 1) {
    aiStack_40[(long)local_48 * 2] = local_48 * 0x14;
    aiStack_40[(long)local_48 * 2 + 1] = local_48 * 0x1e;
  }
  _process_data(local_48 + -5,aiStack_40);
  _calculate_factorial(5);
  iVar1 = _printf("Factorial of 5: %d\n");
  if (*(long *)PTR____stack_chk_guard_100004008 - local_18 != 0) {
                    /* WARNING: Subroutine does not return */
    ___stack_chk_fail(*(long *)PTR____stack_chk_guard_100004008 - local_18,iVar1);
  }
  return 0;
}

// Function: ___stack_chk_fail
void ___stack_chk_fail(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001000006b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR____stack_chk_fail_100004000)();
  return;
}

// Function: _printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001000006c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_100004010)((int)param_1);
  return iVar1;
}

