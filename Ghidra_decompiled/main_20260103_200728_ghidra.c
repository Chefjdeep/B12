// Function: _message
int _message(void)

{
  int iVar1;
  
  iVar1 = _printf("This is another function\n");
  return iVar1;
}

// Function: entry
undefined4 entry(void)

{
  int iVar1;
  
  iVar1 = _printf("Hello World\n");
  _message(iVar1);
  return 0;
}

// Function: _printf
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001000004bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_100004000)((int)param_1);
  return iVar1;
}

