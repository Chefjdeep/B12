// Function: _init
int _init(EVP_PKEY_CTX *ctx)

{
  undefined *puVar1;
  
  puVar1 = PTR___gmon_start___00403fe0;
  if (PTR___gmon_start___00403fe0 != (undefined *)0x0) {
    puVar1 = (undefined *)__gmon_start__();
  }
  return (int)puVar1;
}

// Function: FUN_00401020
void FUN_00401020(void)

{
  (*(code *)PTR_00403ff8)();
  return;
}

// Function: <EXTERNAL>::puts
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int puts(char *__s)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_puts_00404000)();
  return iVar1;
}

// Function: <EXTERNAL>::__libc_start_main
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __libc_start_main(void)

{
  (*_DAT_00404008)();
  return;
}

// Function: <EXTERNAL>::__gmon_start__
void __gmon_start__(void)

{
  (*(code *)PTR___gmon_start___00403fe0)();
  return;
}

// Function: _start
void processEntry _start(undefined8 param_1,undefined8 param_2)

{
  undefined auStack_8 [8];
  
  __libc_start_main(main,param_2,&stack0x00000008,__libc_csu_init,__libc_csu_fini,param_1,auStack_8)
  ;
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

// Function: deregister_tm_clones
/* WARNING: Removing unreachable block (ram,0x00401097) */
/* WARNING: Removing unreachable block (ram,0x004010a1) */

void deregister_tm_clones(void)

{
  return;
}

// Function: register_tm_clones
/* WARNING: Removing unreachable block (ram,0x004010d8) */

void register_tm_clones(void)

{
  return;
}

// Function: __do_global_dtors_aux
void __do_global_dtors_aux(void)

{
  if (completed_0 == '\0') {
    deregister_tm_clones();
    completed_0 = 1;
    return;
  }
  return;
}

// Function: frame_dummy
void frame_dummy(void)

{
  register_tm_clones();
  return;
}

// Function: func0
undefined8 func0(void)

{
  puts("Hello, World!");
  return 0;
}

// Function: main
undefined8 main(void)

{
  func0();
  return 0;
}

// Function: __libc_csu_init
void __libc_csu_init(EVP_PKEY_CTX *param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  
  _init(param_1);
  lVar1 = 0;
  do {
    (*(code *)(&__frame_dummy_init_array_entry)[lVar1])((ulong)param_1 & 0xffffffff,param_2,param_3)
    ;
    lVar1 = lVar1 + 1;
  } while (lVar1 == 0);
  return;
}

// Function: __libc_csu_fini
void __libc_csu_fini(void)

{
  return;
}

// Function: _fini
void _fini(void)

{
  return;
}

// Function: <EXTERNAL>::puts
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int puts(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* puts@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::__libc_start_main
/* WARNING: Control flow encountered bad instruction data */

void __libc_start_main(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* __libc_start_main@GLIBC_2.2.5 */
  halt_baddata();
}

// Function: <EXTERNAL>::__gmon_start__
/* WARNING: Control flow encountered bad instruction data */

void __gmon_start__(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


============================================================
/* LLM4Decompile ENHANCED FUNCTION */

/* LLM4Decompile enhanced function - 2025-12-30 14:57:34 */
int func0(void)
{
  puts("Hello, World!");
  return 0;
}