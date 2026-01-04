/*
 * ===================================================
 * LLM4Decompile Enhancement Applied
 * Time: 2026-01-04 12:30:50
 * Enhanced functions: 8
 * ===================================================
 * Overall Statistics:
 *   Original length: 351 chars
 *   Enhanced length: 856 chars
 *   Difference: +505 chars (+143.87%)
 * ===================================================
 * 100 < *(int *: 93 → 142 chars (+52.69%)
 * param_1 < 2: 42 → 266 chars (+533.33%)
 * entry: 42 → 42 chars (+0.0%)
 * *(long *: 174 → 406 chars (+133.33%)
 * ===================================================
 */

// Function: _process_data
int _process_data(long param_1,int param_2)

{
  int iVar1;
  int local_28;
  
  for (local_28 = 0; local_28 < param_2; local_28 = local_28 + 1) {
/* LLM4Decompile enhanced - 2026-01-04 12:29:19 */
void
100 < *(int* (int*x, int i)
{
  if (x[i] > 100)
    _printf ("Large x: %d\n", x[i]);
}
  }
  iVar1 = _printf("Average: (%d, %d)\n");
  return iVar1;
}

// Function: _calculate_factorial
int _calculate_factorial(int param_1)

{
  int local_14;
  
/* LLM4Decompile enhanced - 2026-01-04 12:29:26 */
int
arg1 < 2(int n)
{
    int i;
    int ret = 1;

    if (n < 2)
        return 1;

    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            ret = 0;
            break;
        }
    }

    return ret;
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
/* LLM4Decompile enhanced - 2026-01-04 12:30:50 */
void*(long*((noinline))
__attribute__((regparm(3)))
foo (int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o, int p, int q, int r, int s, int t, int u, int v, int w, int x, int y, int z)
{
  if (PTR____stack_chk_guard_100004008 - &a != 0)
    ___stack_chk_fail (PTR____stack_chk_guard_100004008 - &a);
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

// Function: _printf
int _printf(char *param_1,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0001000006c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR__printf_100004010)((int)param_1);
  return iVar1;
}

