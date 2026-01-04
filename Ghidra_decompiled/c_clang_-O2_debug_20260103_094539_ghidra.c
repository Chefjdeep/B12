// Function: entry
undefined8 entry(void)

{
  _printf("%d ");
  _printf("%d ");
  _printf("%d ");
  _printf("%d ");
  _printf("%d ");
  return 0;
}

// Function: _printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001000004e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_100004000)((int)param_1);
  return iVar1;
}

