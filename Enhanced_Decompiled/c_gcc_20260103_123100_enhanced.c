// Function: _func0
undefined8 _func0(void)

{
  _puts("Hello, World!");
  return 0;
}

// Function: entry
undefined8 entry(void)

{
  _puts("Hello, World!");
  return 0;
}

// Function: _puts
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _puts(char *param_1)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001000004a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__puts_100004000)((int)param_1);
  return iVar1;
}


============================================================
/* LLM4Decompile ENHANCED FUNCTION */

/* LLM4Decompile enhanced function - 2026-01-03 12:31:18 */
int _func0() {
    _puts("Hello, World!");
    return 0;
}