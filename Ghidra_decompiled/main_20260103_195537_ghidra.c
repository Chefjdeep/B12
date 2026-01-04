// Function: entry
undefined4 entry(void)

{
  _printf("Hello World\n");
  return 0;
}

// Function: _printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00010000049c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_100004000)((int)param_1);
  return iVar1;
}

