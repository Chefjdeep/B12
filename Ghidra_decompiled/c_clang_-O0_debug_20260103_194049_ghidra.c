// Function: entry
undefined8 entry(void)

{
  int local_18;
  
  for (local_18 = 0; local_18 < 5; local_18 = local_18 + 1) {
    _printf("%d ");
  }
  return 0;
}

// Function: _printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001000004cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_100004000)((int)param_1);
  return iVar1;
}

