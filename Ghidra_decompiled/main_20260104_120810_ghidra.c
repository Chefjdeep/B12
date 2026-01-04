// Function: entry
undefined4 entry(void)

{
  _add(10,5);
  _printf("Addition: %d\n");
  _subtract(10,5);
  _printf("Subtraction: %d\n");
  return 0;
}

// Function: _add
int _add(int param_1,int param_2)

{
  return param_1 + param_2;
}

// Function: _subtract
int _subtract(int param_1,int param_2)

{
  return param_1 - param_2;
}

// Function: _printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x000100000528. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_100004000)((int)param_1);
  return iVar1;
}

